#include<graphics.h>
#include<conio.h>
#include <graphics.h>
#include <fstream>
#include <string>
#include <graphics.h>
#include <fstream>
#include <string>
#include <cstdio>

#include <graphics.h>
#include <fstream>
#include <string>
using namespace std;
int x = 0;
int y = 0;
#include <graphics.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <graphics.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <graphics.h>

using namespace std;

void drawText(const char* text, int x, int y) {
    outtextxy(x, y, text);
}

int main() {
    char pic1[] = "pic1.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
    initgraph(800, 600);
    putimage(0, 0, &img_1);

    settextcolor(RGB(255, 255, 255)); // 设置文本颜色
    settextstyle(20, 0, "宋体");      // 设置文本样式

    ifstream file("数据.txt");
    if (file.is_open()) {
        int x = 50; // 起始横坐标
        int y = 50; // 起始纵坐标

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string courseID;
            int credits;
            vector<string> prerequisites;

            iss >> courseID >> credits;
            string prereq;
            while (iss >> prereq) {
                prerequisites.push_back(prereq);
            }

            char text[100];
            if (prerequisites.empty()) {
                sprintf(text, "课程号: %s          学分: %d", courseID.c_str(), credits);
            } else {
                sprintf(text, "课程号: %s          学分: %d         先修课程: ", courseID.c_str(), credits);
                for (const string& prereq : prerequisites) {
                    strcat(text, prereq.c_str());
                    strcat(text, " ");
                }
            }

            drawText(text, x, y);
            y += 30; // 增加纵坐标以绘制下一行
        }

        file.close();
    } else {
        drawText("无法打开数据.txt文件", x, y); // 如果文件无法打开，显示错误消息
    }

    getch();
    closegraph();
    return 0;
}








