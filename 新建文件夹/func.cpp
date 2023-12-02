#include "func.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "string.h"
#include <stack>
#include<graphics.h>
#include<conio.h>
#include <windows.h>

#include<graphics.h>
#include<conio.h>
#include <graphics.h>
#include <fstream>
#include <string>
#include <graphics.h>
#include <fstream>
#include <string>
#include <cstdio>




#include <windows.h>

#include <graphics.h>
#include <fstream>
#include <string>
#include <winsock.h>
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
#include <windows.h>
using namespace std;




//struct users
//{
//	char pwd[20] = {0};
//	char name[20] = {0};
//	int id = 0;
//	int score = 0;
//};
//
//char pic1[] = "pic1.png";
//IMAGE img_1;




extern VexNode result1[100];
extern VexNode result2[100];
extern VexNode result3[100];
extern VexNode result4[100];
extern Class_arrange_Graph G;



const char* getComputerScienceCourse(int courseCode) {
    switch (courseCode) {
        case 0:
            return "Computer_Science";
        case 1:
            return "Data_Structures";
        case 2:
            return "Algorithms";
        case 3:
            return "Computer_Architecture";
        case 4:
            return "Operating_Systems";
        case 5:
            return "Database_Management_Systems";
        case 6:
            return "Advanced_Database_Systems";
        case 7:
            return "Algorithms_and_Data_Structures";
        case 8:
            return "Computer_Networks";
        case 9:
            return "Network_Security";
        case 10:
            return "Software_Engineering";
        case 11:
            return "Artificial_Intelligence";
        case 12:
            return "Machine_Learning";
        case 13:
            return "Computer_Vision";
        default:
            return "Invalid_Course_Code";
    }
}

void mainmenu()
{

    char key;  
	char pic1[] = "bak1.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
    initgraph(1200, 900);
    putimage(0, 0, &img_1);
	settextcolor(RGB(255, 255, 255)); // 设置文本颜色
	settextstyle(35, 0, "宋体");      // 设置文本样式
	char text[100];
	sprintf(text, "欢迎使用课程编排系统");
outtextxy(100, 100, "欢迎使用工大课程编排系统 Welcome Course Scheduling System"); // Display welcome message
	settextstyle(30, 0, "宋体");      // 设置文本样式
outtextxy(100, 200, "1. 查看课程信息 View Course Information"); // Display option 1
outtextxy(100, 300, "2. 修改课程信息 Modify Course Information"); // Display option 2
outtextxy(100, 400, "3. 均匀安排课程 Schedule Courses Evenly"); // Display option 3
outtextxy(100, 500, "4. 尽快安排课程 Schedule Courses ASAP"); // Display option 4
outtextxy(100, 600, "5. 关闭程序 Close Program"); // Display option 5


    
    
	

    key=getch();
    key=key-'0';
    closegraph();
    switch(key)
    {
	case 1:		system("cls");
			cleardevice();
			Print_message();
			break;

	case 2:		system("cls");
			Adjust_message();
			break;

	case 3:		system("cls");
			Arrange_Selete(1);
			break;

	case 4:		system("cls");
			Arrange_Selete(0);
			break;

	case 5:		exit(0);

	default :
			cout << "该选项无效,请按任意键回主菜单" << endl;
			key=getch();
			system("cls");
			break;
    }

	mainmenu();
}



int Locate(char* ch)		
{
	return (2 == strlen(ch)) ? ch[1] - '1' : (ch[1] - '0') * 10 + ch[2] - '1';
}



void Read_file()
{
	FILE* fp = fopen("数据.txt", "r");
	if (NULL == fp)
	{
		printf("这个未找到文件,可能文件路径有误！！！");
		exit(1);
	}

	G.mes=(Message*)malloc(sizeof(Message));

	fscanf(fp,"%d%d%d",&G.mes->term_num,&G.mes->max_credit,&G.VexNum); 	//璇诲彇瀛︽湡鏁帮紝姣忓鏈熸渶澶у鍒嗭紝璇剧▼鎬绘暟
	if(G.VexNum > MaxClass || G.mes->term_num > MaxTerm || G.mes->max_credit > MaxCredit)
	{
		cout << "课程总数或学期数目或每学期最大学分超过上限" <<endl;
		fclose(fp);
		exit(1);
	}

	G.Vex = (VexNode*)malloc(sizeof(VexNode) * G.VexNum);
	int i=0;

	for(;i<G.VexNum;i++)
		G.Vex[i].FirstArc=nullptr;

	for (i = 0; i < G.VexNum; i++)		//璇诲彇璇剧▼淇℃伅
	{
		fscanf(fp, "%s%d", G.Vex[i].data,&G.Vex[i].credit);		//璇诲彇璇剧▼鍚嶇О鍜屽鍒?

		while ('\n' != fgetc(fp)) {		//鏍规嵁鍏堜慨璇剧▼寤虹珛閭绘帴琛ㄧ粨鐐?
			char str[4];
			int s;
			fscanf(fp, "%s", str);
			s = Locate(str);
			if (s < 0 || s > G.VexNum) {		//鍒ゆ柇璇剧▼鏄惁鏈夐敊璇?
				printf("%s课程错误，本专业无其先修课程！\n", G.Vex[i].data);
				fclose(fp);
				exit(1);
			}
			AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));		//鏇存柊閭绘帴琛ㄧ粨鐐?
			p->AdjVex = s;
			p->Next = G.Vex[i].FirstArc;
			G.Vex[i].FirstArc = p;
			G.ArcNum++;
		}
	}
	fclose(fp);

	AdjVexNode * p;
	for (i=0; i<G.VexNum; i++)		//鍒濆鍖栧叆搴?
		G.Vex[i].In_degree=0;
	for(i=0;i<G.VexNum;i++)
	{
		p=G.Vex[i].FirstArc;
		while(p!=nullptr)
		{
			G.Vex[p->AdjVex].In_degree++;
			p=p->Next;
		}
	}

}

void drawText(const char* text, int x, int y) {
    outtextxy(x, y, text);
}

void Print_message()
{
	
	// 绘制学期总数、每学期最大学分和必修课程数量
	char pic1[] = "bak2.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
	initgraph(1200, 900);
	
    putimage(0, 0, &img_1);

    settextcolor(RGB(255, 255, 255)); // 设置文本颜色
    // 减小字号
	settextstyle(35, 0, "宋体");

	outtextxy(100, 100, ("学期总数: " + std::to_string(G.mes->term_num)).c_str());
	outtextxy(350, 100, ("每学期最大学分: " + std::to_string(G.mes->max_credit)).c_str());
	outtextxy(700, 100, ("必修课程数量: " + std::to_string(G.VexNum)).c_str());



outtextxy(100, 150, "北京工业大学计算机系提供课程:");

int y = 200; // 用于垂直定位文本

char courseInfo[256]; // 初始化课程信息字符串
	settextstyle(24, 0, "宋体");
for (int i = 0; i < G.VexNum; i++) {
    snprintf(courseInfo, sizeof(courseInfo), "课程%d：%s 学分：%d 先修课程：", i+1, getComputerScienceCourse(i+1), G.Vex[i].credit);

    for (AdjVexNode* p = G.Vex[i].FirstArc; p != nullptr; p = p->Next) {
        char preCourse[16];
        snprintf(preCourse, sizeof(preCourse), "%s ", getComputerScienceCourse(p->AdjVex + 1));
        strncat(courseInfo, preCourse, sizeof(courseInfo) - strlen(courseInfo) - 1);
    }

    // 输出课程信息，包括先修课程的值
    outtextxy(100, y, courseInfo);

    y += 53; // 减小垂直位置下移的间距
}


	

    getch();
    closegraph();

	mainmenu();

//	printf("学期总数 :  %d \t",G.mes->term_num);
//	printf("每学期最大学分 ： %d \t",G.mes->max_credit);
//	printf("必修课程数量 ：   %d \n",G.VexNum);
//
//	cout << "\n\t\t\t本专业提供课程：\n";
//	for(int i=0;i<G.VexNum;i++)		//寰幆涓嶅仠
//	{	printf("______________________________________________________________________\n");
//		printf("课程号：C%d\t\t学分 ： %d\t\t先修课程： ",i+1,G.Vex[i].credit);
//		for (AdjVexNode* p = G.Vex[i].FirstArc; p!=nullptr; p = p->Next)
//			printf("C%d  ",p->AdjVex+1);
//		printf("\n");
//	}
//
//	cout << "\n\t\t\t\t按任意键回主菜单" <<endl;
//	getch();
//	system("cls");
//	mainmenu();

}


void Adjust_message()
{
	char pic1[] = "bak3.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
	initgraph(1200, 900);
	
    putimage(0, 0, &img_1);
    settextcolor(RGB(255, 255, 255)); // 设置文本颜色
	settextstyle(40, 0, "宋体");      // 设置文本样式
	char text[100];
	sprintf(text, "允许修改的内容有: 1.学期总数  2.个人每学期最大学分");
		outtextxy(100, 100,"在这里你可以选择修改学期\学分信息："); // 在图像上方显示文本
settextstyle(30, 0, "宋体");
	outtextxy(100, 250, "一、允许修改的内容有: 1.学期总数  2.个人每学期最大学分"); // 在图像上方显示文本
	outtextxy(100, 350, "二、使用鼠标选择要修改的内容 ,或按其他键取消修改"); // 在图像上方显示文本
	
	//outtextxy(100, 200, "1. 查看课程信息"); // 显示选项1
	//outtextxy(100, 250, "2. 修改课程信息"); // 显示选项2
	
	printf("允许修改的内容有: 1.学期总数  2.个人每学期最大学分 ");
	printf("\n\n请选择要修改的内容 ,或按其他键取消修改\n\n");
	int result = MessageBoxA(NULL, "请选择要修改的内容:\n1. 学期总数（选择是[Y]）\n2. 个人每学期最大学分（选择否[N]）", "修改选项", MB_ICONINFORMATION | MB_YESNO);




	//char key=getch();
//	key=key-'0';

	if(result == IDYES)
	{	int term;
		outtextxy(100, 450, "请输入学期总数"); // 在图像上方显示文本
		printf("请输入学期总数：");
		scanf("%d",&term);
		char term_str[10];
        sprintf(term_str, "你输入的学期总数是：%d", term);
        outtextxy(100, 550, term_str);
		if(term > MaxTerm || term < 1)
		{
		
		G.mes->term_num=term;
		outtextxy(100, 650, "修改成功"); // 在图像上方显示文本
		outtextxy(100, 700, "按任意键回主菜单"); // 在图像上方显示文本
		cout << "\n修改成功\n" <<endl;
		cout << "按任意键回主菜单" <<endl;
		File_Update();
		getch();
		}
		
		else{
		
		
			outtextxy(100, 650, "输入的学期数不合法 (大于最大允许的学期数 或 小于1 或 不是正整数"); // 在图像上方显示文本
			outtextxy(100,700, "请按任意键回主菜单"); // 在图像上方显示文本
			cout << "\n输入的学期数不合法 (大于最大允许的学期数 或 小于1 或 不是正整数)\n" <<endl;
			cout<< "请按任意键回主菜单"<< endl;
			getch();
			system("cls");
			mainmenu();
		}
	}
	else if(result == IDNO)
	{
		
		int credit;
		outtextxy(100, 450, "输入个人每学期最大学分："); // 在图像上方显示文本
		printf("请输入个人每学期最大学分：");
		scanf("%d",&credit);
		char term_str[10];
        sprintf(term_str, "你输入的个人每学期最大学分是：%d", credit);
        outtextxy(100, 550, term_str);
		if( credit < 1 || credit > MaxCredit)
		{
			outtextxy(100, 650, "输入的学分数不合法 (小于1或大于30)"); // 在图像上方显示文本
			outtextxy(100, 700, "请按任意键回主菜单"); // 在图像上方显示文本
			cout << "\n输入的学分数不合法 (小于1或大于30)\n" <<endl;
			cout<< "请按任意键回主菜单"<< endl;
			getch();
			system("cls");
			mainmenu();
		}
		else{
			outtextxy(100, 650, "输入的学分数不合法 (小于1或大于30)"); // 在图像上方显示文本
			outtextxy(100, 700, "请按任意键回主菜单"); // 在图像上方显示文本
			cout << "\n输入的学分数不合法 (小于1或大于30)\n" <<endl;
			cout<< "请按任意键回主菜单"<< endl;
			getch();
			system("cls");
			mainmenu();
		} 
		G.mes->max_credit=credit;
		outtextxy(100, 650, "修改成功"); // 在图像上方显示文本
		outtextxy(100, 700, "按任意键回主菜单"); // 在图像上方显示文本
		cout << "\n修改成功\n" <<endl;
		cout << "按任意键回主菜单" <<endl;
		File_Update();
		getch();
	}
	

 		closegraph();
		system("cls");
		mainmenu();

}



void File_Update()
{
	ofstream ofs;
	ofs.open("./数据.txt",ios::in | ios::out | ios::binary);

	ofs << G.mes->term_num << " "<< G.mes->max_credit << " " << G.VexNum << "\n" ;
	ofs.close();
}


void Arrange_Selete(int choice)
{
	Top_Sort(result1,0);
	Top_Sort(result2,1);
	Top_Sort(result3,2);
	Top_Sort(result4,3);
	char pic1[] = "pic1.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
	initgraph(1800, 1800);

    putimage(0, 0, &img_1);
    settextcolor(RGB(255, 255, 255)); // 设置文本颜色
	settextstyle(20, 0, "宋体");      // 设置文本样式
	Print_Top_Sort_Result();
	outtextxy(100, 500, "请输入你选择的课程安排先后顺序："); // 在图像上方显示文本
	cout << "\n\n\n请输入你选择的课程安排先后顺序：";
	
		
	char key=getch();
//	int input = static_cast<int>(key); 
//		char term_str[10];
//        sprintf(term_str, "你选择的课程安排位次是：%d-------", input);
//        outtextxy(100, 550, term_str);
	 std::string inputString = "你选择的课程安排位次是: ";
    inputString += key;

    // 将组合后的字符串显示在图像上
    outtextxy(100, 550, inputString.c_str());
    	getch();
	if(key=='1')
		Arrange(result1,choice);
	else if(key=='2')
		Arrange(result2,choice);
	else if(key=='3')
		Arrange(result3,choice);
	else if(key=='4')
		Arrange(result4,choice);
	else
	{
		outtextxy(100, 600, "选择有误，请按任意键回主菜单"); // 在图像上方显示文本
		cout<<"选择有误，请按任意键回主菜单";
		getch();
		mainmenu();
	}

}

void printToGraphics(const char* str, int x, int y) {
    outtextxy(x, y, str);
}

void Arrange(VexNode *result,int choice)
{
	
	char pic1[] = "pic1.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
	initgraph(1800, 1800);

    putimage(0, 0, &img_1);
    settextcolor(RGB(255, 255, 255)); // 设置文本颜色
	settextstyle(20, 0, "宋体");      // 设置文本样式
	system("cls");
	FILE *fp=fopen("./各学期课程安排结果.txt","w");
	int i=0,j,k,course_num,per_max_num,Sumcredit,tag;

	if(choice==0)
		per_max_num=G.VexNum;
	else
	{	if(G.VexNum % G.mes->term_num == 0 || G.VexNum % G.mes->term_num <  G.mes->term_num/2 )
			per_max_num = G.VexNum/G.mes->term_num;
		else
			per_max_num = (G.VexNum/G.mes->term_num+1);
	}

	VexNode this_term_courses[G.VexNum];
	AdjVexNode* p;
//	for(k=0;k<G.VexNum;k++)
//	{
//		if(i==G.VexNum)	break;
//		
//		 
//	 	char buffer[100];
//
//		sprintf(buffer, "\n第%d个学期的课程为：", k + 1);
//
//// Assuming the second and third arguments of printToGraphics are x and y coordinates
//		printToGraphics(buffer, 100, 100 + k * 30);
//        
//        
//        
//		fprintf(fp, "\n第%d个学期的课程为：", k+1);
//		printf("\n第%d个学期的课程为：", k + 1);
//		Sumcredit=0;       //本学期安排课程的总学分
//		course_num=0;	 //本学期安排课程的总数
//		p=result[i].FirstArc;  //先修课指针
//		tag=0;          //标志本学期是否有该课程的先修课程
//		while(Sumcredit + result[i].credit <= G.mes->max_credit  && tag==0 && course_num<per_max_num)
//		{
//			while(p!=nullptr && tag==0)
//			{
//				for(j=0;j<course_num;j++)
//				{
//					if(p->AdjVex == Locate(this_term_courses[j].data) )
//					{
//						tag=1;
//						break;
//					}
//				}
//				p=p->Next;
//			}
//
//			if(tag==1) break;
//			
//			char courseBuffer[100];
//            sprintf(courseBuffer, " %s ", result[i].data);
//    // Adjust the vertical position to avoid overlap
//    		printToGraphics(courseBuffer, 100, 120 + k * 20 + course_num * 30);
//
//            
//			fprintf(fp, " %s ", result[i].data);
//			printf( " %s ", result[i].data);
//			Sumcredit+=result[i].credit;
//			this_term_courses[course_num]=result[i];
//			if(i==G.VexNum)	break;
//			i++;
//			course_num++;
//			p=result[i].FirstArc;
//		}
//
//	}
for (k = 0; k < G.VexNum; k++) {
    if (i == G.VexNum) break;

    char buffer[100];
//    sprintf(buffer, "第%d个学期安排的课程为：", k + 1);
//    printToGraphics(buffer, 100, 100 + k * 30);
	sprintf(buffer, "第%d个学期安排的课程为：", k + 1);

    // 调整垂直位置以避免重叠
    outtextxy(100, 100 + k * 30, buffer);
    fprintf(fp, "第%d个学期安排的课程为：", k + 1);
    printf("第%d个学期安排的课程为：", k + 1);
    Sumcredit = 0;       // 本学期安排课程的总学分
    course_num = 0;      // 本学期安排课程的总数
    p = result[i].FirstArc;  // 先修课指针
    tag = 0;             // 标志本学期是否有该课程的先修课程
	int count = 0;
    while (Sumcredit + result[i].credit <= G.mes->max_credit && tag == 0 && course_num < per_max_num) {
    	count++;
        while (p != nullptr && tag == 0) {
            for (j = 0; j < course_num; j++) {
                if (p->AdjVex == Locate(this_term_courses[j].data)) {
                    tag = 1;
                    break;
                }
            }
            p = p->Next;
        }

        if (tag == 1) break;

        // 输出课程信息
       outtextxy(350+ count*30,  100 + (k) * 30  , getComputerScienceCourse(Locate(result[i].data)));



        fprintf(fp, " %s ", result[i].data);
        printf(" %s ", result[i].data);

        Sumcredit += result[i].credit;
        this_term_courses[course_num] = result[i];
        if (i == G.VexNum) break;
        i++;
        course_num++;
        p = result[i].FirstArc;
    }
    
    printf("\n");  // 换行，显示下一个学期的课程
    fprintf(fp, "\n");
}



	fclose(fp);

	if(k>G.mes->term_num)
	{
		fp=fopen("./各学期课程安排结果.txt","w");
		fprintf(fp,"%s","该课程安排先后顺序下，此策略无解,因为安排所需学期数超过最大学期数");
		fclose(fp);
		cout << "\n\n\n该课程安排先后顺序下，此策略无解,因为安排所需学期数超过最大学期数\n\n\n";
		cout <<"请按任意键回主菜单" <<endl;
		getch();
		system("cls");
		mainmenu();
	}

	cout << "\n\n\n 课程安排信息已经存入当前目录下，“各学期课程安排结果.txt” \n\n请按任意键回主菜单";
	getch();
	system("cls");
	mainmenu();

}




void Top_Sort(VexNode* result,int choice)
{
	int tag=0,i;
	AdjVexNode *  p;
	stack<VexNode> S;
	stack <AdjVexNode*> S1;
	Read_file();
	if(choice==0)

		while(tag==0)
		{
			tag=1;
			for(i=G.VexNum-1;i>=0;i--)
				if(G.Vex[i].In_degree==0)
				{
					S.push(G.Vex[i]);
					G.Vex[i].In_degree--;
					p=G.Vex[i].FirstArc;
					S1.push(p);
					tag=0;
				}

			while(S1.empty()==false)
			{	p=S1.top();
				S1.pop();

				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}
			}
		}



	else if(choice==1)

		while(tag==0)
		{
			tag=1;
			for(i=0;i<G.VexNum;i++)
				if(G.Vex[i].In_degree==0)
				{
					S.push(G.Vex[i]);
					G.Vex[i].In_degree--;
					p=G.Vex[i].FirstArc;
					S1.push(p);
					tag=0;
				}

			while(S1.empty()==false)
			{	p=S1.top();
				S1.pop();

				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}
			}
		}



	else if(choice==2)

		for(i=G.VexNum-1;i>=0;i--)
		{
			if(G.Vex[i].In_degree==0)
			{
				S.push(G.Vex[i]);
				G.Vex[i].In_degree--;
				p=G.Vex[i].FirstArc;
				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}

				i=G.VexNum-1;
			}
		}



	else

		for(i=0;i<G.VexNum;i++)
		{
			if(G.Vex[i].In_degree==0)
			{
				S.push(G.Vex[i]);
				G.Vex[i].In_degree--;
				p=G.Vex[i].FirstArc;
				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}

				i=-1;
			}
		}




	i=S.size();

	if(i <G.VexNum)
	{
		cout<< "拓扑排序失败，课程先修关系可能存在环路，请按任意键回主菜单\n";
		getch();
		system("cls");
		mainmenu();
	}

	for(i=0;i<G.VexNum;i++)
	{
		if(S.empty()==false)
		{
			result[i]=S.top();
			S.pop();
		}
		else
		{
			cout << "拓扑排序弹栈失败,请按任意键回主菜单" << endl;
			getch();
			mainmenu();
		}

	}
}



void Print_Top_Sort_Result()
{
	char pic1[] = "pic1.png";
    IMAGE img_1;
    loadimage(&img_1, pic1);
	initgraph(1800, 1800);
	
    putimage(0, 0, &img_1);
    settextcolor(RGB(255, 255, 255)); // 设置文本颜色
	settextstyle(20, 0, "宋体");      // 设置文本样式

	
	
	
	printf("各课程安排先后顺序为:\n");
	cout << "选择1：" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result1[i].data<< "  " ;
	}

	cout << "\n\n选择2：" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result2[i].data<< "  " ;
	}

	cout << "\n\n选择3：" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result3[i].data<< "  " ;
	}

	cout << "\n\n选择4：" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result4[i].data<< "  " ;
	}	
	    // 在图形窗口中显示文本
    outtextxy(100, 50, "各课程代号安排先后顺序为:___________________");
    outtextxy(100, 100, "（1）可供参考的排序选择一:");
    outtextxy(100, 200, "（2）可供参考的排序选择二:");
    outtextxy(100, 300, "（3）可供参考的排序选择三:");
    outtextxy(100, 400, "（4）可供参考的排序选择四:");

    // 选择1
   for (int i = 0; i <  G.VexNum; i++) {
        // 使用 std::string 构造函数处理字符数组
        std::string data_str(result1[i].data, result1[i].data + sizeof(result1[i].data));
        outtextxy(150 + i * 30, 150,data_str.c_str());
    }

    for (int i = 0; i <  G.VexNum; i++) {
        std::string data_str(result2[i].data, result2[i].data + sizeof(result2[i].data));
        outtextxy(150 + i * 30, 250, data_str.c_str());
    }

    for (int i = 0; i <  G.VexNum; i++) {
        std::string data_str(result3[i].data, result3[i].data + sizeof(result3[i].data));
        outtextxy(150 + i * 30, 350, data_str.c_str());
    }

    for (int i = 0; i <  G.VexNum; i++) {
        std::string data_str(result4[i].data, result4[i].data + sizeof(result4[i].data));
        outtextxy(150 + i * 30, 450, data_str.c_str());
    }


 
 
 
    

}





void titlepage() {
	float H = 50;
	float S = 1;
	float L = 0.48f;
	char pic1[] = "pic1.png";
    IMAGE img_1;
	putimage(0, 0, &img_1);
	setbkcolor(WHITE);
	clearrectangle(50, 300, 450, 550);
	setbkcolor(RGB(0,191,255));
	clearrectangle(55, 305, 445, 545);
	setbkcolor(YELLOW);                                            //文本框
	clearrectangle(160, 470, 410, 510);
	clearrectangle(160, 410, 410, 450);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(254, 241, 67));
	settextstyle(120, 0, _T("黑体"));

	settextcolor(RGB(220, 105, 36));

	settextcolor(BLACK);
	settextstyle(16, 0, _T("黑体"));
	outtextxy(116, 415, _T("账号："));
	outtextxy(116, 475, _T("密码："));
	settextcolor(RGB(254, 241, 67));
	settextstyle(40, 0, _T("黑体"));
	outtextxy(75, 325, _T("工大教学管理系统"));
	settextcolor(RGB(162, 178, 194));
	settextstyle(12, 0, _T("宋体"));
	outtextxy(160, 420, _T(" 输入（3-18）位账号"));
	outtextxy(160, 480, _T(" 输入（6-18）位密码"));
}


char* registers(users** player) {
	char username[18] = { 0 };
	char password[18] = { 0 };
	char password2[18] = { 0 };
	MOUSEMSG m;
	FILE* fp;
	int a = 0;
	if ((fp = fopen("rec.txt", "r")) == NULL) {
		settextcolor(RGB(220, 105, 36));
		settextstyle(16, 0, _T("黑体"));
		outtextxy(20, 150, _T("游戏文件异常,请检查文件完整性"));
	}
	int x0 = 0;
	char c = 1;
	settextcolor(BLACK);
	setbkcolor(WHITE);

	clearrectangle(160, 410, 410, 450);
	for (int x = 0; c != 13 && x <= 18; x++) {//录入用户名

		setbkcolor(BLACK);
		clearrectangle(0, 0, 5, 5);
		while (!a) {//输入位置闪烁
			while (MouseHit()) {
				m = GetMouseMsg();

				if (m.mkLButton == 1) {


				}

			}
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(157 + 13 * x, 420, '|');
			}
			if (clock() / 500 % 2 == 1) {
				setbkcolor(WHITE);
				clearrectangle(160 + 13 * x, 410, 162 + 13 * x, 450);
			}
			a = _kbhit();
		}

		setbkcolor(WHITE);
		clearrectangle(160 + 13 * x, 410, 162 + 13 * x, 450);

		c = _getch();
		if (x < 18 && c != 8) {//非退格输入
			username[x] = c;
		}
		if (c == 8 && x == 0) {//无字时退格输入
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//有字时退格输入
			x = x - 1;
			username[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}

		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(16, 0, _T("黑体"));
			outtextxy(163 + 13 * x, 420, c);
		}

		FlushMouseMsgBuffer();

		a = 0;
		if (x == 18) {
			x--;
		}
		x0 = x;
	}
	if (x0 < 3) {
		titlepage();
		settextcolor(BLACK);
		settextstyle(16, 0, _T("黑体"));
		outtextxy(163, 440, _T("用户名太短！"));
		fclose(fp);
		return NULL;
	}
	c = 1;


	clearrectangle(160, 470, 410, 510);
	for (int x = 0; c != 13; x++) {
		while (!a) {//输入位置闪烁
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(157 + 13 * x, 480, '|');
			}
			if (clock() / 500 % 2 == 1) {
				setbkcolor(WHITE);
				clearrectangle(160 + 13 * x, 470, 162 + 13 * x, 510);
			}
			a = _kbhit();
		}
		setbkcolor(WHITE);
		clearrectangle(160 + 13 * x, 470, 162 + 13 * x, 510);
		c = _getch();
		if (x < 18 && c != 8) {
			password[x] = c;
		}
		if (c == 8 && x == 0) {//无字时退格输入
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//有字时退格输入
			x = x - 1;
			password[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(20, 0, _T("黑体"));
			outtextxy(163 + 13 * x, 480, '*');
		}
		a = 0;
		if (x == 18) {
			x--;
		}
		x0 = x;
	}
	if (x0 < 3) {
		titlepage();
		settextcolor(BLACK);
		settextstyle(16, 0, _T("黑体"));
		outtextxy(163, 440, _T("密码太短！"));
		fclose(fp);
		return NULL;
	}
	c = 1;
	clearrectangle(160, 470, 410, 510);
	settextstyle(16, 0, _T("黑体"));
	outtextxy(116 - 32, 475, _T("确认"));
	for (int x = 0; c != 13; x++) {
		while (!a) {//输入位置闪烁
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(157 + 13 * x, 480, '|');
			}
			if (clock() / 500 % 2 == 1) {
				setbkcolor(WHITE);
				clearrectangle(160 + 13 * x, 470, 162 + 13 * x, 510);
			}
			a = _kbhit();
		}
		setbkcolor(WHITE);
		clearrectangle(160 + 13 * x, 470, 162 + 13 * x, 510);
		c = _getch();
		if (x < 18 && c != 8) {
			password2[x] = c;
		}
		if (c == 8 && x == 0) {//无字时退格输入
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//有字时退格输入
			x = x - 1;
			password2[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(20, 0, _T("黑体"));
			outtextxy(163 + 13 * x, 480, '*');
		}
		if (x == 18) {
			x--;
		}
		a = 0;
	}
	if (strncmp(password, password2, 18) != 0) {
		titlepage();
		settextcolor(BLACK);
		settextstyle(16, 0, _T("黑体"));
		outtextxy(163, 440, _T("两次输入密码不同，请重试！"));
		fclose(fp);
		return NULL;
	}
	int id = 0;
	int x = 0;

	if (fp != 0) {
		users b;
		(*player) = (users*)malloc(sizeof(users));
		if ((*player) != NULL) {
			(*player)->name[20] = { 0 };
			(*player)->pwd[20] = { 0 };
			(*player)->id = 0;
			(*player)->score = 0;
		}
		fread(&b, sizeof(struct users), 1, fp);
		strcpy((*player)->name, username);
		strcpy((*player)->pwd, password);
		while (1)

		{
			if (strcmp((*player)->name, b.name)) /*如果两串不相等*/
			{
				if (!feof(fp))    /*如果未到文件尾*/
				{
					fread(&b, sizeof(struct users), 1, fp);
					x++;
					id = x;
				}
				else
					break;
			}
			else
			{
				titlepage();
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(163, 440, _T("此用户名已存在！请重新注册！"));
				fclose(fp);
				return NULL;
			}

		}
		(*player)->id = id;
		(*player)->score = 100;
		fp = fopen("rec.txt", "a");
		if ((*player) != 0) {
			fwrite((*player), sizeof(struct users), 1, fp);
		}
		fclose(fp);
		return (*player)->name;
	}
	return NULL;
}
char* login(users** player) {
	char username[18] = { 0 };
	char password[18] = { 0 };
	FILE* fp;
	MOUSEMSG m;
	int a = 0;
	if ((fp = fopen("rec.txt", "r")) == NULL) {
		settextcolor(RGB(220, 105, 36));
		settextstyle(16, 0, _T("黑体"));
		outtextxy(20, 150, _T("游戏文件异常,请检查文件完整性"));
	}
	char c = 1;
	settextcolor(BLACK);
	setbkcolor(WHITE);

	clearrectangle(160, 410, 410, 450);
	for (int x = 0; c != 13 && x <= 18; x++) {//录入用户名

		while (!a) {//输入位置闪烁


			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(157 + 13 * x, 420, '|');
			}
			if (clock() / 500 % 2 == 1) {
				setbkcolor(WHITE);
				clearrectangle(160 + 13 * x, 410, 162 + 13 * x, 450);
			}
			a = _kbhit();
		}

		setbkcolor(WHITE);
		clearrectangle(160 + 13 * x, 410, 162 + 13 * x, 450);

		c = _getch();
		if (x < 18 && c != 8) {//非退格输入
			username[x] = c;
		}
		if (c == 8 && x == 0) {//无字时退格输入
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//有字时退格输入
			x = x - 1;
			username[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}

		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(16, 0, _T("黑体"));
			outtextxy(163 + 13 * x, 420, c);
		}

		FlushMouseMsgBuffer();

		a = 0;
		if (x == 18) {
			x--;
		}
	}

	c = 1;
	clearrectangle(160, 470, 410, 510);
	for (int x = 0; c != 13; x++) {
		while (!a) {//输入位置闪烁
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(157 + 13 * x, 480, '|');
			}
			if (clock() / 500 % 2 == 1) {
				setbkcolor(WHITE);
				clearrectangle(160 + 13 * x, 470, 162 + 13 * x, 510);
			}
			a = _kbhit();
		}
		setbkcolor(WHITE);
		clearrectangle(160 + 13 * x, 470, 162 + 13 * x, 510);
		c = _getch();
		if (x < 18 && c != 8) {
			password[x] = c;
		}
		if (c == 8 && x == 0) {//无字时退格输入
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//有字时退格输入
			x = x - 1;
			password[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(20, 0, _T("黑体"));
			outtextxy(163 + 13 * x, 480, '*');
		}
		if (x == 18) {
			x--;
		}
		a = 0;
	}


	if (fp != 0) {
		users  b;
		(*player) = (users*)malloc(sizeof(users));
		(*player)->name[20] = { 0 };
		(*player)->pwd[20] = { 0 };
		fread(&b, sizeof(struct users), 1, fp);
		strcpy((*player)->name, username);
		strcpy((*player)->pwd, password);
		while (1)
		{
			if (strcmp((*player)->name, b.name) == 0)         //如果有此用户名
			{
				break;
			}
			else
			{
				if (!feof(fp))  //如果文件没有读完                            
				{
					fread(&b, sizeof(struct users), 1, fp);
				}
				else
				{
					titlepage();
					settextcolor(BLACK);
					settextstyle(16, 0, _T("黑体"));
					outtextxy(163, 440, _T("用户名不存在！请重新登录！"));
					fclose(fp);
					return NULL;
				}
			}
		}
		do {
			if (strcmp((*player)->pwd, b.pwd) == 0)            /*如果密码匹配*/
			{
				(*player)->score = b.score;
				fclose(fp);
				return  (*player)->name;
			}
			else
			{
				titlepage();		
				settextcolor(BLACK);
				settextstyle(16, 0, _T("黑体"));
				outtextxy(163, 440, _T("密码不正确!请重新登录！"));
				fclose(fp);
				return NULL;
			}
		} while (strcmp((*player)->pwd, b.pwd) == 0);
	}
	return NULL;
}

void showgui() {
	setbkcolor(WHITE);
	clearrectangle(470, 355, 530, 395);
	setbkcolor(RGB(124, 75, 0));
	clearrectangle(473, 358, 527, 392);
	setbkcolor(WHITE);
	clearrectangle(470, 425, 530, 465);
	setbkcolor(RGB(124, 75, 0));
	clearrectangle(473, 428, 527, 462);
	settextcolor(YELLOW);
	settextstyle(16, 0, _T("黑体"));
	outtextxy(482, 368, _T("登录"));
	outtextxy(482, 438, _T("注册"));
}
void titlesystem(users** player) {
	int x = 0, y = 0, choose = 0;
	int a = 2;
	char* p = NULL;
	titlepage();
	showgui();
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > 470 && m.y > 355 && m.x < 530 && m.y < 395) {

				m.uMsg = 0; titlepage(); p = login(player);
				if (p != NULL) { return; }
				else { showgui(); }
			}
			if (m.x > 470 && m.y > 425 && m.x < 530 && m.y < 465) {

				m.uMsg = 0; titlepage(); p = registers(player);
				if (p != 0) { return; }
				else { showgui(); }
			}
		}
	}
}


