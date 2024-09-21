// ver 1.0 main file of game
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

#define BASEPOS_X 0
#define BASEPOS_Y 0
#define TEXT_SPEED 0.001

void gotoxy(int x, int y) {
	COORD pos = { x-1+BASEPOS_X, y-1+BASEPOS_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void animateText(char text[]) {
	int len = strlen(text);
	
	for (int i = 0; i < len; i++) {
		char slice[3];
		strncpy(slice, &text[i], 1);
		slice[1] = '\0';
		
		printf("%s", slice);
		Sleep((int)(TEXT_SPEED * 1000));
	}
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

int main() {
	char name[20];
	char buffer[200];
	int selected = 0;
	
	srand(time(NULL));
	
	printf("이름 입력 ");
	scanf("%s", name);
	
	system("cls");
	
	sprintf(buffer,"내 이름은 %s.\n반지하에 사는 길거리 어디에서나 볼 법한사람이다.", name);
	animateText(buffer);
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
	
	return 0;
}
