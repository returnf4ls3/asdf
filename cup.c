#include <stdio.h>
#include <windows.h>

#define BASEPOS_X 0
#define BASEPOS_Y 0

void gotoxy(int x, int y) {
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawCup(int centerX, int centerY) {	
	gotoxy(5+centerX, 1+centerY);
	printf("___");
	gotoxy(4+centerX, 2+centerY);
	printf("/");
	gotoxy(8+centerX, 2+centerY);
	printf("\\");
	gotoxy(3+centerX, 3+centerY);
	printf("/");
	gotoxy(9+centerX, 3+centerY);
	printf("\\");
	gotoxy(2+centerX, 4+centerY);
	printf("/");
	gotoxy(10+centerX, 4+centerY);
	printf("\\");
}

void drawCups(int centerX, int centerY, int sel, int answer) {			
	int p = 0;

	system("cls");
	
	if (sel != 0) {
		if (sel == 1) {
			p = 0;
			if (sel == answer) {
				drawCup(centerX+p, centerY-1);
				gotoxy(6+centerX+p, 4+centerY);
				printf("■");
			} else {
				drawCup(centerX+p, centerY-1);
			}
			p += 11;
			drawCup(centerX+p, centerY);
			p += 11;
			drawCup(centerX+p, centerY);
			
			return;
		} else if (sel == 2) {
			p = 0;
			drawCup(centerX+p, centerY);
			p += 11;
			if (sel == answer) {
				drawCup(centerX+p, centerY-1);
				gotoxy(6+centerX+p, 4+centerY);
				printf("■");
			} else {
				drawCup(centerX+p, centerY-1);
			}
			p += 11;
			drawCup(centerX+p, centerY);
			
			return;
		} else if (sel == 3) {
			p = 0;
			drawCup(centerX+p, centerY);
			p += 11;
			drawCup(centerX+p, centerY);
			p += 11;
			if (sel == answer) {
				drawCup(centerX+p, centerY-1);
				gotoxy(6+centerX+p, 4+centerY);
				printf("■");
			} else {
				drawCup(centerX+p, centerY-1);
			}
			
			return;
		}
	}

	for (int i = 0; i < 3; i++) {
		drawCup(centerX+p, centerY);
		p += 11;
	}
	
	gotoxy(1+centerX, 5+centerY);
	printf("_________________________________\n\n");
}

void drawCupsAtCenter(int sel, int answer) {
	int centerX = 33;
	int centerY = 15;
	
	int p = 0;

	system("cls");
	
	if (sel != 0) {
		if (sel == 1) {
			p = 0;
			if (sel == answer) {
				drawCup(centerX+p, centerY-1);
				gotoxy(6+centerX+p, 4+centerY);
				printf("■");
			} else {
				drawCup(centerX+p, centerY-1);
			}
			p += 11;
			drawCup(centerX+p, centerY);
			p += 11;
			drawCup(centerX+p, centerY);
			
			return;
		} else if (sel == 2) {
			p = 0;
			drawCup(centerX+p, centerY);
			p += 11;
			if (sel == answer) {
				drawCup(centerX+p, centerY-1);
				gotoxy(6+centerX+p, 4+centerY);
				printf("■");
			} else {
				drawCup(centerX+p, centerY-1);
			}
			p += 11;
			drawCup(centerX+p, centerY);
			
			return;
		} else if (sel == 3) {
			p = 0;
			drawCup(centerX+p, centerY);
			p += 11;
			drawCup(centerX+p, centerY);
			p += 11;
			if (sel == answer) {
				drawCup(centerX+p, centerY-1);
				gotoxy(6+centerX+p, 4+centerY);
				printf("■");
			} else {
				drawCup(centerX+p, centerY-1);
			}
			
			return;
		}
	}

	for (int i = 0; i < 3; i++) {
		drawCup(centerX+p, centerY);
		p += 11;
	}
	
	printf("\n");
}

// return value is 0 or 1
int cup() {
	int selected = 0;
	int ans = rand() % 3 + 1;
	
	drawCupsAtCenter(0, 0);
	
	printf("정답: ");
	scanf("%d", &selected);
	
	drawCupsAtCenter(selected, ans);
		
	if (selected == ans) {
		return 1;
	} else {
		return 0;
	}
}

int main() {
	int a;
	
	srand(time(NULL));
	
	a = cup(); 
	
	if (a == 1) {
		gotoxy(1, 6);
		printf("정답");
	} else {
		gotoxy(1, 6);
		printf("오답");
	}
	
	return 0;
}
