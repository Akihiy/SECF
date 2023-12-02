#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include "structure.h"
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
#include <time.h>


//MOUSEMSG m;
#include <conio.h>

   struct users
{
	char pwd[20] = {0};
	char name[20] = {0};
	int id = 0;
	int score = 0;
};

//char pic1[] = "pic1.png";
//IMAGE img_1;

const char* getComputerScienceCourse(int courseCode);

void mainmenu();	

int Locate(char* ch);			

void Read_file();	

void Print_message(); 

void Adjust_message(); 

void File_Update();   

void Arrange_Selete(int choice);		

void Arrange(VexNode *result,int choice);

void Top_Sort(VexNode *result,int choice);	

void Print_Top_Sort_Result();  

void titlepage(); 
char* registers(users** player) ;
char* login(users** player);
void showgui();
void titlesystem(users** player);



#endif // FUNC_H_INCLUDED
