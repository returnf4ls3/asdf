#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x-1, y-1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawCup(int centerX, int centerY) {
	int p = 0;
	for (int i = 0; i < 3; i++) {
		gotoxy(5+centerX+p, 1+centerY);
		printf("___");
		gotoxy(4+centerX+p, 2+centerY);
		printf("/");
		gotoxy(8+centerX+p, 2+centerY);
		printf("\\");
		gotoxy(3+centerX+p, 3+centerY);
		printf("/");
		gotoxy(9+centerX+p, 3+centerY);
		printf("\\");
		gotoxy(2+centerX+p, 4+centerY);
		printf("/");
		gotoxy(10+centerX+p, 4+centerY);
		printf("\\");
		p += 11;
	}
	
	gotoxy(1+centerX, 5+centerY);
	printf("_________________________________");
}

int main() {
	drawCup(0, 0);
	
	return 0;
} 
