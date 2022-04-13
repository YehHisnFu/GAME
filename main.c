#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


 //https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/color
#define COLOR_GREEN_GREEN 0x22//window API DOS COLOR
#define COLOR_PURPLE_PURPLE 0x55
#define COLOR_BLUE_BLUE 0x11
#define COLOR_GREEN_RED 0x2C


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



//創建game area 
void create_game_area(int width, int height)
{
	int x = 0;
	int y = 0;
	int width_index =0;
	int height_index =0;
	WORD old_screen_attr=0;
	// 區塊填充為綠色 
	SetColor(COLOR_GREEN_GREEN,&old_screen_attr);
	
	for(width_index=0 ; width_index <width ; width_index++){
		for(height_index=0 ; height_index <height ; height_index++){	
		//從(2,1座標位置開始，繪製成遊戲區域) 
		PrintAtCursor("　",width_index*2,height_index);
		
		}
	}
	
	SetColor(old_screen_attr,NULL);
	
	return;
}
 
void create_game_frame(int width,int height)
{
	int width_index =0;
	int height_index =0;
	WORD old_screen_attr=0;
	SetColor(COLOR_BLUE_BLUE,&old_screen_attr);
	
	//上邊框
	for(width_index=0 ; width_index <=width ; width_index++){
	PrintAtCursor("Ｘ",width_index*2,0);
	}
	//左邊框
		for(height_index=0 ; height_index <width ; height_index++){
	PrintAtCursor("Ｘ",0,height_index);
	}
	//下邊框
		for(width_index=0 ; width_index <width ; width_index++){
	PrintAtCursor("Ｘ",width_index*2,height-1);
	}
	//右邊框
		for(height_index=0 ; height_index <width ; height_index++){
	PrintAtCursor("Ｘ",width*2,height_index);
	}
	
	SetColor(old_screen_attr,NULL);
	
	return;
}

typedef struct SNAKE_NODE//蛇身的一個節點 
{
	int x;
	int y;
	struct SNAKE_NODE *next_node;//下一個節點 		
}snake_node_s;

//向貪吃蛇添加一個新節點 
//(x/y)為新節點座標,節點添加到蛇的頭部 
//返回新的貪吃蛇的蛇頭指針 
snake_node_s* snake_add_node_to_head(snake_node_s *snake_head, int x, int y)
{
	snake_node_s* new_node =(snake_node_s*)malloc(sizeof(snake_node_s));
	
	//新節點座標
	new_node->x =x;
	new_node->y =y;
	 
	new_node->next_node= snake_head;//將節點連接到蛇頭
	return new_node; 
}

//初始化貪吃蛇
//在x/y指定位置
//長度為number_of_node 
snake_node_s* snake_init(snake_node_s* snake_head,int x, int y, int number_of_node){
	while(number_of_node--){
		snake_head = snake_add_node_to_head(snake_head,x,y);
		x=x+2;
	}
	return snake_head;
}

void print_snake(snake_node_s* snake){
	
	WORD old_screen_attr=0;
	
	SetColor(COLOR_GREEN_RED,&old_screen_attr);	
	
	if(snake){
		PrintAtCursor("Ｏ",snake->x*2,snake->y);
		snake =snake->next_node;
	}
	while(snake){
		PrintAtCursor("ｏ",snake->x*2,snake->y);
		snake =snake->next_node;
	}
	
	MoveCursorPosition(0,42);
	
	SetColor(old_screen_attr,NULL);
	
	return;
}


int main() {
	
//system("chcp");//顯示窗口cmd的顯示字符集
//system("chcp 65001");//調整cmd窗口輸出字符集為utf-8 用來顯示中文字幅集 英文為半形 中文全形占兩格 
	
	system("cls");
	
	system("mode con cols=140 lines=50");
	
	create_game_area(40,40);
	
	create_game_frame(40,40);
	
	snake_node_s* the_snake_head = NULL;//貪吃蛇頭
	
	//地圖中央創建貪吃蛇 
	 
	the_snake_head = snake_init(the_snake_head,40/2,40/2,1);
	
	print_snake(the_snake_head);
	
	return 0;
}

