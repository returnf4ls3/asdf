#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x-1, y-1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawCup() {
	gotoxy(5, 1);
	printf("___");
	gotoxy(4, 2);
	printf("/");
	gotoxy(8, 2);
	printf("\\");
	gotoxy(3, 3);
	printf("/");
	gotoxy(9, 3);
	printf("\\");
	gotoxy(2, 4);
	printf("/");
	gotoxy(10, 4);
	printf("\\");
	gotoxy(1, 5);
	printf("________________");
}

int main() {
	drawCup();
	
	return 0;
} 
