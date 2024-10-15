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
	int heart; 
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
int moving = 1000;
int Moving = 0;
int mh = 50;
int point = 0;
int mp = 0;

void gotoxy(int x, int y, char* z) {              //원하는 위치에 텍스트 쓰는 함수
	COORD coord = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%s", z);
}

void summon(int idx) {
	srand(time(NULL));
	eArr[idx].x = rand() % 23 + 1;
	eArr[idx].y = rand() % 19 + 1;
	gotoxy(eArr[idx].x, eArr[idx].y, "⊙ ");
	eArr[idx].isAlive = 1;
	eArr[idx].heart = mh;
}



void CursorView() {									//콘솔 커서 없애는 함수
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = FALSE;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gameover(void) {
	int a;
	gotoxy(10, 17, "GAME OVER");
	gotoxy(10, 18, "RETRY?(PRESS ENTER)");
	while (1) {
		if (_kbhit()) {
			a = _getch();
			if (a == 13) {
				start();
			}
		}
	}
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
	int a = 0;
	map();
	CursorView();
	gotoxy(10, 9, "┎-─┻─┳─━=- ");
	gotoxy(10, 10, "G U N N E R");
	while (1) {
		if (_kbhit()) {
			a == _getch();
			if (a == 13) {
				start();
			}
		}
	}
}

void start(void) {
	system("cls");
	map();
	point = 0;
	int counter[2];
	int Fak = 0;
	int Fakx = time(NULL) % 23 + 1;                      //구급상자 x좌표
	int Faky = time(NULL) % 19 + 1;                      //구급상자 y좌표
	int m;
	int cooltime = 0;
	int cool = 0;
	int magazine = 25;
	int hx = 35;
	int hearts = 5;
	int count[2];
	for (int i = 0; i < 2; i++) {
		count[i] = 0;
	}
	int b;
	int timer[4];
	int cur[4];
	int Plus = time(NULL);
	int Minus = time(NULL);
	for (int i = 0; i < 6; i++) {
		timer[i] = time(NULL);
		cur[i] = time(NULL);
		counter[i] = time(NULL);
	}
	timer[3] = 0;
	cur[3] = 0;
	timer[1] = GetTickCount();
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
	gotoxy(ch[0][0], ch[0][1], "");
	while (1) {
		if (hearts == 0) {
			gameover();
		}
		point += 1;
		gotoxy(33, 13, "point : ");
		printf("%d", point / 1000);
		Plus = time(NULL);
		if (Plus - Minus >= 10) {
			Minus = Plus;
			gotoxy(Fakx, Faky, "  ");
			Fakx = time(NULL) % 23 + 1;
			Faky = time(NULL) % 19 + 1;
			Fak = 1;
			gotoxy(Fakx, Faky, "+");
			gotoxy(1, 0, "■");
		}
		for (int i = 0; i < 100; i++) {
			if (bArr[i].x == Fakx && bArr[i].y == Faky) {
				Fakx = 1;
				Faky = 0;
				Fak = 0;
				gotoxy(1, 0, "■");
			}
			if (eArr[i].x == Fakx && eArr[i].y == Faky) {
				Fakx = 1;
				Faky = 0;
				Fak = 0;
				gotoxy(1, 0, "■");
			}
		}
		if (ch[0][0] == Fakx && Faky == ch[0][1] && Fak == 1) {
			if (hearts < 5) {
				Fak = 0;
				hearts += 1;
				Fakx = 1;
				Faky = 0;
				gotoxy(1, 0, "■");
			}
		}
		counter[0] = time(NULL);
		if (300 > counter[0] - counter[1] && counter[0] - counter[1] > 180) {
			mh = 100;
			moving = 650;
		}
		else if (counter[0] - counter[1] > 300) {
			mh = 150;
			moving = 300;
		}
		if (magazine < 1) {
			cur[3] += 1;
			gotoxy(31, 16, " ");
			printf("%d", cur[3] / 1000);
			if (cur[3] - timer[3] >= 5000) {
				cur[3] = 0;
				magazine = 25;
				gotoxy(31, 16, "  ");
			}
		}
		gotoxy(30, 15, "25 / ");
		gotoxy(32, 15, " ");
		printf("%d", magazine);
		if (magazine < 10) {
			gotoxy(33, 15, " ");
		}
		count[1] += 1;
		for (int i = 0; i < 100; i++) {
			if (ch[0][0] == eArr[i].x && ch[0][1] == eArr[i].y) {
				if (count[1] > 1000) {
					count[1] = 0;
					hearts -= 1;
				}
			}
		}
		if (hearts <= 4) {
			for (int i = 8; i >= hearts * 2; i -= 2) {
				gotoxy(hx + i, 20, "□");
			}
		}
		gotoxy(31, 20, "heart : ");
		for (int i = 0; i < hearts * 2; i += 2) {
			gotoxy(hx + i, 20, "■");
		}
		gotoxy(33, 17, "Skill (F) = ");
		printf(" %d", cooltime / 1000);
		if (cooltime <= 10000) {
			gotoxy(40, 17, " ");
		}
		count[0] += 1;
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
				if (magazine > 0) {
					for (int i = 0; i < 100; i++) {
						if (bArr[i].isAlive == 0) {
							bArr[i].x = ch[0][0];
							bArr[i].y = ch[0][1];
							bArr[i].dir = dir;
							bArr[i].isAlive = 1;
							magazine -= 1;
							break;
						}
					}

				}
				break;
			case 70:
				if (hearts < 5 && cooltime == 0) {
					hearts += 1;
					cool = 1;
					cooltime = 19000;
				}
			case 102:
				if (hearts < 5 && cooltime == 0) {
					hearts += 1;
					cool = 1;
					cooltime = 19000;
				}
			}
			gotoxy(ch[0][0], ch[0][1], "■");
			if (a != 32) {
				gotoxy(ch[1][0], ch[1][1], "  ");
				gotoxy(ch[0][0], ch[0][1], "■");
			}
		}
		if (cool == 1 && cooltime >= 1) {
			cooltime -= 1;
		}
		if (cooltime == 0) {
			cool = 0;
		}
		for (int i = 0; i < 100; i++) {
			if (eArr[i].isAlive <= 0) {
				eArr[i].x = 7;
				eArr[i].y = 0;
			}
			for (int m = 0; m < 100; m++) {
				if (eArr[i].heart < 1) {
					eArr[i].isAlive = 0;
				}
				if (eArr[i].x == bArr[m].x && eArr[i].y == bArr[m].y) {
					eArr[i].heart -= 1;
				}
			}
			if (bArr[i].isAlive == 1) {
				if (count[0] >= 50) {
					count[0] = 0;
					gotoxy(bArr[i].x, bArr[i].y, "  ");
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
						for (int j = 0; j < 100; j++) {
							if (eArr[j].isAlive == 1) {
								gotoxy(eArr[j].x, eArr[j].y, "⊙");
							}
						}
					}
					else {
						bArr[i].isAlive = 0;
					}
				}
			}
		}
		cur[0] = time(NULL);
		m = time(NULL) % 100;
		if (cur[0] - timer[0] >= 1) {
			timer[0] = cur[0];
			for (int i = 0; i < 100; i++) {
				if (eArr[i].isAlive == 0) {
					summon(i);
					break;
				}
			}
		}
		cur[1] = GetTickCount();
		if (cur[1] - timer[1] >= moving) {
			timer[1] = cur[1];
			for (int i = 0; i < 100; i++) {
				if (eArr[i].isAlive == 1) {
					move(i);
				}
			}
		}
	}
}