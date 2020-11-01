#include "stdafx.h"
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
bool EndGame(short x) throw() ;
short _Start() throw() ;
void Settings() throw() ;
void SeeSettings() throw() ;
void About() throw() ;
void ResetSettings() throw() ;
pos head,tail[MaxSnakeTailLength],fruit;
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
	} while(fruit.x==0||fruit.y==0||fruit.x==HIGHT-1||fruit.y==WIDTH-1);
}
void InitHead(short ms) throw() {		//初始化蛇头.
	HideCursor();
	int a[4]= {2,4,6,8};
	int x;
	switch(ms) {
		case WALK:
			x=0;
			break;
		case GO:
			x=1;
			break;
		case RUN:
			x=2;
			break;
		case FAST:
			x=3;
			break;
		default:
			x=3;
			break;
	}
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
					Print_Fame(a[i][0],a[i][1],a[i][2]);
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
			cout<<" 散步  行走  奔跑  疯狂  随机\n\n";
			cout<<"左、右方向键切换,回车选择\n";
			Print_Fame(2,a[f][0],a[f][1]);
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

void Settings() throw() {
	HideCursor();
	system("cls");
	cout<<"请输入蛇头符号(默认为#):";
	HeadC=getche();
	cout<<"\n请输入蛇身符号(默认为*):";
	TailC=getche();
	cout<<"\n请输入食物符号(默认为0):";
	FruitC=getche();
	cout<<"\n更改设置成功!\n";
	system("pause");
}
void SeeSettings() throw() {
	HideCursor();
	system("cls");
	cout<<"当前蛇头符号为:"<<HeadC<<endl;
	cout<<"当前蛇身符号为:"<<TailC<<endl;
	cout<<"当前食物符号为:"<<FruitC<<endl;
	system("pause");
}
void About() throw() {
	HideCursor();
	system("cls");
	cout<<"贪吃蛇"<<VERSION<<" by 好吃的大水坑\n";
	Sleep(100);
	cout<<"更新时间:"<<TIME<<endl;
	Sleep(100);
	system("pause");
}
void ResetSettings() throw() {
	cin.clear();
	system("cls");
	HeadC='#';
	TailC='*';
	FruitC='0';
	cout<<"已将蛇头符号设置为#\n";
	cout<<"已将蛇身符号设置为*\n";
	cout<<"已将食物符号设置为0\n";
	system("pause");
}
short StartMenu() throw() {		//初始菜单.
	HideCursor();
	int f=0;
	bool flag=false;
	int a[6][2]= {2,2,11,6,24,6,37,6,50,2,59,6};
	while(1) {
		if(flag==false){
			system("cls");
			cout<<"**********贪吃蛇**********\n\n";
			cout<<" 开始     查看设置     更改设置     重置设置     关于     退出游戏\n";
		}
		else
			flag=false;
		Print_Fame(1,a[f][0],a[f][1]);
		gotoXY(0,4);
		cout<<"左、右方向键切换,回车选择\n";
		char c1=getch();
		if(c1!=0&&c1!=224&&c1!=-32) {
			if(c1==13) {		//回车.
				if(f==1)
					SeeSettings();
				else if(f==2)
					Settings();
				else if(f==3)
					ResetSettings();
				else if(f==4)
					About();
				else if(f==5)
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
				if(f==0)
					f=5;
				else
					f--;
			} else if(c2==RIGHT) {
				if(f==5)
					f=0;
				else
					f++;
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

