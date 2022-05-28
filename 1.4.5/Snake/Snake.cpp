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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "Snake.h"
using namespace std;
//定义.
void initFruit();
void initHead(short ms);
void printMap();
void printTips();
bool move();
void eatFruit();
bool getInput();
void startGame(short ms);
short startMenu();
void debugSettings();
void testSettings();
bool endGame(short x);
short startGameMenu();
void settings();
void about();
Pos head,tail[maxSnakeTailLength],fruit;
DebugModeSettingStruct DebugModeSetting;
TestSettingStruct TestSetting;
int SnakeLength=0;
const short dx[4]= {-1,1,0,0},dy[4]= {0,0,-1,1};
const short rdx[4]= {1,-1,0,0},rdy[4]= {0,0,1,-1};
bool Pausing=false,SeeMenu=false;
int d;		//0前1后2左3右

int main(int argc,char* argv[],char** env) {
	srand((unsigned)time(NULL));
	system("title 贪吃蛇");
	hideCursor();

	DebugModeSetting.HBT = true;
	DebugModeSetting.InitTailLength = 0;
	while(1) {
		SnakeLength=0;
		system("cls");
		short t=startMenu();
		if(SeeMenu){
			SeeMenu=false;
			continue;
		}
		if(!endGame(t)) {
			system("cls");
			system("pause");
			return 0;
		}
	}
}

void initFruit(){		//初始化水果.
	hideCursor();
	do {
		fruit.x=rand()%HIGHT,fruit.y=rand()%WIDTH;
		for(int i=0;i<SnakeLength;i++)
			if(fruit.x==tail[i].x&&fruit.y==tail[i].y){
				fruit.x=0;
				break;
			}
	} while(fruit.x==0||fruit.y==0||fruit.x==HIGHT-1||fruit.y==WIDTH-1||(fruit.x==head.x&&fruit.y==head.y));
}
void initHead(short ms){		//初始化蛇头.
	hideCursor();
	int a[4]= {2,4,6,8};
	int x=0;
	if(ms==SPEED_MS[1])	x=0;
	else if(ms==SPEED_MS[2])	x=1;
	else if(ms==SPEED_MS[3])	x=2;
	else if(ms==SPEED_MS[4])	x=3;
	do {
		head.x=rand()%HIGHT,head.y=rand()%WIDTH;
	} while(head.x<=a[x]||head.y<=a[x]||head.x>=HIGHT-a[x]||head.y>=WIDTH-a[x]);
}

void printMap(){		//输出地图.
	hideCursor();
	bool mp[HIGHT+2][WIDTH+2];
	memset(mp,0,sizeof(mp));
	mp[head.x][head.y]=1;
	for(int i=0; i<SnakeLength; i++) {
		mp[tail[i].x][tail[i].y]=1;
	}
	for(int i=0; i<HIGHT; i++) {
		for(int j=0; j<WIDTH; j++) {
			if(i==fruit.x&&j==fruit.y) {
				gotoXY(j,i);
				cout<<FruitC;
			} else if(mp[i][j]) {
				gotoXY(j,i);
				if(i==head.x&&j==head.y)
					cout<<HeadC;
				else
					cout<<TailC;
			} else if(i==0||j==0||i==HIGHT-1||j==WIDTH-1) {
				gotoXY(j,i);
				if(i==0||i==HIGHT-1) {
					cout<<"-";
				} else {
					cout<<"|";
				}
			} else {
				gotoXY(j,i);
				cout<<" ";
			}
		}
	}
}
void printTips(){
	hideCursor();
	gotoXY(WIDTH+2,10);
	cout<<"当前分数:"<<SnakeLength+1<<"         ";
	gotoXY(WIDTH+2,12);
	cout<<"用方向键操控贪吃蛇,ESC暂停           ";
}

bool move(){		//是否可以移动,如果可以就移动.
	hideCursor();
	int thx=head.x+dx[d],thy=head.y+dy[d];
	if(DebugModeSetting.HBT)
		for(int i=0; i<SnakeLength; i++)
			if(thx==tail[i].x&&thy==tail[i].y)
				return false;
	int lx=head.x,ly=head.y;
	head.x+=dx[d],head.y+=dy[d];
	for(int i=0; i<SnakeLength; i++) {
		int tx=tail[i].x,ty=tail[i].y;
		tail[i].x=lx,tail[i].y=ly;
		lx=tx,ly=ty;
	}
	return true;
}

void eatFruit(){		//吃到水果.
	hideCursor();
	tail[SnakeLength].x=tail[SnakeLength-1].x+rdx[d];
	tail[SnakeLength].y=tail[SnakeLength-1].y+rdy[d];
	SnakeLength++;
	initFruit();
}

bool getInput(){		//获取键盘输入.
	hideCursor();
	char t=_getch();
	if(t!=0&&t!=224&&t!=-32) {
		if (t == 0x1b) 
			Pausing=true;
		return true;
	}
	char c=_getch();		//第二次读取,为什么网上有.
	if(c==UP) {
		if(d!=1) {
			d=0;
			if(!move())
				return false;
		}
	} else if(c==DOWN) {
		if(d!=0) {
			d=1;
			if(!move())
				return false;
		}
	} else if(c==LEFT) {
		if(d!=3) {
			d=2;
			if(!move())
				return false;
		}
	} else if(c==RIGHT) {
		if(d!=2) {
			d=3;
			if(!move())
				return false;
		}
	}
	return true;
}

void startGame(short ms){		//开始游戏.
	hideCursor();
	gotoXY(WIDTH,0);
	cout<<"       ";
	d=rand()%4;
	initHead(ms);
	initFruit();
	for(int i=1;i<=DebugModeSetting.InitTailLength;i++)	eatFruit();
	while(head.x>0&&head.y>0&&head.x<HIGHT-1&&head.y<WIDTH-1) {
		if(Pausing) {
			int a[3][3]={9,WIDTH+2,8,11,WIDTH+2,12,13,WIDTH+2,8},i=0;
			bool flag=false;
			while(1){
				if(!flag){
					system("cls");
					printMap();
					gotoXY(WIDTH+2,10);
					cout<<"返回游戏                 ";
					gotoXY(WIDTH+2,12);
					cout<<"退出至主菜单             ";
					gotoXY(WIDTH+2,14);
					cout<<"退出游戏                 ";
					printFrame(a[i][0],a[i][1],a[i][2]+1);
					gotoXY(WIDTH+2,16);
					cout<<"上、下方向键切换, 回车选择";
				} else {
					flag=false;
				}
				char t=_getch();
				if(t==0||t==224||t==-32) {
					char c=_getch();
					if(c==UP) {
						if(i>0) i--;
						else	i=2;
					} else if(c==DOWN) {
						if(i<2)	i++;
						else	i=0;
					} else {
						flag=true;
					}
				} else if(t==13){	//回车.
					if(i==0){
						break;
					}else if(i==1){
						Pausing=false;
						SeeMenu=true;
						return ;
					}else if(i==2){
						gotoXY(0,HIGHT+1);
						exit(0);
					}
				}
			}
			Pausing=false;
			system("cls");
			printMap();
			printTips();
		}
		if(head.x==fruit.x&&head.y==fruit.y) {
			eatFruit();
		}
		if(_kbhit()) {
			if(!getInput())
				break;
		} else {
			if(!move())
				break;
		}
		Sleep(ms);
		printMap();
		printTips();
	}
	printMap();
	printTips();
}

short startGameMenu(){
	hideCursor();
	system("cls");
	int f=0,speed,flag=false;
	int a[5][2]={2,2,8,2,14,2,20,2,26,2};
	while(1){
		if(!flag){
			system("cls");
			cout<<"**********贪吃蛇**********\n";
			cout<<"请选择速度\n\n";
			cout<<' '<<SPEED_STR[1]<<"  "<<SPEED_STR[2]<<"  "
				<<SPEED_STR[3]<<"  "<<SPEED_STR[4]<<" 随机\n\n";
			cout<<"左、右方向键切换,回车选择\n";
			printFrame(2,a[f][0],a[f][1]+1);
		} else {
			flag=false;
		}
		char c1=_getch();
		if(c1!=0&&c1!=224&&c1!=-32){
			if(c1==13){
				if(f==4){
					speed=rand()%4+1;	//散步:1 行走:2 奔跑:3 疯狂:4 
				} else {
					speed=f+1;
				}
				break;
			} else {
				flag=true;
			}
		} else {
			char c2=_getch();
			if(c2==LEFT){
				if(f==0)	f=4;
				else	f--;
			} else if(c2==RIGHT){
				if(f==4)	f=0;
				else	f++;
			} else {
				flag=true;
			}
		}
	}
	system("cls");
	if(f==4)
		cout<<"已选速度:"<<SPEED_STR[speed]<<endl;
	cout<<"加载中...\n";
	Sleep(1050);
	startGame(SPEED_MS[speed]);
	return speed;
}

void testSettings() {
	int f = 0;
	int a[2][3] = { 1,24,2,3,24,13};
	bool flag = false;
	while (1) {
		if (!flag) {
			system("cls");
			cout << "********实验性********\n\n";
			cout << "玩完游戏自动关机:";
			if (TestSetting.sd)	cout << "是";
			else	cout << "否";
			cout << "    更改\n\n";
			gotoXY(23, 4);
			cout << "返回到Debug设置\n\n";
		} else flag = false;
		printFrame(a[f][0], a[f][1], a[f][2] + 1);
		char c1 = _getch();
		if (c1 != 0 && c1 != 224 && c1 != -32) {
			if (c1 == 13) {		//回车.
				system("cls");
				if (f == 0) {
					if (TestSetting.sd) {
						TestSetting.sd = false;
						cout << "玩完游戏自动关机已更改为:否\n";
						Sleep(700);
						continue;
					}
					cout << "确定嘛?(Y/N)";
					char c2 = _getche();
					while (c2 != 'Y' && c2 != 'N'&&c2!='y'&&c2!='n')	c2 = _getch();
					if (c2 == 'N' || c2 == 'n')	continue;
					TestSetting.sd = true;
					cout << "\n危\n";
					Sleep(700);
				} else {
					break;
				}
			} else {
				flag = true;
				continue;
			}
		}
		else {
			char c2 = _getch();
			if (c2 == UP) {
				if (f == 0)	f = 1;
				else	f--;
			}
			else if (c2 == DOWN) {
				if (f == 1)	f = 0;
				else	f++;
			}
			else {
				flag = true;
				continue;
			}
		}
	}
}
void debugSettings(){
	int f=0;
	int a[4][3]={1,22,2,3,22,10,5,22,4,7,22,2};
	bool flag=false;
	while(1){
		if(!flag){
			system("cls");
			cout<<"********Debug设置********\n\n";
			cout<<"蛇头撞蛇身死亡:";
			if(DebugModeSetting.HBT)	cout<<"是";
			else	cout<<"否";
			cout<<"    更改  \n\n";
			cout<<"当前初始长度为:"<<DebugModeSetting.InitTailLength+1;
			gotoXY(21,4);
			cout<<"更改初始长度  \n\n";
			cout << "实验性";
			gotoXY(21,6);
			cout<<"设置\n\n";
			gotoXY(21,8);
			cout<<"退出\n\n";
			cout<<"上、下方向键选择, 回车确认 \n";
		} else flag=false;
		printFrame(a[f][0],a[f][1],a[f][2]+1);
		char c1=_getch();
		if(c1!=0&&c1!=224&&c1!=-32) {
			if(c1==13){		//回车.
				system("cls");
				if(f==0){
					DebugModeSetting.HBT=!DebugModeSetting.HBT;
					cout<<"蛇头撞蛇身死亡已更改为";
					if(DebugModeSetting.HBT==true)	cout<<"是\n";
					else	cout<<"否\n";
					cout<<"即将回到Debug设置界面...\n";
					Sleep(700);
				} else if(f==1){
					cout<<"请输入要更改的初始长度:";
					long long t;
					cin>>t;
					t--;
					if(t<0)	t=-t;
					t%=maxSnakeTailLength;
					DebugModeSetting.InitTailLength=t;
					cout<<"\n更改成功!即将回到Debug设置界面...";
					Sleep(700);
				} else if (f == 2) {
					testSettings();
				} else{
					break;
				}
			} else {
				flag=true;
				continue;
			}
		} else {
			char c2=_getch();
			if(c2==UP){
				if(f==0)	f=3;
				else	f--;
			} else if(c2==DOWN){
				if(f==3)	f=0;
				else	f++;
			} else {
				flag=true;
				continue;
			}
		}
	}
}

void settings(){
	hideCursor();
	int fx=0,fy=0;
	int a[4][2][3]={{{1,12,2},{1,20,2}},
					{{3,12,2},{3,20,2}},
					{{5,12,2},{5,20,2}},
					{{7,9,8},{7,20,6}}};
	bool flag=false;
	while(1){
		if(!flag){
			system("cls");
			cout<<"**********设置***********\n\n";
			cout<<" 蛇头:"<<HeadC<<"    重置    更改 \n\n";
			cout<<" 蛇身:"<<TailC<<"    重置    更改 \n\n";
			cout<<" 食物:"<<FruitC<<"    重置    更改 \n\n";
			cout<<"        Debug模式  退出设置 \n\n";
			cout<<"上下左右方向键选择, 回车确认\n";
		} else	flag=false;
		printFrame(a[fx][fy][0],a[fx][fy][1],a[fx][fy][2]+1);
		char c1=_getch();
		if(c1!=0&&c1!=224&&c1!=-32) {
			if(c1==13){		//回车.
				if(fy==0&&fx<3){
					system("cls");
					if(fx==0){
						HeadC='#';
						cout<<"蛇头符号已重置为#\n";
						cout<<"即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==1){
						TailC='*';
						cout<<"蛇身符号已重置为*\n";
						cout<<"即将回到设置界面...";
						Sleep(700);
					}
					else {
						FruitC='0';
						cout<<"食物符号已重置为0\n";
						cout<<"即将回到设置界面...";
						Sleep(700);
					}
				} else if(fy==1){
					system("cls");
					if(fx==0){
						cout<<"请输入要更改的蛇头符号:";
						HeadC=_getche();
						cout<<"\n更改成功!即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==1){
						cout<<"请输入要更改的蛇身符号:";
						TailC=_getche();
						cout<<"\n更改成功!即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==2){
						cout<<"请输入要更改的食物符号:";
						FruitC=_getche();
						cout<<"\n更改成功!即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==3)	break;
				} else if(fx==3&&fy==0){
					debugSettings();
				}
			} else {
				flag=true;
				continue;
			}
		} else {
			char c2=_getch();
			if(c2==UP){
				if(fx==0)	fx=3;
				else	fx--;
			} else if(c2==DOWN){
				if(fx==3)	fx=0;
				else	fx++;
			} else if(c2==LEFT){
				if(fy==0)	fy=1;
				else	fy--;
			} else if(c2==RIGHT){
				if(fy==1)	fy=0;
				else	fy++;
			} else {
				flag=true;
				continue;
			}
		}
	}
}
void about(){
	hideCursor();
	system("cls");
	cout<<"贪吃蛇"<<VERSION<<" by 2345Explorer\n";
	Sleep(100);
	cout<<"更新时间:"<<TIME<<endl;
	Sleep(100);
	cout<<"点个Star⑧ QAQ\n仓库地址:https://gitee.com/Explorer2345/snake\n";
	Sleep(100);
	system("pause");
}
short startMenu(){		//初始菜单.
	hideCursor();
	int f=0;
	bool flag=false;
	int a[4][2]= {2,2,11,2,20,2,29,6};
	while(1) {
		if(!flag){
			system("cls");
			cout<<"**********贪吃蛇**********\n\n";
			cout<<" 开始     设置     关于     退出游戏  \n";
		}
		else	flag=false;
		printFrame(1,a[f][0],a[f][1]+1);
		gotoXY(0,4);
		cout<<"左、右方向键切换,回车选择\n";
		char c1=_getch();
		if(c1!=0&&c1!=224&&c1!=-32) {
			if(c1==13) {		//回车.
				if(f==1)
					settings();
				else if(f==2)
					about();
				else if(f==3)
					exit(0);
				else
					break;
			} else {
				flag=true;
				continue;
			}
		} else {
			char c2=_getch();
			if(c2==LEFT) {
				if(f==0)	f=3;
				else	f--;
			} else if(c2==RIGHT) {
				if(f==3)	f=0;
				else	f++;
			} else {
				flag=true;
				continue;
			}
		}
	}
	return startGameMenu();
}
bool endGame(short x){		//游戏结束.
	hideCursor();
	gotoXY(0,HIGHT+1);
	cout<<"游戏结束!\n";
	system("pause");
	system("cls");
	cout<<"游戏结束!\n";
	cout<<"分数:"<<SnakeLength+1<<endl;
	cout<<"速度:"<<SPEED_STR[x]<<endl;
	Sleep(1000);
	if (TestSetting.sd) {
		cout << "游戏玩完了 关机中...";
		system("shutdown /s /t 10");
	}
	cout<<"Y:再来一次 N:结束\n";
	char c=32;
	while(c!='Y'&&c!='y'&&c!='N'&&c!='n'){
		c=_getch();
	}
	return (c=='Y'||c=='y');
}
