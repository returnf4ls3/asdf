   #include <stdio.h>
#include <windows.h>

int BASEPOS_X = 0;
int BASEPOS_Y = 0;		
int endSelection = 0;

void gotoxy(int x, int y) {
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void intro() {
	gotoxy(1, 1);
	printf("■");
	gotoxy(9, 1);
	printf("■");
	gotoxy(13, 1);
	printf("■");
	gotoxy(1, 2);
	printf("■");
	gotoxy(9, 2);
	printf("■");
	gotoxy(13, 2);
	printf("■");
	gotoxy(1, 3);
	printf("■■■■");
	gotoxy(9, 3);
	printf("■");
	gotoxy(13, 3);
	printf("■■■");
	gotoxy(1, 4);
	printf("■");
	gotoxy(9, 4);
	printf("■");
	gotoxy(13, 4);
	printf("■");
} 

int main() {
	intro();
	
	return 0; 
}
