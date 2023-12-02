#include <iostream>
#include "structure.h"
#include "func.h"
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
using namespace std;


VexNode result1[100];
VexNode result2[100];
VexNode result3[100];
VexNode result4[100];
Class_arrange_Graph G;










int main()
{
	char pic1[] = "pic4.png";
	IMAGE img_1;
    initgraph(1200, 900);
    loadimage(&img_1, pic1);
    putimage(0, 0, &img_1);
    Read_file();
//    users* player[1];
//    titlesystem(player);
    

	mainmenu();

    return 0;
}



