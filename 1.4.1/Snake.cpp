/*
   Copyright (c) [Year] [name of copyright holder]
   [Software Name] is licensed under Mulan PSL v2.
   You can use this software according to the terms and conditions of the Mulan PSL v2. 
   You may obtain a copy of Mulan PSL v2 at:
            http://license.coscl.org.cn/MulanPSL2 
   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.  
   See the Mulan PSL v2 for more details.  


                     Mulan Permissive Software License，Version 2

   Mulan Permissive Software License，Version 2 (Mulan PSL v2)
   January 2020 http://license.coscl.org.cn/MulanPSL2

   Your reproduction, use, modification and distribution of the Software shall be subject to Mulan PSL v2 (this License) with the following terms and conditions: 
   
   0. Definition
   
      Software means the program and related documents which are licensed under this License and comprise all Contribution(s). 
   
      Contribution means the copyrightable work licensed by a particular Contributor under this License.
   
      Contributor means the Individual or Legal Entity who licenses its copyrightable work under this License.
   
      Legal Entity means the entity making a Contribution and all its Affiliates.
   
      Affiliates means entities that control, are controlled by, or are under common control with the acting entity under this License, ‘control’ means direct or indirect ownership of at least fifty percent (50%) of the voting power, capital or other securities of controlled or commonly controlled entity.

   1. Grant of Copyright License

      Subject to the terms and conditions of this License, each Contributor hereby grants to you a perpetual, worldwide, royalty-free, non-exclusive, irrevocable copyright license to reproduce, use, modify, or distribute its Contribution, with modification or not.

   2. Grant of Patent License 

      Subject to the terms and conditions of this License, each Contributor hereby grants to you a perpetual, worldwide, royalty-free, non-exclusive, irrevocable (except for revocation under this Section) patent license to make, have made, use, offer for sale, sell, import or otherwise transfer its Contribution, where such patent license is only limited to the patent claims owned or controlled by such Contributor now or in future which will be necessarily infringed by its Contribution alone, or by combination of the Contribution with the Software to which the Contribution was contributed. The patent license shall not apply to any modification of the Contribution, and any other combination which includes the Contribution. If you or your Affiliates directly or indirectly institute patent litigation (including a cross claim or counterclaim in a litigation) or other patent enforcement activities against any individual or entity by alleging that the Software or any Contribution in it infringes patents, then any patent license granted to you under this License for the Software shall terminate as of the date such litigation or activity is filed or taken.

   3. No Trademark License

      No trademark license is granted to use the trade names, trademarks, service marks, or product names of Contributor, except as required to fulfill notice requirements in Section 4.

   4. Distribution Restriction

      You may distribute the Software in any medium with or without modification, whether in source or executable forms, provided that you provide recipients with a copy of this License and retain copyright, patent, trademark and disclaimer statements in the Software.

   5. Disclaimer of Warranty and Limitation of Liability

      THE SOFTWARE AND CONTRIBUTION IN IT ARE PROVIDED WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR IMPLIED. IN NO EVENT SHALL ANY CONTRIBUTOR OR COPYRIGHT HOLDER BE LIABLE TO YOU FOR ANY DAMAGES, INCLUDING, BUT NOT LIMITED TO ANY DIRECT, OR INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM YOUR USE OR INABILITY TO USE THE SOFTWARE OR THE CONTRIBUTION IN IT, NO MATTER HOW IT’S CAUSED OR BASED ON WHICH LEGAL THEORY, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

   6. Language

      THIS LICENSE IS WRITTEN IN BOTH CHINESE AND ENGLISH, AND THE CHINESE VERSION AND ENGLISH VERSION SHALL HAVE THE SAME LEGAL EFFECT. IN THE CASE OF DIVERGENCE BETWEEN THE CHINESE AND ENGLISH VERSIONS, THE CHINESE VERSION SHALL PREVAIL.

   END OF THE TERMS AND CONDITIONS

   How to Apply the Mulan Permissive Software License，Version 2 (Mulan PSL v2) to Your Software

      To apply the Mulan PSL v2 to your work, for easy identification by recipients, you are suggested to complete following three steps:

      i Fill in the blanks in following statement, including insert your software name, the year of the first publication of your software, and your name identified as the copyright owner; 

      ii Create a file named “LICENSE” which contains the whole context of this License in the first directory of your software package;

      iii Attach the statement to the appropriate annotated syntax at the beginning of each source file.


   Copyright (c) [Year] [name of copyright holder]
   [Software Name] is licensed under Mulan PSL v2.
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
void InitFruit() throw() ;
void InitHead(short ms) throw() ;
void Print_Map() throw() ;
void Print_Tips() throw() ;
bool Move() throw() ;
void EatFruit() throw() ;
bool GetInput() throw() ;
void StartGame(short ms) throw() ;
short StartMenu() throw() ;
void DebugMode() throw() ;
bool EndGame(short x) throw() ;
short _Start() throw() ;
void Settings() throw() ;
void About() throw() ;
pos head,tail[MaxSnakeTailLength],fruit;
DebugModeSettings DebugModeSetting=(DebugModeSettings){true,0};
int SnakeLength=0;
const short dx[4]= {-1,1,0,0},dy[4]= {0,0,-1,1};
const short rdx[4]= {1,-1,0,0},rdy[4]= {0,0,1,-1};
bool Pausing=false,SeeMenu=false;
int d;		//0前1后2左3右

int main(int argc,char* argv[],char** env) {
	srand((unsigned)time(NULL));
	system("title 贪吃蛇");
	HideCursor();

	while(1) {
		SnakeLength=0;
		system("cls");
		short t=StartMenu();
		if(SeeMenu){
			SeeMenu=false;
			continue;
		}
		if(!EndGame(t)) {
			system("cls");
			system("pause");
			return 0;
		}
	}
}

void InitFruit() throw() {		//初始化水果.
	HideCursor();
	do {
		fruit.x=rand()%HIGHT,fruit.y=rand()%WIDTH;
		for(int i=0;i<SnakeLength;i++)
			if(fruit.x==tail[i].x&&fruit.y==tail[i].y){
				fruit.x=0;
				break;
			}
	} while(fruit.x==0||fruit.y==0||fruit.x==HIGHT-1||fruit.y==WIDTH-1||(fruit.x==head.x&&fruit.y==head.y));
}
void InitHead(short ms) throw() {		//初始化蛇头.
	HideCursor();
	int a[4]= {2,4,6,8};
	int x;
	if(ms==SPEED_MS[1])	x=0;
	else if(ms==SPEED_MS[2])	x=1;
	else if(ms==SPEED_MS[3])	x=2;
	else if(ms==SPEED_MS[4])	x=3;
	do {
		head.x=rand()%HIGHT,head.y=rand()%WIDTH;
	} while(head.x<=a[x]||head.y<=a[x]||head.x>=HIGHT-a[x]||head.y>=WIDTH-a[x]);
}

void Print_Map() throw() {		//输出地图.
	HideCursor();
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
void Print_Tips() throw() {
	HideCursor();
	gotoXY(WIDTH+2,10);
	cout<<"当前分数:"<<SnakeLength+1<<"         ";
	gotoXY(WIDTH+2,12);
	cout<<"用方向键操控贪吃蛇,ESC暂停           ";
}

bool Move() throw() {		//是否可以移动,如果可以就移动.
	HideCursor();
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

void EatFruit() throw() {		//吃到水果.
	HideCursor();
	tail[SnakeLength].x=tail[SnakeLength-1].x+rdx[d];
	tail[SnakeLength].y=tail[SnakeLength-1].y+rdy[d];
	SnakeLength++;
	InitFruit();
}

bool GetInput() throw() {		//获取键盘输入.
	HideCursor();
	char t=getch();
	if(t!=0&&t!=224&&t!=-32) {
		if(t==0x1b)
			Pausing=true;
		return true;
	}
	char c=getch();		//第二次读取,为什么网上有.
	if(c==UP) {
		if(d!=1) {
			d=0;
			if(!Move())
				return false;
		}
	} else if(c==DOWN) {
		if(d!=0) {
			d=1;
			if(!Move())
				return false;
		}
	} else if(c==LEFT) {
		if(d!=3) {
			d=2;
			if(!Move())
				return false;
		}
	} else if(c==RIGHT) {
		if(d!=2) {
			d=3;
			if(!Move())
				return false;
		}
	}
	return true;
}

void StartGame(short ms) throw() {		//开始游戏.
	HideCursor();
	gotoXY(WIDTH,0);
	cout<<"       ";
	d=rand()%4;
	InitHead(ms);
	InitFruit();
	for(int i=1;i<=DebugModeSetting.InitTailLength;i++)	EatFruit();
	while(head.x>0&&head.y>0&&head.x<HIGHT-1&&head.y<WIDTH-1) {
		if(Pausing) {
			int a[3][3]={9,WIDTH+2,8,11,WIDTH+2,12,13,WIDTH+2,8},i=0;
			bool flag=false;
			while(1){
				if(!flag){
					system("cls");
					Print_Map();
					gotoXY(WIDTH+2,10);
					cout<<"返回游戏                 ";
					gotoXY(WIDTH+2,12);
					cout<<"退出至主菜单             ";
					gotoXY(WIDTH+2,14);
					cout<<"退出游戏                 ";
					if(IsWin7())	Print_Fame(a[i][0],a[i][1],a[i][2]+1);
					else	Print_Fame(a[i][0],a[i][1],a[i][2]);
					gotoXY(WIDTH+2,16);
					cout<<"上、下方向键切换, 回车选择";
				} else {
					flag=false;
				}
				char t=getch();
				if(t==0||t==224||t==-32) {
					char c=getch();
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
			Print_Map();
			Print_Tips();
		}
		if(head.x==fruit.x&&head.y==fruit.y) {
			EatFruit();
		}
		if(_kbhit()) {
			if(!GetInput())
				break;
		} else {
			if(!Move())
				break;
		}
		Sleep(ms);
		Print_Map();
		Print_Tips();
	}
	Print_Map();
	Print_Tips();
}

short _Start() throw() {
	HideCursor();
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
			if(IsWin7())	Print_Fame(2,a[f][0],a[f][1]+1);
			else	Print_Fame(2,a[f][0],a[f][1]);
		} else {
			flag=false;
		}
		char c1=getch();
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
			char c2=getch();
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
	StartGame(SPEED_MS[speed]);
	return speed;
}

void DebugMode() throw() {
	int f=0;
	int a[3][3]={1,22,2,3,22,10,5,22,2};
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
			gotoXY(21,6);
			cout<<"退出\n\n";
			cout<<"上、下方向键选择, 回车确认 \n";
		} else flag=false;
		if(IsWin7)	Print_Fame(a[f][0],a[f][1],a[f][2]+1);
		else	Print_Fame(a[f][0],a[f][1],a[f][2]);
		char c1=getch();
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
					t%=MaxSnakeTailLength;
					DebugModeSetting.InitTailLength=t;
					cout<<"\n更改成功!即将回到Debug设置界面...";
					Sleep(700);
				} else{
					break;
				}
			} else {
				flag=true;
				continue;
			}
		} else {
			char c2=getch();
			if(c2==UP){
				if(f==0)	f=2;
				else	f--;
			} else if(c2==DOWN){
				if(f==2)	f=0;
				else	f++;
			} else {
				flag=true;
				continue;
			}
		}
	}
}

void Settings() throw() {
	HideCursor();
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
		if(IsWin7())	Print_Fame(a[fx][fy][0],a[fx][fy][1],a[fx][fy][2]+1);
		else	Print_Fame(a[fx][fy][0],a[fx][fy][1],a[fx][fy][2]);
		char c1=getch();
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
						HeadC=getche();
						cout<<"\n更改成功!即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==1){
						cout<<"请输入要更改的蛇身符号:";
						TailC=getche();
						cout<<"\n更改成功!即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==2){
						cout<<"请输入要更改的食物符号:";
						FruitC=getche();
						cout<<"\n更改成功!即将回到设置界面...";
						Sleep(700);
					}
					else if(fx==3)	break;
				} else if(fx==3&&fy==0){
					DebugMode();
				}
			} else {
				flag=true;
				continue;
			}
		} else {
			char c2=getch();
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
void About() throw() {
	HideCursor();
	system("cls");
	cout<<"贪吃蛇"<<VERSION<<" by 2345Explorer\n";
	Sleep(100);
	cout<<"更新时间:"<<TIME<<endl;
	Sleep(100);
	system("pause");
}
short StartMenu() throw() {		//初始菜单.
	HideCursor();
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
		if(IsWin7())	Print_Fame(1,a[f][0],a[f][1]+1);
		else	Print_Fame(1,a[f][0],a[f][1]);
		gotoXY(0,4);
		cout<<"左、右方向键切换,回车选择\n";
		char c1=getch();
		if(c1!=0&&c1!=224&&c1!=-32) {
			if(c1==13) {		//回车.
				if(f==1)
					Settings();
				else if(f==2)
					About();
				else if(f==3)
					exit(0);
				else
					break;
			} else {
				flag=true;
				continue;
			}
		} else {
			char c2=getch();
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
	return _Start();
}
bool EndGame(short x) throw() {		//游戏结束.
	HideCursor();
	gotoXY(0,HIGHT+1);
	cout<<"游戏结束!\n";
	system("pause");
	system("cls");
	cout<<"游戏结束!\n";
	cout<<"分数:"<<SnakeLength+1<<endl;
	cout<<"速度:"<<SPEED_STR[x]<<endl;
	Sleep(1000);
	cout<<"Y:再来一次 N:结束\n";
	char c=32;
	while(c!='Y'&&c!='y'&&c!='N'&&c!='n'){
		c=getch();
	}
	return (c=='Y'||c=='y');
}
