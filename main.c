// ver 1.0 main file of game
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define TEXT_SPEED 0.0000001 // edit it
#define INIT_POS 1
#define MAP_SIZE 4

int BASEPOS_X = 0;
int BASEPOS_Y = 0;		
int endSelection = 0;

void gotoxy(int x, int y) {
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// 2차원 배열로 이루어진 맵
const int originMap[MAP_SIZE][MAP_SIZE] = {
    {1, 6, 1, 8},
    {6, 2, 5, 4},
    {7, 2, 5, 4},
    {8, 3, 3, 7}
};

// 포지션 구조체
typedef struct {
    int x;
    int y;
} Pos;

// 게임 상태를 저장하는 구조체
typedef struct {
    char questionMap[MAP_SIZE][MAP_SIZE]; // 맞추고 있는 맵
    Pos player;                             // 플레이어 커서 위치
    Pos flipPos[2];                        // 뒤집은 카드 위치 저장
    int flipCount;                         // 뒤집은 카드 개수
    int spaceCount;                        // 뒤집은 횟수
    int matchedCardCount;                  // 맞춘 카드 개수
} GameManager;

// 콘솔 내부의 특정 위치로 커서를 이동하는 함수
void GotoX_Card(int x, int y) {
    COORD pos;
    pos.X = 2 * x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 콘솔 창 크기와 제목을 관리하는 함수
void SetConsoleView() {
    system("mode con:cols=65 lines=10");
}

// 키보드 입력 감지 및 입력된 키보드를 반환하는 함수
int GetKeyDown() {
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}

// 초기화 함수
void Init(GameManager *game) {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            game->questionMap[y][x] = '?'; // 물음표로 다 세팅
        }
    }
    game->player.x = 0;
    game->player.y = 0;
    game->flipCount = 0;
    game->spaceCount = 0;
    game->matchedCardCount = 0;
}

// 카드 뒤집는 함수
void FlipCard(GameManager *game) {
    if (game->questionMap[game->player.y][game->player.x] != '?') return;
    if (game->flipCount > 1) return; // 2장만 뒤집을 수 있음
    game->flipPos[game->flipCount].x = game->player.x;
    game->flipPos[game->flipCount].y = game->player.y;
    game->questionMap[game->player.y][game->player.x] = originMap[game->player.y][game->player.x] + '0';
    ++game->flipCount;
}

// 커서의 위치 이동
void MovePos(GameManager *game) {
    GotoX_Card(INIT_POS + (game->player.x * 3), INIT_POS + (game->player.y * 2) + 1);
    printf("  "); // 이전 위치 지우기

    // 키보드 입력을 받아서, 해당 위치로 이동
    int key = _getch();
    switch (key) {
        case 75: // LEFT
            if (game->player.x > 0) --game->player.x;
            break;
        case 77: // RIGHT
            if (game->player.x < MAP_SIZE - 1) ++game->player.x;
            break;
        case 72: // UP
            if (game->player.y > 0) --game->player.y;
            break;
        case 80: // DOWN
            if (game->player.y < MAP_SIZE - 1) ++game->player.y;
            break;
    }
}

// 화면에 그리기
void DrawMain(GameManager *game) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
    char c;
    for (int y = 0; y < MAP_SIZE; ++y) {
        GotoX_Card(INIT_POS, INIT_POS + (2 * y));
        for (int x = 0; x < MAP_SIZE; ++x) {
            c = game->questionMap[y][x];
            if (c != '?') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // GREEN
            }
            printf("[%c]   ", c);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
        }
    }

    // 플레이어 그리기
    GotoX_Card(INIT_POS + (game->player.x * 3), INIT_POS + (game->player.y * 2) + 1);
    printf(" ^");

    GotoX_Card(14, 1);
    printf("Count : %d", game->spaceCount);
}

// 카드 확인 함수
int CheckCard(GameManager *game) {
    if (game->flipCount == 2) {
        char c = '?';
        if (originMap[game->flipPos[0].y][game->flipPos[0].x] == originMap[game->flipPos[1].y][game->flipPos[1].x]) {
            c = originMap[game->flipPos[0].y][game->flipPos[0].x] + '0';
            ++game->matchedCardCount;
        } else {
            Sleep(500);
        }
        game->questionMap[game->flipPos[0].y][game->flipPos[0].x] = c;
        game->questionMap[game->flipPos[1].y][game->flipPos[1].x] = c;
        game->flipCount = 0;
        ++game->spaceCount;

        if (game->matchedCardCount >= 8) {
            // 게임 클리어
            DrawGameClear();
            Sleep(2000);
            system("cls");
            return 1;
        }
    }
    
    return 0;
}

// 게임 클리어 메시지 출력
void DrawGameClear() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // YELLOW
    GotoX_Card(10, 3);
    printf("=========================");
    GotoX_Card(10, 4);
    printf("======= C L E A R =======");
    GotoX_Card(10, 5);
    printf("=========================");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // WHITE
}

// 텍스트에서 가장 긴 줄의 길이와 총 라인 수를 계산하는 함수
void calculateTextSize(char text[], int *maxWidth, int *lineCount) {
    int currentWidth = 0;
    *maxWidth = 0;
    *lineCount = 1;  // 기본적으로 한 줄은 있다고 가정
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            (*lineCount)++;  // 줄바꿈이 있을 때마다 라인 수 증가
            if (currentWidth > *maxWidth) {
                *maxWidth = currentWidth;  // 가장 긴 줄의 길이를 저장
            }
            currentWidth = 0;  // 새로운 줄의 길이를 계산하기 위해 초기화
        } else {
            currentWidth++;
        }
    }
    
    // 마지막 줄도 확인
    if (currentWidth > *maxWidth) {
        *maxWidth = currentWidth;
    }
}

// 한 글자씩 애니메이션처럼 출력하는 함수
void animateText(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        char slice[2];
        strncpy(slice, &text[i], 1);
        slice[1] = '\0';  // 문자열 끝에 null 추가
        printf("%s", slice);  // 한 글자씩 출력
        Sleep((int)(TEXT_SPEED * 1000));  // 딜레이 추가
    }
    printf("\n\n");  // 각 텍스트 후 줄바꿈
}

// 콘솔 창의 중앙에 텍스트를 출력하는 함수
void gotoCenter(char text[]) {
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);  // 콘솔 크기를 가져옴

    int maxWidth, lineCount;
    calculateTextSize(text, &maxWidth, &lineCount);  // 텍스트의 최대 너비와 라인 수 계산

    // 콘솔 중앙 위치 계산
    int startX = (consoleWidth - maxWidth) / 2;
    int startY = (consoleHeight - lineCount) / 2;

    // 텍스트를 출력하기 위해 커서 위치를 이동시키며 출력
    int currentX = startX;
    int currentY = startY;

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            currentY++;  // 줄바꿈이 발생하면 세로 위치를 한 줄 내림
            currentX = startX;  // 가로 위치는 처음 중앙으로 초기화
        } else {
            pos.X = currentX;
            pos.Y = currentY;
            SetConsoleCursorPosition(hConsole, pos);  // 커서 이동
            char slice[2];
            strncpy(slice, &text[i], 1);  // 한 글자만 추출
            slice[1] = '\0';
            printf("%s", slice);  // 한 글자씩 출력
            Sleep((int)(TEXT_SPEED * 1000));  // 텍스트 속도에 맞춰 딜레이 적용
            currentX++;  // 다음 문자는 오른쪽으로 이동
        }
    }
}

// 콘솔의 마지막 줄에 메시지를 출력하는 함수
void printExitMessage() {
    int consoleWidth, consoleHeight;
    getConsoleSize(&consoleWidth, &consoleHeight);  // 콘솔 크기를 가져옴

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // 콘솔의 마지막 줄로 커서 이동
    pos.X = 0;
    pos.Y = consoleHeight - 1;
    SetConsoleCursorPosition(hConsole, pos);  // 마지막 줄로 커서 이동
}

/*void animateText(char text[]) {
	int len = strlen(text);
	
	for (int i = 0; i < len; i++) {
		char slice[3];
		strncpy(slice, &text[i], 1);
		slice[1] = '\0';
		
		gotoCenter(text);
		printf("%s", slice);
		Sleep((int)(TEXT_SPEED * 1000));
	}
	printExitMessage();
	printf("\n\n");
}*/

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
	
	system("mode con:cols=100 lines=25");
	
	printf("(이름을 작성해주세요) ");
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
	animateText("커튼이 젖혀져 밝은 빛이 눈을 감고 있는 내게도 선명히 보이는 듯 하다.");
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
	animateText("...불안한 새소리가 들리는 듯 하다.");
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
		/*int selection;

		animateText("뒤로가려면 0을 입력 ");
		while (1) {
			scanf("%d", &selection);
			if (selection == 0) break;
		}
		
		system("cls");
		*/
		getch();
	}
	
	int canOpenDoor = 0;
	
	while (1) {
		int selection;

		if (endSelection == 1) break;
		
		printRooms();
		
		printf("\n\n");
		printf("어디로 갈까? ");
		scanf("%d", &selection);
		
		if (selection == 1) {
			if (canOpenDoor == 1) {
				system("cls");
				animateText("문이 열린다.");
				Sleep(1000);
				sprintf(buffer, "%s: 응? 아까 분명히 잠겨 있었는데?", name);
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
				sprintf(buffer, "%s: ..이게 뭐지?", name);
				animateText(buffer);
				canOpenDoor = 2;
			} else if (canOpenDoor == 2) {
				animateText("문을 열었다.");
				Sleep(1000);
				animateText("앞에 상자와 그 안에 쪽지가 보인다.");
				Sleep(1000);
				animateText("쪽지엔 곰 고양이 금붕어 강아지 원숭이라고 쓰여있다.");
			} else {
				animateText("문이 밖에서 잠겼는지 철컹 소리와 함께 열리지 않는다.");
				Sleep(1000);
				getch();
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
					animateText("하양, 빨강, 노랑, 파랑색의 크레파스들이 가지런히 놓여 있다.");
					Sleep(1000);
					animateText("길이 순서대로 본다면 빨강,파랑, 하양, 노랑순으로 길다.");
					Sleep(1000);
				} else if (sel_table == 3) {
					animateText("어렸을때 많이 해본 게임이다.");
					Sleep(500);
					int skip = 0;
					while (1) {
						int selected;
						if (skip == 0) selected = userSelection("1. 게임을 한다.", "2. 무시 한다.");				
							
						if (selected == 1) {
							int result = cup();	// 1, 0
							
							if (result == 1) {
								printf("\n\n");	
								animateText("<문 앞으로 나가 보시오.>");
								Sleep(1000);
								sprintf(buffer, "%s: 응 문? 문은 잠겼는데?", name);
								animateText(buffer);
								Sleep(1000);
								canOpenDoor = 1;
								break;
							} else {
								while (1) {
									int	selected2 = userSelection("1. 다시 한다.", "2. 무시 한다.");
									
									skip = 1;
									if (selected2 == 1) {
										selected = 1;
										break;
									} else {
										selected = 2;
										break;
									}
								}
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
			animateText("구식전화기다. 전화를 걸 수 있는 상태인 거 같다.");
			while (1) {
				if (endSelection == 1) break;
				int selected = userSelection("1. 전화번호를 입력한다.", "2. 무시 한다.");
				char text[100];
				char pw[100];
			
				if (selected == 1) {
					while (1) {
						printf("전화번호 입력: ");
						scanf("%s", text);
						if (strcmp(text, "4583-8194") == 0) {
							Sleep(1000);
							printf("\n\n");
							animateText("\"..암호를 말하라\"");
							scanf("%s", pw);
							printf("\n");
							if (strcmp(pw, "53276") == 0) {
								Sleep(2500);
								animateText("정답이다.");
								Sleep(1000);
								animateText("띵! 메세지가 왔다.");
								Sleep(1000);
								animateText("<메세지> 'www.qkdxkfcnfwja.com'");
								Sleep(1000);
								sprintf(buffer, "%s: ...이게 뭐야?", name);
								animateText(buffer);
								Sleep(2500);
								animateText("<메세지창> '신뢰할 수 없는 링크입니다. 그래도 이동하시겠습니까?'");
								Sleep(1000);
								sprintf(buffer, "%s: ...");
								while (1) {
									int selected = userSelection("1. 링크를 누른다.", "2. 링크를 누르지 않는다.");
									
									if (selected == 1) {
										break;
									} else {
										Sleep(2500);
										animateText("전화가 온다.\n\n4583-8194 라고 쓰여있다.");
										Sleep(1000);
										sprintf(buffer, "%s: 여보세요?", name);
										animateText(buffer);
										Sleep(1000);
										animateText("\"..치지직..눌...라...치지직\"");
										Sleep(1000);
										sprintf(buffer, "%s: 뭐라고요? 누르라고요?", name);
										animateText(buffer);
										Sleep(1000);
										animateText("띡-");
										Sleep(1000);
										animateText("전화가 끊겼다.");
										Sleep(1000);
										sprintf(buffer, "%s: 뭐야 자기 맘대로 끊고.. 짜증나게.. 그나저나 링크 누르라고..?", name);
										animateText(buffer);
										Sleep(1000);
										animateText("<메세지창> '신뢰할 수 없는 링크입니다.  그래도 이동하시겠습니까?'");
										Sleep(1000);
										sprintf(buffer, "%s: ..예", name);
										animateText(buffer);
										Sleep(1000);
										break;
									}
								}
								endSelection = 1;
								break;
							} else {
								animateText("뚜- 뚜- 뚜- 뚜-");
								Sleep(1000);
								animateText("전화가 끊겼다.");
								Sleep(1000);
								sprintf(buffer, "%s: 뭐야..? 틀린건가? 다시 생각해보자.");
								animateText(buffer);
								Sleep(1000);
								break;
							}
						} else {
							printf("이 번호는 없는 번호입니다. 확인 후 다시 걸어주세요.");
							break;
						}
					}
				} else {
					break;
				}
			}
		}
	}
	
	sprintf(buffer, "%s: ..이게 뭐지??? 같은 숫자 카드 찾기 게임?", name);
	animateText(buffer);
	Sleep(2500);
	animateText("조작법\n\n방향키: 움직이기\n스페이스: 뒤집기");
	Sleep(1000);
	getch();
	
	SetConsoleView();
    GameManager game;
    Init(&game);
    
    while (1) {
        int key = GetKeyDown(); // 키 입력 받기
        if (key == 224) { // IS_ARROW
         	   MovePos(&game);
        }
        if (key == 32) { // SPACE
            FlipCard(&game);
        }
        DrawMain(&game);
        Sleep(100);
        int a = CheckCard(&game);
        if (a == 1) {
        	break;
		}
	}
	
	system("mode con:cols=100 lines=25");
	
	Sleep(1000);
	sprintf(buffer, "%s: 드디어 깼네.. 도대체 나한테 왜 이러는거야? 갑자기 방에 가둬서 게임을 시키지 ㅇㅏㄶ....", name);
	animateText(buffer);
	Sleep(1000);
	animateText("정신이 몽롱해진다.");
	Sleep(1000);
	sprintf(buffer, "%s: ...나", name);
	animateText(buffer);
	Sleep(1000);
	sprintf(buffer, "%s: ..어?", name);
	animateText(buffer);
	Sleep(1000);
	animateText("시간은 06:42이다.");
	Sleep(1000);
	animateText("언제나 봐오던 우리집");
	Sleep(1000);
	animateText("익숙한 침대, 익숙한 집 구조 아무리 둘러 봐도 내가 있던 그 기이한 집은 없다.");
	Sleep(1000);
	sprintf(buffer, "%s: ..아잇 첫 알바날에 이런 똥 꿈을 꾸다니.. 칫..", name);
	animateText(buffer);
	Sleep(1000);
	animateText("나는 알바에 나가려고 옷을 갈아입는다.");
	Sleep(1000);
	animateText("내 핸드폰 화면엔.. 4583-8194라는 번호로..부재중 전화가 와있다.");
	Sleep(1000);
	animateText("-끝-");
	Sleep(1000);
	
	return 0;
}
