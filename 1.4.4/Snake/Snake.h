/*
   Copyright (c) 2021 2345Explorer
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

//方向键的ASCII.
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//20*50的格子.
#define HIGHT 20
#define WIDTH 50
//蛇的最长长度.
#define MaxSnakeTailLength 10000
//速度.
#define WALK 300
#define GO 125
#define RUN 50
#define FAST 25

char HeadC='#',TailC='*',FruitC='0';

void gotoXY(short x,short y) {
	COORD pos = {x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void Print_Fame(int x,int y,int len){
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

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

struct pos {		//pos从0开始.
	short x,y;
};
struct DebugModeSettingStruct{
	bool HBT;	//蛇头撞蛇身是否算死亡.
	long long InitTailLength;	//初始蛇长.
};
struct TestSettingStruct {
	bool sd;	//游戏玩完后关机
};

const short SPEED_MS[5]={0,WALK,GO,RUN,FAST};		//速度对应的值  
const string SPEED_STR[5]={"","散步","行走","奔跑","疯狂"};	//必须是两个字

const string VERSION="1.4.3",TIME="2022.1.23";
