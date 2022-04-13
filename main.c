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



//�Ы�game area 
void create_game_area(int width, int height)
{
	int x = 0;
	int y = 0;
	int width_index =0;
	int height_index =0;
	WORD old_screen_attr=0;
	// �϶���R����� 
	SetColor(COLOR_GREEN_GREEN,&old_screen_attr);
	
	for(width_index=0 ; width_index <width ; width_index++){
		for(height_index=0 ; height_index <height ; height_index++){	
		//�q(2,1�y�Ц�m�}�l�Aø�s���C���ϰ�) 
		PrintAtCursor("�@",width_index*2,height_index);
		
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
	
	//�W���
	for(width_index=0 ; width_index <=width ; width_index++){
	PrintAtCursor("��",width_index*2,0);
	}
	//�����
		for(height_index=0 ; height_index <width ; height_index++){
	PrintAtCursor("��",0,height_index);
	}
	//�U���
		for(width_index=0 ; width_index <width ; width_index++){
	PrintAtCursor("��",width_index*2,height-1);
	}
	//�k���
		for(height_index=0 ; height_index <width ; height_index++){
	PrintAtCursor("��",width*2,height_index);
	}
	
	SetColor(old_screen_attr,NULL);
	
	return;
}

typedef struct SNAKE_NODE//�D�����@�Ӹ`�I 
{
	int x;
	int y;
	struct SNAKE_NODE *next_node;//�U�@�Ӹ`�I 		
}snake_node_s;

//�V�g�Y�D�K�[�@�ӷs�`�I 
//(x/y)���s�`�I�y��,�`�I�K�[��D���Y�� 
//��^�s���g�Y�D���D�Y���w 
snake_node_s* snake_add_node_to_head(snake_node_s *snake_head, int x, int y)
{
	snake_node_s* new_node =(snake_node_s*)malloc(sizeof(snake_node_s));
	
	//�s�`�I�y��
	new_node->x =x;
	new_node->y =y;
	 
	new_node->next_node= snake_head;//�N�`�I�s����D�Y
	return new_node; 
}

//��l�Ƴg�Y�D
//�bx/y���w��m
//���׬�number_of_node 
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
		PrintAtCursor("��",snake->x*2,snake->y);
		snake =snake->next_node;
	}
	while(snake){
		PrintAtCursor("��",snake->x*2,snake->y);
		snake =snake->next_node;
	}
	
	MoveCursorPosition(0,42);
	
	SetColor(old_screen_attr,NULL);
	
	return;
}


int main() {
	
//system("chcp");//��ܵ��fcmd����ܦr�Ŷ�
//system("chcp 65001");//�վ�cmd���f��X�r�Ŷ���utf-8 �Ψ���ܤ���r�T�� �^�嬰�b�� ������Υe��� 
	
	system("cls");
	
	system("mode con cols=140 lines=50");
	
	create_game_area(40,40);
	
	create_game_frame(40,40);
	
	snake_node_s* the_snake_head = NULL;//�g�Y�D�Y
	
	//�a�Ϥ����Ыسg�Y�D 
	 
	the_snake_head = snake_init(the_snake_head,40/2,40/2,1);
	
	print_snake(the_snake_head);
	
	return 0;
}

