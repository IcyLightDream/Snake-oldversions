/*
   Copyright (c) 2022 2345Explorer
   Snake is licensed under Mulan PSL v2.
   You can use this software according to the terms and conditions of the Mulan PSL v2. 
   You may obtain a copy of Mulan PSL v2 at:
               http://license.coscl.org.cn/MulanPSL2 
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
   See the Mulan PSL v2 for more details.  
*/
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

//�������ASCII.
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//20*50�ĸ���.
#define HIGHT 20
#define WIDTH 50
//�ߵ������.
const int maxSnakeTailLength=10000;

char HeadC='#',TailC='*',FruitC='0';

void gotoXY(short x,short y) {
	COORD pos = {x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void printFrame(int x,int y,int len){
	gotoXY(y-1,x);
	for(int i=0;i<=len+1;i++)
		cout<<"-";
	gotoXY(y-1,x+2);
	for(int i=0;i<=len+1;i++)
		cout<<"-";
	gotoXY(y-2,x+1);
	cout<<"|";
	gotoXY(y+len,x+1);
	cout<<"|";
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

struct Pos {		//pos��0��ʼ.
	short x,y;
};
struct DebugModeSettingStruct{
	bool HBT;	//��ͷײ�����Ƿ�������.
	long long InitTailLength;	//��ʼ�߳�.
};
struct TestSettingStruct {
	bool sd;	//��Ϸ�����ػ�
};

const short SPEED_MS[5]={0,300,125,50,25};		//�ٶȶ�Ӧ��ֵ  
const string SPEED_STR[5]={"","ɢ��","����","����","���"};	//������������

const string VERSION="1.4.5",TIME="2022.5.28";