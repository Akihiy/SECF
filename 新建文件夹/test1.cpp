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

    settextcolor(RGB(255, 255, 255)); // �����ı���ɫ
    settextstyle(20, 0, "����");      // �����ı���ʽ

    ifstream file("����.txt");
    if (file.is_open()) {
        int x = 50; // ��ʼ������
        int y = 50; // ��ʼ������

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
                sprintf(text, "�γ̺�: %s          ѧ��: %d", courseID.c_str(), credits);
            } else {
                sprintf(text, "�γ̺�: %s          ѧ��: %d         ���޿γ�: ", courseID.c_str(), credits);
                for (const string& prereq : prerequisites) {
                    strcat(text, prereq.c_str());
                    strcat(text, " ");
                }
            }

            drawText(text, x, y);
            y += 30; // �����������Ի�����һ��
        }

        file.close();
    } else {
        drawText("�޷�������.txt�ļ�", x, y); // ����ļ��޷��򿪣���ʾ������Ϣ
    }

    getch();
    closegraph();
    return 0;
}








