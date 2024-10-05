// ver 1.0 main file of game
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define TEXT_SPEED 0.000001 // edit it

int BASEPOS_X = 0;
int BASEPOS_Y = 0;


void gotoxy(int x, int y) {
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoCenter(int x, int y, char text[]) {
	BASEPOS_X = (int)((strlen(text)) / 2);
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
 
void animateText(char text[]) {
	int len = strlen(text);
	
	for (int i = 0; i < len; i++) {
		char slice[3];
		strncpy(slice, &text[i], 1);
		slice[1] = '\0';
		
		//gotoCenter(i, 0, text);
		printf("%s", slice);
		Sleep((int)(TEXT_SPEED * 1000));
	}
	//BASEPOS_Y++;
	printf("\n\n");
}

int userSelection(char sentence1[], char sentence2[]) {
	int selected = 0;
	
	printf("\n[선택]\n");
	animateText(sentence1);
	Sleep(1000);
	animateText(sentence2);
		
	printf("선택: ");
	scanf("%d", &selected);	
	
	if (selected == 1 || selected == 2) {
		return selected;
	} else {
        printf("다시 입력해주세요.\n");
        return 0;
    }
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
	char name[20];
	char buffer[200];
	int selected = 0;
	
	srand(time(NULL));
	
	printf("내 이름은 ");
	scanf("%s", name);
	printf("\n");
	Sleep(1000);
	animateText("반지하에 사는 길거리 어디에서나 볼 법한사람이다.");
	Sleep(1000);
	animateText("피곤했던 오늘을 보내고 잠에 들려고 한다.");
	Sleep(1000);
	animateText("오늘 따라 잠이 들지 않지만 내일을 위해 억지로 눈을 감는다.");
	Sleep(1000);
	animateText("한밤중인데도, 커튼을 닫은 창문밖이 이질적으로 밝아 보인다.");
	Sleep(1000);
	sprintf(buffer, "%s: 몇시..지..?", name);
	animateText(buffer);
	Sleep(1000);
	animateText("뭔가 집에서 진동과 함께 덜컹 거리는 소리가 난다.");
	Sleep(1000);
	animateText("이상한 굉음과 함께 집이 크게 흔들린다.");
	Sleep(1000);
	animateText("커튼이 젖혀져 밝은 빛이 감고 내 눈에도 선명히 보이는 듯 하다.");
	Sleep(1000);
	
	while (1) {	
		selected = userSelection("1. 일어나서 주변을 살핀다.", "2. 다시 눈을 감는다.");
		
		if (selected == 1) {
			printf("\n");
			animateText("눈을 서서히 떴다.");
			Sleep(1000);
			animateText("하지만 피곤함과 더불어 주변이 너무 밝아 앞이 보이지 않아, 눈을 뜨는 것을 포기하고 다시 눕는다.");
			Sleep(1000);
			printf("\n");
		} else if (selected == 2) {
			printf("\n");
			animateText("이상한 진동과 소리를 꿈이라고 믿고 다시 눈을 감는다.");
			break;
		}
	}
	
	animateText("갑자기 주변이 고요해진다.. 편안하다..");
	Sleep(1000);
	animateText("아까는 감기지 않던 눈이 감긴다.");
	Sleep(1000);
	animateText("다시 잠에 든다.");
	Sleep(1000);
	animateText("…불안한 새소리가 들리는 듯 하다.");
	Sleep(1000);
	animateText("핸드폰으로 시간을 확인한다.");
	Sleep(1000);
	animateText("9시 56분");
	Sleep(1000);
	sprintf(buffer, "%s: 으..으아아악! 오늘 첫알바하는 날인데!!!", name);
	animateText(buffer);
	Sleep(1000);
	animateText("재빨리 핸드폰을 켜 카톡을 킨다.");
	Sleep(2500);
	printf("\n\n");
	printf("[Web발신]\n");
	printf("[유니컴즈] 이번 달 데이터 사용량 안내\n");
	printf("▶ 데이터 사용량 안내\n");
	printf(".......\n\n");
	Sleep(3000);
	
	sprintf(buffer, "%s: ..데이터? 와이파이 꺼졌나..?", name);
	animateText(buffer);
	Sleep(1000);
	animateText("공유기를 확인 하려고 일어난다. 눈 앞이 보이지 않아 커튼을 닫으려고 창문 쪽으로 걸어갔다.");
	Sleep(1000);
	sprintf(buffer, "%s: ..뭐야..? 여기는?", name);
	animateText(buffer);
	Sleep(1000);
	animateText("창밖에 아무것도 보이지 않는다.");
	Sleep(1000);
	animateText("내 눈이 보이지 않는게 아니라 정말 창밖에 아무것도 없다.");
	Sleep(1000);
	animateText("그저 빛 밖에 보이지 않는다.");
	Sleep(1000);
	animateText("..집 구조가 이상하다.");
	Sleep(1000);
	animateText("부엌도, 화장실도 보이지 않는다.");
	Sleep(1000);
	animateText("내 방이 아니다.");
	Sleep(1000);
	animateText("크고 안락하지만 음습해보이는.. 집을 더 탐색 해보자.");
	Sleep(1000);
	
	void printRooms() {
		printf("\n\n");
		animateText("1. 문");
		Sleep(500);
		animateText("2. 편지가 놓여있는 원형 탁자");
		Sleep(500);
		animateText("3. 전화기");
		Sleep(500);
	}
	
	void printLetters() {
		printf("\n\n");
		animateText("1) 붉은색 소인이 찍혀있는 편지");
		Sleep(1000);
		animateText("2) 몇번 썼는지 많이 닳아 있는 크레파스");
		Sleep(1000);
		animateText("3) 레트로 게임기");
		Sleep(1000);
		animateText("0) 뒤로가기");
		
	}
	
	void back() {
		int selection;

		animateText("뒤로가려면 0을 입력 ");
		while (1) {
			scanf("%d", &selection);
			if (selection == 0) break;
		}
		
		system("cls");
	}
	
	int canOpenDoor = 0;
	
	while (1) {
		int selection;
		
		printRooms();
		
		printf("\n\n");
		printf("어디로 갈까? ");
		scanf("%d", &selection);
		
		if (selection == 1) {
			if (canOpenDoor == 1) {
				animateText("문이 열린다.");
				Sleep(1000);
				sprintf(buffer, "%s: 응? 아까 분명히 잠겨 있었는데?");
				animateText(buffer);
				Sleep(1000);
				animateText("문 앞에 상자가 놓여있다.");
				Sleep(1000);
				animateText("상자안엔 쪽지가 놓여있다.");
				Sleep(1000);
				animateText("<쪽지>");
				Sleep(500);
				animateText("곰 고양이 금붕어 강아지 원숭이");
				Sleep(1000);
				sprintf(buffer, "%s: ..이게 뭐지?");
				animateText(buffer);
			} else {
				animateText("문이 밖에서 잠겼는지 철컹 소리와 함께 열리지 않는다.");
				back();
			}
		} else if (selection == 2) {
			while (1) {
				int sel_table;
				
				printLetters();
								
				scanf("%d", &sel_table);
				
				if (sel_table == 1) {
					printf("\n\n");
					animateText("(편지)");
					Sleep(500);
					animateText("글씨가 번져 잘 보이지 않지만 유추해보니 4583라는 숫자가 보인다.");
					Sleep(500);
					animateText("그리고 시가 보인다.");
					Sleep(1500);
					animateText("<시>");
					Sleep(500);
					animateText("동물들이 달리기 시합을 한다.");
					Sleep(500);
					animateText("파랑새는 1등,");
					Sleep(500);
					animateText("주황 금붕어가 2등,");
					Sleep(500);
					animateText("보라 고양이가 3등,");
					Sleep(500);
					animateText("노란 너구리는 4등,");
					Sleep(500);
					animateText("검정 곰은 5등,");
					Sleep(500);
					animateText("갈색 원숭이는 6등,");
					Sleep(500);
					animateText("초록 강아지는 7등,");
					Sleep(500);
					animateText("빨간 돼지는 8등,");
					Sleep(500);
					animateText("하얀염소가 9등이다.");
				} else if (sel_table == 2) {
					
				} else if (sel_table == 3) {
					animateText("어렸을때 많이 해본 게임이다.");
					Sleep(500);
					while (1) {
						selected = userSelection("1. 게임을 한다.", "2. 무시 한다.");
						
						if (selected == 1) {
							int result = cup();	// 1, 0
							
							if (result == 1) {
								animateText("<문 앞으로 나가 보시오.>");
								Sleep(1000);
								animateText("“응 문? 문은 잠겼는데?”");
								Sleep(1000);
								canOpenDoor = 1;
								break;
							} else {
								
							}
						} else if (selected == 2) {
							break;
						}
					}
				} else if (sel_table == 0) {
					break;
				} else {
        			printf("다시 입력해주세요.\n");
				}
				
				back();
			}
		} else if (selection == 3) {
			animateText("구식전화기다. 전화를 걸 수 있는 상태인 거 같다. ");
			back();	
		}
	}
	
	return 0;
}
