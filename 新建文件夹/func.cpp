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
	settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
	settextstyle(35, 0, "����");      // �����ı���ʽ
	char text[100];
	sprintf(text, "��ӭʹ�ÿγ̱���ϵͳ");
outtextxy(100, 100, "��ӭʹ�ù���γ̱���ϵͳ Welcome Course Scheduling System"); // Display welcome message
	settextstyle(30, 0, "����");      // �����ı���ʽ
outtextxy(100, 200, "1. �鿴�γ���Ϣ View Course Information"); // Display option 1
outtextxy(100, 300, "2. �޸Ŀγ���Ϣ Modify Course Information"); // Display option 2
outtextxy(100, 400, "3. ���Ȱ��ſγ� Schedule Courses Evenly"); // Display option 3
outtextxy(100, 500, "4. ���찲�ſγ� Schedule Courses ASAP"); // Display option 4
outtextxy(100, 600, "5. �رճ��� Close Program"); // Display option 5


    
    
	

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
			cout << "��ѡ����Ч,�밴����������˵�" << endl;
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
	FILE* fp = fopen("����.txt", "r");
	if (NULL == fp)
	{
		printf("���δ�ҵ��ļ�,�����ļ�·�����󣡣���");
		exit(1);
	}

	G.mes=(Message*)malloc(sizeof(Message));

	fscanf(fp,"%d%d%d",&G.mes->term_num,&G.mes->max_credit,&G.VexNum); 	//读取学期数，每学期最大学分，课程总数
	if(G.VexNum > MaxClass || G.mes->term_num > MaxTerm || G.mes->max_credit > MaxCredit)
	{
		cout << "�γ�������ѧ����Ŀ��ÿѧ�����ѧ�ֳ�������" <<endl;
		fclose(fp);
		exit(1);
	}

	G.Vex = (VexNode*)malloc(sizeof(VexNode) * G.VexNum);
	int i=0;

	for(;i<G.VexNum;i++)
		G.Vex[i].FirstArc=nullptr;

	for (i = 0; i < G.VexNum; i++)		//读取课程信息
	{
		fscanf(fp, "%s%d", G.Vex[i].data,&G.Vex[i].credit);		//读取课程名称和学�?

		while ('\n' != fgetc(fp)) {		//根据先修课程建立邻接表结�?
			char str[4];
			int s;
			fscanf(fp, "%s", str);
			s = Locate(str);
			if (s < 0 || s > G.VexNum) {		//判断课程是否有错�?
				printf("%s�γ̴��󣬱�רҵ�������޿γ̣�\n", G.Vex[i].data);
				fclose(fp);
				exit(1);
			}
			AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));		//更新邻接表结�?
			p->AdjVex = s;
			p->Next = G.Vex[i].FirstArc;
			G.Vex[i].FirstArc = p;
			G.ArcNum++;
		}
	}
	fclose(fp);

	AdjVexNode * p;
	for (i=0; i<G.VexNum; i++)		//初始化入�?
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
	
	// ����ѧ��������ÿѧ�����ѧ�ֺͱ��޿γ�����
	char pic1[] = "bak2.png";

    IMAGE img_1;
    loadimage(&img_1, pic1);
	initgraph(1200, 900);
	
    putimage(0, 0, &img_1);

    settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
    // ��С�ֺ�
	settextstyle(35, 0, "����");

	outtextxy(100, 100, ("ѧ������: " + std::to_string(G.mes->term_num)).c_str());
	outtextxy(350, 100, ("ÿѧ�����ѧ��: " + std::to_string(G.mes->max_credit)).c_str());
	outtextxy(700, 100, ("���޿γ�����: " + std::to_string(G.VexNum)).c_str());



outtextxy(100, 150, "������ҵ��ѧ�����ϵ�ṩ�γ�:");

int y = 200; // ���ڴ�ֱ��λ�ı�

char courseInfo[256]; // ��ʼ���γ���Ϣ�ַ���
	settextstyle(24, 0, "����");
for (int i = 0; i < G.VexNum; i++) {
    snprintf(courseInfo, sizeof(courseInfo), "�γ�%d��%s ѧ�֣�%d ���޿γ̣�", i+1, getComputerScienceCourse(i+1), G.Vex[i].credit);

    for (AdjVexNode* p = G.Vex[i].FirstArc; p != nullptr; p = p->Next) {
        char preCourse[16];
        snprintf(preCourse, sizeof(preCourse), "%s ", getComputerScienceCourse(p->AdjVex + 1));
        strncat(courseInfo, preCourse, sizeof(courseInfo) - strlen(courseInfo) - 1);
    }

    // ����γ���Ϣ���������޿γ̵�ֵ
    outtextxy(100, y, courseInfo);

    y += 53; // ��С��ֱλ�����Ƶļ��
}


	

    getch();
    closegraph();

	mainmenu();

//	printf("ѧ������ :  %d \t",G.mes->term_num);
//	printf("ÿѧ�����ѧ�� �� %d \t",G.mes->max_credit);
//	printf("���޿γ����� ��   %d \n",G.VexNum);
//
//	cout << "\n\t\t\t��רҵ�ṩ�γ̣�\n";
//	for(int i=0;i<G.VexNum;i++)		//循环不停
//	{	printf("______________________________________________________________________\n");
//		printf("�γ̺ţ�C%d\t\tѧ�� �� %d\t\t���޿γ̣� ",i+1,G.Vex[i].credit);
//		for (AdjVexNode* p = G.Vex[i].FirstArc; p!=nullptr; p = p->Next)
//			printf("C%d  ",p->AdjVex+1);
//		printf("\n");
//	}
//
//	cout << "\n\t\t\t\t������������˵�" <<endl;
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
    settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
	settextstyle(40, 0, "����");      // �����ı���ʽ
	char text[100];
	sprintf(text, "�����޸ĵ�������: 1.ѧ������  2.����ÿѧ�����ѧ��");
		outtextxy(100, 100,"�����������ѡ���޸�ѧ��\ѧ����Ϣ��"); // ��ͼ���Ϸ���ʾ�ı�
settextstyle(30, 0, "����");
	outtextxy(100, 250, "һ�������޸ĵ�������: 1.ѧ������  2.����ÿѧ�����ѧ��"); // ��ͼ���Ϸ���ʾ�ı�
	outtextxy(100, 350, "����ʹ�����ѡ��Ҫ�޸ĵ����� ,��������ȡ���޸�"); // ��ͼ���Ϸ���ʾ�ı�
	
	//outtextxy(100, 200, "1. �鿴�γ���Ϣ"); // ��ʾѡ��1
	//outtextxy(100, 250, "2. �޸Ŀγ���Ϣ"); // ��ʾѡ��2
	
	printf("�����޸ĵ�������: 1.ѧ������  2.����ÿѧ�����ѧ�� ");
	printf("\n\n��ѡ��Ҫ�޸ĵ����� ,��������ȡ���޸�\n\n");
	int result = MessageBoxA(NULL, "��ѡ��Ҫ�޸ĵ�����:\n1. ѧ��������ѡ����[Y]��\n2. ����ÿѧ�����ѧ�֣�ѡ���[N]��", "�޸�ѡ��", MB_ICONINFORMATION | MB_YESNO);




	//char key=getch();
//	key=key-'0';

	if(result == IDYES)
	{	int term;
		outtextxy(100, 450, "������ѧ������"); // ��ͼ���Ϸ���ʾ�ı�
		printf("������ѧ��������");
		scanf("%d",&term);
		char term_str[10];
        sprintf(term_str, "�������ѧ�������ǣ�%d", term);
        outtextxy(100, 550, term_str);
		if(term > MaxTerm || term < 1)
		{
		
		G.mes->term_num=term;
		outtextxy(100, 650, "�޸ĳɹ�"); // ��ͼ���Ϸ���ʾ�ı�
		outtextxy(100, 700, "������������˵�"); // ��ͼ���Ϸ���ʾ�ı�
		cout << "\n�޸ĳɹ�\n" <<endl;
		cout << "������������˵�" <<endl;
		File_Update();
		getch();
		}
		
		else{
		
		
			outtextxy(100, 650, "�����ѧ�������Ϸ� (������������ѧ���� �� С��1 �� ����������"); // ��ͼ���Ϸ���ʾ�ı�
			outtextxy(100,700, "�밴����������˵�"); // ��ͼ���Ϸ���ʾ�ı�
			cout << "\n�����ѧ�������Ϸ� (������������ѧ���� �� С��1 �� ����������)\n" <<endl;
			cout<< "�밴����������˵�"<< endl;
			getch();
			system("cls");
			mainmenu();
		}
	}
	else if(result == IDNO)
	{
		
		int credit;
		outtextxy(100, 450, "�������ÿѧ�����ѧ�֣�"); // ��ͼ���Ϸ���ʾ�ı�
		printf("���������ÿѧ�����ѧ�֣�");
		scanf("%d",&credit);
		char term_str[10];
        sprintf(term_str, "������ĸ���ÿѧ�����ѧ���ǣ�%d", credit);
        outtextxy(100, 550, term_str);
		if( credit < 1 || credit > MaxCredit)
		{
			outtextxy(100, 650, "�����ѧ�������Ϸ� (С��1�����30)"); // ��ͼ���Ϸ���ʾ�ı�
			outtextxy(100, 700, "�밴����������˵�"); // ��ͼ���Ϸ���ʾ�ı�
			cout << "\n�����ѧ�������Ϸ� (С��1�����30)\n" <<endl;
			cout<< "�밴����������˵�"<< endl;
			getch();
			system("cls");
			mainmenu();
		}
		else{
			outtextxy(100, 650, "�����ѧ�������Ϸ� (С��1�����30)"); // ��ͼ���Ϸ���ʾ�ı�
			outtextxy(100, 700, "�밴����������˵�"); // ��ͼ���Ϸ���ʾ�ı�
			cout << "\n�����ѧ�������Ϸ� (С��1�����30)\n" <<endl;
			cout<< "�밴����������˵�"<< endl;
			getch();
			system("cls");
			mainmenu();
		} 
		G.mes->max_credit=credit;
		outtextxy(100, 650, "�޸ĳɹ�"); // ��ͼ���Ϸ���ʾ�ı�
		outtextxy(100, 700, "������������˵�"); // ��ͼ���Ϸ���ʾ�ı�
		cout << "\n�޸ĳɹ�\n" <<endl;
		cout << "������������˵�" <<endl;
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
	ofs.open("./����.txt",ios::in | ios::out | ios::binary);

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
    settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
	settextstyle(20, 0, "����");      // �����ı���ʽ
	Print_Top_Sort_Result();
	outtextxy(100, 500, "��������ѡ��Ŀγ̰����Ⱥ�˳��"); // ��ͼ���Ϸ���ʾ�ı�
	cout << "\n\n\n��������ѡ��Ŀγ̰����Ⱥ�˳��";
	
		
	char key=getch();
//	int input = static_cast<int>(key); 
//		char term_str[10];
//        sprintf(term_str, "��ѡ��Ŀγ̰���λ���ǣ�%d-------", input);
//        outtextxy(100, 550, term_str);
	 std::string inputString = "��ѡ��Ŀγ̰���λ����: ";
    inputString += key;

    // ����Ϻ���ַ�����ʾ��ͼ����
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
		outtextxy(100, 600, "ѡ�������밴����������˵�"); // ��ͼ���Ϸ���ʾ�ı�
		cout<<"ѡ�������밴����������˵�";
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
    settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
	settextstyle(20, 0, "����");      // �����ı���ʽ
	system("cls");
	FILE *fp=fopen("./��ѧ�ڿγ̰��Ž��.txt","w");
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
//		sprintf(buffer, "\n��%d��ѧ�ڵĿγ�Ϊ��", k + 1);
//
//// Assuming the second and third arguments of printToGraphics are x and y coordinates
//		printToGraphics(buffer, 100, 100 + k * 30);
//        
//        
//        
//		fprintf(fp, "\n��%d��ѧ�ڵĿγ�Ϊ��", k+1);
//		printf("\n��%d��ѧ�ڵĿγ�Ϊ��", k + 1);
//		Sumcredit=0;       //��ѧ�ڰ��ſγ̵���ѧ��
//		course_num=0;	 //��ѧ�ڰ��ſγ̵�����
//		p=result[i].FirstArc;  //���޿�ָ��
//		tag=0;          //��־��ѧ���Ƿ��иÿγ̵����޿γ�
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
//    sprintf(buffer, "��%d��ѧ�ڰ��ŵĿγ�Ϊ��", k + 1);
//    printToGraphics(buffer, 100, 100 + k * 30);
	sprintf(buffer, "��%d��ѧ�ڰ��ŵĿγ�Ϊ��", k + 1);

    // ������ֱλ���Ա����ص�
    outtextxy(100, 100 + k * 30, buffer);
    fprintf(fp, "��%d��ѧ�ڰ��ŵĿγ�Ϊ��", k + 1);
    printf("��%d��ѧ�ڰ��ŵĿγ�Ϊ��", k + 1);
    Sumcredit = 0;       // ��ѧ�ڰ��ſγ̵���ѧ��
    course_num = 0;      // ��ѧ�ڰ��ſγ̵�����
    p = result[i].FirstArc;  // ���޿�ָ��
    tag = 0;             // ��־��ѧ���Ƿ��иÿγ̵����޿γ�
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

        // ����γ���Ϣ
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
    
    printf("\n");  // ���У���ʾ��һ��ѧ�ڵĿγ�
    fprintf(fp, "\n");
}



	fclose(fp);

	if(k>G.mes->term_num)
	{
		fp=fopen("./��ѧ�ڿγ̰��Ž��.txt","w");
		fprintf(fp,"%s","�ÿγ̰����Ⱥ�˳���£��˲����޽�,��Ϊ��������ѧ�����������ѧ����");
		fclose(fp);
		cout << "\n\n\n�ÿγ̰����Ⱥ�˳���£��˲����޽�,��Ϊ��������ѧ�����������ѧ����\n\n\n";
		cout <<"�밴����������˵�" <<endl;
		getch();
		system("cls");
		mainmenu();
	}

	cout << "\n\n\n �γ̰�����Ϣ�Ѿ����뵱ǰĿ¼�£�����ѧ�ڿγ̰��Ž��.txt�� \n\n�밴����������˵�";
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
		cout<< "��������ʧ�ܣ��γ����޹�ϵ���ܴ��ڻ�·���밴����������˵�\n";
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
			cout << "��������ջʧ��,�밴����������˵�" << endl;
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
    settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
	settextstyle(20, 0, "����");      // �����ı���ʽ

	
	
	
	printf("���γ̰����Ⱥ�˳��Ϊ:\n");
	cout << "ѡ��1��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result1[i].data<< "  " ;
	}

	cout << "\n\nѡ��2��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result2[i].data<< "  " ;
	}

	cout << "\n\nѡ��3��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result3[i].data<< "  " ;
	}

	cout << "\n\nѡ��4��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result4[i].data<< "  " ;
	}	
	    // ��ͼ�δ�������ʾ�ı�
    outtextxy(100, 50, "���γ̴��Ű����Ⱥ�˳��Ϊ:___________________");
    outtextxy(100, 100, "��1���ɹ��ο�������ѡ��һ:");
    outtextxy(100, 200, "��2���ɹ��ο�������ѡ���:");
    outtextxy(100, 300, "��3���ɹ��ο�������ѡ����:");
    outtextxy(100, 400, "��4���ɹ��ο�������ѡ����:");

    // ѡ��1
   for (int i = 0; i <  G.VexNum; i++) {
        // ʹ�� std::string ���캯�������ַ�����
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
	setbkcolor(YELLOW);                                            //�ı���
	clearrectangle(160, 470, 410, 510);
	clearrectangle(160, 410, 410, 450);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(254, 241, 67));
	settextstyle(120, 0, _T("����"));

	settextcolor(RGB(220, 105, 36));

	settextcolor(BLACK);
	settextstyle(16, 0, _T("����"));
	outtextxy(116, 415, _T("�˺ţ�"));
	outtextxy(116, 475, _T("���룺"));
	settextcolor(RGB(254, 241, 67));
	settextstyle(40, 0, _T("����"));
	outtextxy(75, 325, _T("�����ѧ����ϵͳ"));
	settextcolor(RGB(162, 178, 194));
	settextstyle(12, 0, _T("����"));
	outtextxy(160, 420, _T(" ���루3-18��λ�˺�"));
	outtextxy(160, 480, _T(" ���루6-18��λ����"));
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
		settextstyle(16, 0, _T("����"));
		outtextxy(20, 150, _T("��Ϸ�ļ��쳣,�����ļ�������"));
	}
	int x0 = 0;
	char c = 1;
	settextcolor(BLACK);
	setbkcolor(WHITE);

	clearrectangle(160, 410, 410, 450);
	for (int x = 0; c != 13 && x <= 18; x++) {//¼���û���

		setbkcolor(BLACK);
		clearrectangle(0, 0, 5, 5);
		while (!a) {//����λ����˸
			while (MouseHit()) {
				m = GetMouseMsg();

				if (m.mkLButton == 1) {


				}

			}
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("����"));
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
		if (x < 18 && c != 8) {//���˸�����
			username[x] = c;
		}
		if (c == 8 && x == 0) {//����ʱ�˸�����
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//����ʱ�˸�����
			x = x - 1;
			username[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}

		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(16, 0, _T("����"));
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
		settextstyle(16, 0, _T("����"));
		outtextxy(163, 440, _T("�û���̫�̣�"));
		fclose(fp);
		return NULL;
	}
	c = 1;


	clearrectangle(160, 470, 410, 510);
	for (int x = 0; c != 13; x++) {
		while (!a) {//����λ����˸
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("����"));
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
		if (c == 8 && x == 0) {//����ʱ�˸�����
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//����ʱ�˸�����
			x = x - 1;
			password[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(20, 0, _T("����"));
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
		settextstyle(16, 0, _T("����"));
		outtextxy(163, 440, _T("����̫�̣�"));
		fclose(fp);
		return NULL;
	}
	c = 1;
	clearrectangle(160, 470, 410, 510);
	settextstyle(16, 0, _T("����"));
	outtextxy(116 - 32, 475, _T("ȷ��"));
	for (int x = 0; c != 13; x++) {
		while (!a) {//����λ����˸
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("����"));
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
		if (c == 8 && x == 0) {//����ʱ�˸�����
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//����ʱ�˸�����
			x = x - 1;
			password2[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(20, 0, _T("����"));
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
		settextstyle(16, 0, _T("����"));
		outtextxy(163, 440, _T("�����������벻ͬ�������ԣ�"));
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
			if (strcmp((*player)->name, b.name)) /*������������*/
			{
				if (!feof(fp))    /*���δ���ļ�β*/
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
				settextstyle(16, 0, _T("����"));
				outtextxy(163, 440, _T("���û����Ѵ��ڣ�������ע�ᣡ"));
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
		settextstyle(16, 0, _T("����"));
		outtextxy(20, 150, _T("��Ϸ�ļ��쳣,�����ļ�������"));
	}
	char c = 1;
	settextcolor(BLACK);
	setbkcolor(WHITE);

	clearrectangle(160, 410, 410, 450);
	for (int x = 0; c != 13 && x <= 18; x++) {//¼���û���

		while (!a) {//����λ����˸


			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("����"));
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
		if (x < 18 && c != 8) {//���˸�����
			username[x] = c;
		}
		if (c == 8 && x == 0) {//����ʱ�˸�����
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//����ʱ�˸�����
			x = x - 1;
			username[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 410, 176 + 13 * x, 450);
			x = x - 1;
		}

		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(16, 0, _T("����"));
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
		while (!a) {//����λ����˸
			if (clock() / 500 % 2 == 0) {
				settextcolor(BLACK);
				settextstyle(16, 0, _T("����"));
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
		if (c == 8 && x == 0) {//����ʱ�˸�����
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (c == 8 && x > 0) {//����ʱ�˸�����
			x = x - 1;
			password[x] = { 0 };
			setbkcolor(WHITE);
			clearrectangle(163 + 13 * x, 470, 176 + 13 * x, 510);
			x = x - 1;
		}
		if (x < 18 && c != 13 && c != 8) {
			settextcolor(BLACK);
			settextstyle(20, 0, _T("����"));
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
			if (strcmp((*player)->name, b.name) == 0)         //����д��û���
			{
				break;
			}
			else
			{
				if (!feof(fp))  //����ļ�û�ж���                            
				{
					fread(&b, sizeof(struct users), 1, fp);
				}
				else
				{
					titlepage();
					settextcolor(BLACK);
					settextstyle(16, 0, _T("����"));
					outtextxy(163, 440, _T("�û��������ڣ������µ�¼��"));
					fclose(fp);
					return NULL;
				}
			}
		}
		do {
			if (strcmp((*player)->pwd, b.pwd) == 0)            /*�������ƥ��*/
			{
				(*player)->score = b.score;
				fclose(fp);
				return  (*player)->name;
			}
			else
			{
				titlepage();		
				settextcolor(BLACK);
				settextstyle(16, 0, _T("����"));
				outtextxy(163, 440, _T("���벻��ȷ!�����µ�¼��"));
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
	settextstyle(16, 0, _T("����"));
	outtextxy(482, 368, _T("��¼"));
	outtextxy(482, 438, _T("ע��"));
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


