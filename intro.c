#include <stdio.h>
#include <windows.h>

int BASEPOS_X = 0;
int BASEPOS_Y = 0;		
int endSelection = 0;

void gotoxy(int x, int y) {
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void t() {
	gotoxy(1, 1);
	printf("■■■■■");
	gotoxy(13, 1);
	printf("■");
	gotoxy(1, 2);
	printf("■");
	gotoxy(13, 2);
	printf("■");
	gotoxy(1, 3);
	printf("■■■■■");
	gotoxy(13, 3);
	printf("■■■");
	gotoxy(1, 4);
	printf("■");
	gotoxy(13, 4);
	printf("■");
	gotoxy(1, 5);
	printf("■■■■■");
	gotoxy(13, 5);
	printf("■");
	gotoxy(3, 7);
	printf("■■■■■");
	gotoxy(11, 8);
	printf("■");
	gotoxy(3, 9);
	printf("■■■■■");
	gotoxy(3, 10);
	printf("■");
	gotoxy(3, 11);
	printf("■■■■■");
}

void c() {
	gotoxy(7, 1);
	printf("■");
	gotoxy(1, 2);
	printf("■■■■■■■");
	gotoxy(5, 3);
	printf("■");
	gotoxy(9, 3);
	printf("■");
	gotoxy(3, 4);
	printf("■");
	gotoxy(11, 4);
	printf("■");
	gotoxy(3, 6);
	printf("■■■■■");
	gotoxy(7, 7);
	printf("■");
	gotoxy(7, 8);
	printf("■");
	gotoxy(3, 10);
	printf("■■■■■");
	gotoxy(11, 11);
	printf("■");
	gotoxy(3, 12);
	printf("■■■■■");
	gotoxy(3, 13);
	printf("■");
	gotoxy(3, 14);
	printf("■■■■■");
}

void intro() {
	// 방 
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
	gotoxy(1, 5);
	printf("■■■■");
	gotoxy(9, 5);
	printf("■");
	gotoxy(13, 5);
	printf("■");
	gotoxy(5, 7);
	printf("■■■");
	gotoxy(3, 8);
	printf("■");
	gotoxy(11, 8);
	printf("■");
	gotoxy(1, 9);
	printf("■");
	gotoxy(13, 9); 
	printf("■");
	gotoxy(1, 10);
	printf("■");
	gotoxy(13, 10);
	printf("■");
	gotoxy(3, 11);
	printf("■");
	gotoxy(11, 11);
	printf("■");
	gotoxy(5, 12);
	printf("■■■");
	// 탈
	BASEPOS_X = 20;
	gotoxy(1, 1);
	printf("■■■■■");
	gotoxy(13, 1);
	printf("■");
	gotoxy(1, 2);
	printf("■");
	gotoxy(13, 2);
	printf("■");
	gotoxy(1, 3);
	printf("■■■■■");
	gotoxy(13, 3);
	printf("■■■");
	gotoxy(1, 4);
	printf("■");
	gotoxy(13, 4);
	printf("■");
	gotoxy(1, 5);
	printf("■■■■■");
	gotoxy(13, 5);
	printf("■");
	gotoxy(3, 7);
	printf("■■■■■");
	gotoxy(11, 8);
	printf("■");
	gotoxy(3, 9);
	printf("■■■■■");
	gotoxy(3, 10);
	printf("■");
	gotoxy(3, 11);
	printf("■■■■■");
	// 출 
	BASEPOS_X = 40;
	gotoxy(7, 1);
	printf("■");
	gotoxy(1, 2);
	printf("■■■■■■■");
	gotoxy(5, 3);
	printf("■");
	gotoxy(9, 3);
	printf("■");
	gotoxy(3, 4);
	printf("■");
	gotoxy(11, 4);
	printf("■");
	gotoxy(3, 6);
	printf("■■■■■");
	gotoxy(7, 7);
	printf("■");
	gotoxy(7, 8);
	printf("■");
	gotoxy(3, 10);
	printf("■■■■■");
	gotoxy(11, 11);
	printf("■");
	gotoxy(3, 12);
	printf("■■■■■");
	gotoxy(3, 13);
	printf("■");
	gotoxy(3, 14);
	printf("■■■■■");
	BASEPOS_X = 0;
}

int main() {
	system("mode con:cols=100 lines=25");
	intro();
	return 0;
}
