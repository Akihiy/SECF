/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <jni.h>
#include <android/bitmap.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <utility>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include "include/errorcode.h"
#include "include/ms_tensor.h"
#include "MindSporeNetnative.h"
#include "MSNetWork.h"
#include "lite_cv/lite_mat.h"
#include "lite_cv/image_process.h"

static const int RET_GARBAGE_SORT_SUM = 4;
static const char *labels_name_grbage_sort_map[RET_GARBAGE_SORT_SUM] = {{"可回收物"},
                                                                        {"干垃圾"},
                                                                        {"有害垃圾"},
                                                                        {"湿垃圾"}};

static const int RET_GARBAGE_DETAILED_SUM = 26;
static const char *labels_name_grbage_detailed_map[RET_GARBAGE_DETAILED_SUM] = {
        {"塑料瓶"},
        {"帽子"},
        {"报纸"},
        {"易拉罐"},
        {"玻璃制品"},
        {"玻璃瓶"},
        {"硬纸板"},
        {"篮球"},
        {"纸张"},
        {"金属制品"},              //可回收物
        {"一次性筷子"},
        {"打火机"},
        {"扫把"},
        {"旧镜子"},
        {"牙刷"},
        {"脏污衣服"},
        {"贝壳"},
        {"陶瓷碗"},                 //干垃圾
        {"油漆桶"},
        {"电池"},
        {"荧光灯"},
        {"药片胶囊"},                //有害垃圾
        {"橙皮"},
        {"菜叶"},
        {"蛋壳"},
        {"香蕉皮"}};                 //湿垃圾


static float g_thres_map[RET_GARBAGE_DETAILED_SUM] = {
  0.23, 0.03, 0.10, 0.13, 0.03,
  0.10, 0.06, 0.09, 0.09, 0.05,
  0.01, 0.04, 0.01, 0.27, 0.05,
  0.16, 0.01, 0.16, 0.04, 0.13,
  0.09, 0.18, 0.10, 0.65, 0.08,
  0.04,

};

char *CreateLocalModelBuffer(JNIEnv *env, jobject modelBuffer) {
  jbyte *modelAddr = static_cast<jbyte *>(env->GetDirectBufferAddress(modelBuffer));
  int modelLen = static_cast<int>(env->GetDirectBufferCapacity(modelBuffer));
  char *buffer(new char[modelLen]);
  memcpy(buffer, modelAddr, modelLen);
  return buffer;
}

/**
 * To process the result of MindSpore inference.
 * @param msOutputs
 * @return
 */
std::string ProcessRunnetResult(const int RET_CATEGORY_SUM, const char *const labels_name_map[],
                                std::unordered_map<std::string, mindspore::MSTensor> msOutputs) {
  // Get the branch of the model output.
  // Use iterators to get map elements.
  std::unordered_map<std::string, mindspore::MSTensor>::iterator iter;
  iter = msOutputs.begin();

  // The mobilenetv2.ms model output just one branch.
  auto outputTensor = iter->second;

  int tensorNum = outputTensor.ElementNum();
  //MS_PRINT("Number of tensor elements:%d", tensorNum);

  // Get a pointer to the first score.
  float *temp_scores = static_cast<float *>(outputTensor.MutableData());
  float scores[RET_CATEGORY_SUM];
  for (int i = 0; i < RET_CATEGORY_SUM; ++i) {
    scores[i] = temp_scores[i];
  }

  const float unifiedThre = 0.5;
  const float probMax = 1.0;
  for (size_t i = 0; i < RET_CATEGORY_SUM; ++i) {
    float threshold = g_thres_map[i];
    float tmpProb = scores[i];
    if (tmpProb < threshold) {
      tmpProb = tmpProb / threshold * unifiedThre;
    } else {
      tmpProb = (tmpProb - threshold) / (probMax - threshold) * unifiedThre + unifiedThre;
    }
    scores[i] = tmpProb;
  }

  for (int i = 0; i < RET_CATEGORY_SUM; ++i) {
    if (scores[i] > 0.5) {
      //MS_PRINT("MindSpore scores[%d] : [%f]", i, scores[i]);
    }
  }

  // Score for each category.
  // Converted to text information that needs to be displayed in the APP.
  std::string categoryScore = "";
  for (int i = 0; i < RET_CATEGORY_SUM; ++i) {
    categoryScore += labels_name_map[i];
    categoryScore += ":";
    std::string score_str = std::to_string(scores[i]);
    categoryScore += score_str;
    categoryScore += ";";
  }
  return categoryScore;
}

bool BitmapToLiteMat(JNIEnv *env, const jobject &srcBitmap, mindspore::dataset::LiteMat *lite_mat) {
  bool ret = false;
  AndroidBitmapInfo info;
  void *pixels = nullptr;
  mindspore::dataset::LiteMat &lite_mat_bgr = *lite_mat;
  AndroidBitmap_getInfo(env, srcBitmap, &info);
  if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
    //MS_PRINT("Image Err, Request RGBA");
    return false;
  }
  AndroidBitmap_lockPixels(env, srcBitmap, &pixels);
  if (info.stride == info.width * 4) {
    ret = InitFromPixel(reinterpret_cast<const unsigned char *>(pixels),
                        mindspore::dataset::LPixelType::RGBA2RGB, mindspore::dataset::LDataType::UINT8,
                        info.width, info.height, lite_mat_bgr);
    if (!ret) {
      //MS_PRINT("Init From RGBA error");
    }
  } else {
    unsigned char *pixels_ptr = new unsigned char[info.width * info.height * 4];
    unsigned char *ptr = pixels_ptr;
    unsigned char *data = reinterpret_cast<unsigned char *>(pixels);
    for (int i = 0; i < info.height; i++) {
      memcpy(ptr, data, info.width * 4);
      ptr += info.width * 4;
      data += info.stride;
    }
    ret = InitFromPixel(reinterpret_cast<const unsigned char *>(pixels_ptr),
                        mindspore::dataset::LPixelType::RGBA2RGB, mindspore::dataset::LDataType::UINT8,
                        info.width, info.height, lite_mat_bgr);
    if (!ret) {
     // MS_PRINT("Init From RGBA error");
    }
    delete[] (pixels_ptr);
  }
  AndroidBitmap_unlockPixels(env, srcBitmap);
  return ret;
}

bool PreProcessImageData(const mindspore::dataset::LiteMat &lite_mat_bgr, mindspore::dataset::LiteMat *lite_norm_mat_ptr) {
  bool ret = false;
  mindspore::dataset::LiteMat lite_mat_resize;
  mindspore::dataset::LiteMat &lite_norm_mat_cut = *lite_norm_mat_ptr;
  ret = ResizeBilinear(lite_mat_bgr, lite_mat_resize, 256, 256);
  if (!ret) {
    //MS_PRINT("ResizeBilinear error");
    return false;
  }
  mindspore::dataset::LiteMat lite_mat_convert_float;
  ret = ConvertTo(lite_mat_resize, lite_mat_convert_float, 1.0 / 255.0);
  if (!ret) {
    //MS_PRINT("ConvertTo error");
    return false;
  }
  mindspore::dataset::LiteMat lite_mat_cut;
  ret = Crop(lite_mat_convert_float, lite_mat_cut, 16, 16, 224, 224);
  if (!ret) {
   // MS_PRINT("Crop error");
    return false;
  }
  std::vector<float> means = {0.485, 0.456, 0.406};
  std::vector<float> stds = {0.229, 0.224, 0.225};
  SubStractMeanNormalize(lite_mat_cut, lite_norm_mat_cut, means, stds);
  return true;
}


/**
 * The Java layer reads the model into MappedByteBuffer or ByteBuffer to load the model.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_mindspore_classification_gallery_classify_TrackingMobile_loadModel(JNIEnv *env,
                         jobject thiz,
                         jobject model_buffer,
                         jint num_thread) {
  if (nullptr == model_buffer) {
    //MS_PRINT("error, buffer is nullptr!");
    return (jlong) nullptr;
  }
  jlong bufferLen = env->GetDirectBufferCapacity(model_buffer);
  if (0 == bufferLen) {
   // MS_PRINT("error, bufferLen is 0!");
    return (jlong) nullptr;
  }

  char *modelBuffer = CreateLocalModelBuffer(env, model_buffer);
  if (modelBuffer == nullptr) {
   // MS_PRINT("modelBuffer create failed!");
    return (jlong) nullptr;
  }

  // To create a MindSpore network inference environment.
  void **labelEnv = new void *;
  MSNetWork *labelNet = new MSNetWork;
  *labelEnv = labelNet;

  auto context = std::make_shared<mindspore::Context>();
  if (context == nullptr) {
    //MS_PRINT("context create failed!");
    delete labelNet;
    delete labelEnv;
    return (jlong) nullptr;
  }

  context->SetThreadNum(num_thread);
  context->SetThreadAffinity(0);
  auto &device_list = context->MutableDeviceInfo();
  auto cpuDeviceInfo = std::make_shared<mindspore::CPUDeviceInfo>();
  cpuDeviceInfo->SetEnableFP16(false);
  device_list.push_back(cpuDeviceInfo);

  if (!labelNet->BuildModel(modelBuffer, bufferLen, context)) {
    //MS_PRINT("MindSpore Build model failed!.");
    delete labelNet;
    delete labelEnv;
    return (jlong) nullptr;
  }

  return (jlong) labelEnv;
}

/**
 * After the inference environment is successfully created,
 * sending a picture to the model and run inference.
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_mindspore_classification_gallery_classify_TrackingMobile_runNet(JNIEnv *env, jclass type,
                      jlong netEnv,
                      jobject srcBitmap) {
  mindspore::dataset::LiteMat lite_mat_bgr, lite_norm_mat_cut;

  if (!BitmapToLiteMat(env, srcBitmap, &lite_mat_bgr)) {
  //  MS_PRINT("BitmapToLiteMat error");
    return NULL;
  }
  if (!PreProcessImageData(lite_mat_bgr, &lite_norm_mat_cut)) {
    //MS_PRINT("PreProcessImageData error");
    return NULL;
  }

  ImgDims inputDims;
  inputDims.channel = lite_norm_mat_cut.channel_;
  inputDims.width = lite_norm_mat_cut.width_;
  inputDims.height = lite_norm_mat_cut.height_;

  // Get the MindSpore inference environment which created in loadModel().
  void **labelEnv = reinterpret_cast<void **>(netEnv);
  if (labelEnv == nullptr) {
    //MS_PRINT("MindSpore error, labelEnv is a nullptr.");
    return NULL;
  }
  MSNetWork *labelNet = static_cast<MSNetWork *>(*labelEnv);

  auto mModel = labelNet->model();
  if (mModel == nullptr) {
    //MS_PRINT("MindSpore error, Session is a nullptr.");
    return NULL;
  }
  //MS_PRINT("MindSpore get session.");

  auto msInputs = mModel->GetInputs();
  if (msInputs.empty()) {
    //MS_PRINT("MindSpore error, msInputs.size() equals 0.");
    return NULL;
  }
  auto inTensor = msInputs.front();

  float *dataHWC = reinterpret_cast<float *>(lite_norm_mat_cut.data_ptr_);
  // Copy dataHWC to the model input tensor.
  memcpy(inTensor.MutableData(), dataHWC,
         inputDims.channel * inputDims.width * inputDims.height * sizeof(float));
  std::vector<mindspore::MSTensor> outputs;
  // After the model and image tensor data is loaded, run inference.
  auto status = mModel->Predict(msInputs, &outputs);

  if (!status.IsOk()) {
    //MS_PRINT("MindSpore run net error.");
    return NULL;
  }

  /**
   * Get the MindSpore inference results.
   * Return the map of output node name and MindSpore Lite MSTensor.
   */
  auto names = mModel->GetOutputTensorNames();
  std::unordered_map<std::string, mindspore::MSTensor> msOutputs;
  for (const auto &name : names) {
    auto temp_dat = mModel->GetOutputByTensorName(name);
    msOutputs.insert(std::pair<std::string, mindspore::MSTensor>{name, temp_dat});
  }

  std::string resultStr = ProcessRunnetResult(::RET_GARBAGE_DETAILED_SUM,
                                              ::labels_name_grbage_detailed_map, msOutputs);

  const char *resultCharData = resultStr.c_str();
  return (env)->NewStringUTF(resultCharData);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_mindspore_classification_gallery_classify_TrackingMobile_unloadModel(JNIEnv *env,
                           jclass type,
                           jlong netEnv) {
 // MS_PRINT("MindSpore release net.");
  void **labelEnv = reinterpret_cast<void **>(netEnv);
  if (labelEnv == nullptr) {
   // MS_PRINT("MindSpore error, labelEnv is a nullptr.");
  }
  MSNetWork *labelNet = static_cast<MSNetWork *>(*labelEnv);

  labelNet->ReleaseNets();

  return (jboolean) true;
}
