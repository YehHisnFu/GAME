#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//inference-->https://www.youtube.com/watch?v=kWdzxJmVOUs   
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void MoveCursorPosition(int x,int y)//���ʥ��Ц�m 
{
	//���w�@�Ӯy�� 
	COORD pos;
	pos.X=x;	//���w��� 
	pos.Y=y;	//�a���� 
	
	//��ocmd�����L���� 
	HANDLE  hCmdWindow;
	hCmdWindow=GetStdHandle(STD_OUTPUT_HANDLE);
	
	//���ʥ��Ш� pos�ܶq���w��m 
	SetConsoleCursorPosition(hCmdWindow, pos);
	return;
}

 void PrintAtCursor(char *ch, int x,int y){
 	MoveCursorPosition(x,y);
	printf("%s",ch);
	//�Q�Ψ�ƱN���ʥ��и򥴦L�M�b�@�_ 
	//	MoveCursorPosition(0,0);
	//  printf("");
 } 
 //�ק��e���L�N�ϥαo�C��(�ëO�s�ק�H�e���]�m) 
 void SetColor(WORD NewColor,WORD *old/*�O��ק�e���ù��ݩ�*/)
 {
 	//1.��o���L���f�ާ@�y�` 
 	HANDLE hOutput;
 	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//2.�O���e���b�ϥΪ��C��
	if(old){
		CONSOLE_SCREEN_BUFFER_INFO Info;
		GetConsoleScreenBufferInfo(hOutput,&Info);
		*old = Info.wAttributes; 
	}
	//3.�ھڨ�ưѼƫ��w���C��ȡA �ק�̹������L�C���ݩ�
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
	
//  system("chcp");��ܵ��fcmd����ܦr�Ŷ�
//	system("chcp 65001");�վ�cmd���f��X�r�Ŷ���utf-8 �Ψ���ܤ���r�T�� �^�嬰�b�� ������Υe��� 
	
	system("cls");
	
	WORD old_screen_attr=0;	//�O�s���C�� 
	
	SetColor(COLOR_GREEN_PURPLE,&old_screen_attr);//set ���L�⬰�񩳵��r 
	PrintAtCursor("green background, green word",0,10);//print
	SetColor(old_screen_attr,NULL);  //reset color
	printf("�񩳺�r");
	
	PrintAtCursor("������������",0,0);
	
	PrintAtCursor("������������",0,0);
	 
	system("pause");
	 
	PrintAtCursor("   ",2,0);//space �i�H�\���r���Ÿ� 
	return 0;
}
