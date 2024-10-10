#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void start(void);

typedef struct enemy {
	int x;
	int y;
	int isAlive;
}Enemy;

typedef struct bullet {
	int x;
	int y;
	int isAlive;
	int dir;
}Bullet;

int ch[2][2];
Enemy eArr[100];
Bullet bArr[100];

void gotoxy(int x, int y, char* z) {              //원하는 위치에 텍스트 쓰는 함수
	COORD coord = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%s", z);
}

void summon(int idx) {
	srand(time(NULL));
	eArr[idx].x = rand() % 24 + 1;
	eArr[idx].y = rand() % 19 + 1;
	gotoxy(eArr[idx].x, eArr[idx].y, "1 ");
	eArr[idx].isAlive = 1;
}



void CursorView() {									//콘솔 커서 없애는 함수
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = FALSE;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void map(void) {                                        //맵 만드는 함수
	for (int i = 0; i < 25; i++)
	{
		gotoxy(i, 0, "■");
	}
	for (int i = 0; i < 20; i++)
	{
		gotoxy(0, i, "■");
		gotoxy(25, i, "■");
	}
	for (int i = 0; i < 25; i++)
	{
		gotoxy(i, 20, "■");
	}
	gotoxy(25 ,20 , "■");
}

void move(int idx) {
	int dx = ch[0][0] - eArr[idx].x;
	int dy = ch[0][1] - eArr[idx].y;
	gotoxy(eArr[idx].x, eArr[idx].y, "  ");
	if (abs(dx) > abs(dy)) {
		if (dx > 0) {
			eArr[idx].x += 1;
		}
		else {
			eArr[idx].x -= 1;
		}
	}
	else {
		if (dy > 0) {
			eArr[idx].y += 1;
		}
		else {
			eArr[idx].y -= 1;
		}
	}
	gotoxy(eArr[idx].x, eArr[idx].y, "⊙");
}

int main(void) {
	map();
	CursorView();
	start();
}

void start(void) {
	int m;
	int count;
	int b;
	int timer[4];
	int cur[4];
	for (int i = 0; i < 4; i++) {
		timer[i] = time(NULL);
		cur[i] = time(NULL);
	}
	int a = 0;
	int dir = 2;
	ch[0][0] = 12;
	ch[0][1] = 10;
	for (int i = 0; i < 100; i++) {
		eArr[i].x = 0;
		eArr[i].y = 0;
		eArr[i].isAlive = 0;
		bArr[i].x = 0;
		bArr[i].y = 0;
		bArr[i].isAlive = 0;
		bArr[i].dir = 0;
	}
	gotoxy(ch[0][0], ch[0][1], "■");
	while (1) {
		if (_kbhit())
		{
			do
			{
				a = _getch();
			} while (a == 224);
			ch[1][0] = ch[0][0];
			ch[1][1] = ch[0][1];
			switch (a) {
			case 72:
				if (ch[0][1] > 1) {
					ch[0][1] -= 1;
					dir = 0;
				}
				break;
			case 77:
				if (ch[0][0] < 24) {
					ch[0][0] += 1;
					dir = 1;
				}
				break;
			case 80:
				if (ch[0][1] < 19) {
					ch[0][1] += 1;
					dir = 2;
				}
				break;
			case 75:
				if (ch[0][0] > 1) {
					ch[0][0] -= 1;
					dir = 3;
				}
				break;
			case 32:
				for (int i = 0; i < 100; i++) {
					if (bArr[i].isAlive == 0) {
						bArr[i].x = ch[0][0];
						bArr[i].y = ch[0][1];
						bArr[i].dir = dir;
						bArr[i].isAlive = 1;
						break;
					}
				}
				break;
			}
			gotoxy(ch[0][0], ch[0][1], "■");
			if (a != 32) {
				gotoxy(ch[1][0], ch[1][1], "  ");
				gotoxy(ch[0][0], ch[0][1], "■");
			}
		}
		for (int i = 0; i < 100; i++) {
			if (bArr[i].isAlive == 1) {
				//gotoxy(bArr[i].x, bArr[i].y, "  ");
				gotoxy(ch[0][0], ch[0][1], "■");
				if (bArr[i].dir == 0) {
					bArr[i].y -= 1;
				}
				else if (bArr[i].dir == 1) {
					bArr[i].x += 1;
				}
				else if (bArr[i].dir == 2) {
					bArr[i].y += 1;
				}
				else if (bArr[i].dir == 3) {
					bArr[i].x -= 1;
				}
				if (bArr[i].x > 0 && bArr[i].y > 0 && bArr[i].x < 25 && bArr[i].y < 20) {
					gotoxy(bArr[i].x, bArr[i].y, "○");
				}
				else {
					bArr[i].isAlive = 0;
				}
			}
		}
		cur[0] = time(NULL);
		m = time(NULL) % 100 + 1;
		if (cur[0] - timer[0] >= 1) {
			timer[0] = cur[0];
			for (int i = 0; i < 100; i++) {
				if (eArr[i].isAlive == 0) {
					summon(i);
					break;
				}
			}
		}
		cur[1] = time(NULL);
		if (cur[1] - timer[1] >= 1) {
			timer[1] = cur[1];
			for (int i = 0; i < 100; i++) {
				if (eArr[i].isAlive == 1) {
					move(i);
				}
			}
		}
	}
}