#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//inference-->https://www.youtube.com/watch?v=kWdzxJmVOUs   
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void MoveCursorPosition(int x,int y)//移動光標位置 
{
	//指定一個座標 
	COORD pos;
	pos.X=x;	//指定橫坐標 
	pos.Y=y;	//縱坐標 
	
	//獲得cmd的打印控制 
	HANDLE  hCmdWindow;
	hCmdWindow=GetStdHandle(STD_OUTPUT_HANDLE);
	
	//移動光標到 pos變量指定位置 
	SetConsoleCursorPosition(hCmdWindow, pos);
	return;
}

 void PrintAtCursor(char *ch, int x,int y){
 	MoveCursorPosition(x,y);
	printf("%s",ch);
	//利用函數將移動光標跟打印和在一起 
	//	MoveCursorPosition(0,0);
	//  printf("");
 } 
 //修改當前打印將使用得顏色(並保存修改以前的設置) 
 void SetColor(WORD NewColor,WORD *old/*記住修改前的螢幕屬性*/)
 {
 	//1.獲得打印窗口操作句柄 
 	HANDLE hOutput;
 	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//2.記住當前正在使用的顏色
	if(old){
		CONSOLE_SCREEN_BUFFER_INFO Info;
		GetConsoleScreenBufferInfo(hOutput,&Info);
		*old = Info.wAttributes; 
	}
	//3.根據函數參數指定的顏色值， 修改屏幕的打印顏色屬性
	SetConsoleTextAttribute(hOutput,NewColor);
	return;
 } 
 //https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/color
#define COLOR_GREEN_GREEN 0x22//window API DOS COLOR
#define COLOR_GREEN_PURPLE 0x25
#define COLOR_GRAY_BLUE 0x81
#define COLOR_YELLOW_RED 0xEC

void create_game_area(int width, int height)
{
	int x = 0;
	int y = 0;
	int width_index =0;
	int height_index =0;
}

int main() {
	
//  system("chcp");顯示窗口cmd的顯示字符集
//	system("chcp 65001");調整cmd窗口輸出字符集為utf-8 用來顯示中文字幅集 英文為半形 中文全形占兩格 
	
	system("cls");
	
	WORD old_screen_attr=0;	//保存舊顏色 
	
	SetColor(COLOR_GREEN_PURPLE,&old_screen_attr);//set 打印色為綠底紫字 
	PrintAtCursor("green background, green word",0,10);//print
	SetColor(old_screen_attr,NULL);  //reset color
	printf("綠底綠字");
	
	PrintAtCursor("☆☆☆☆☆☆",0,0);
	
	PrintAtCursor("☆☆☆☆☆☆",0,0);
	 
	system("pause");
	 
	PrintAtCursor("   ",2,0);//space 可以蓋掉字元符號 
	return 0;
}
