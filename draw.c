#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define UP 0
#define DOWN 1
#define SUBMIT 2

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void draw_tilte() {
	printf("	     ######    #######\n");
	printf("	    #      #   #     #\n");
	printf("	    #      #   #######\n");
	printf("	     ######       #\n");
	printf("	        #     #########\n");
	printf("	        #      #######\n");
	printf("	    #########        #\n");
}
int draw_menu() {
	int x = 16;
	int y = 10;

	gotoxy(x - 2, y);
	printf(">  ���ӽ���  ");
	gotoxy(x, y + 1);
	printf("������߰�");
	gotoxy(x, y + 2);
	printf("   ����   ");
	gotoxy(x, y + 3);
	printf(" �ҷ����� ");
	gotoxy(x, y + 4);
	printf("   ����   ");
	while (1)
	{
		int n = keyControl();
		switch (n)
		{
		case UP:
			{
				if (y > 10)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, --y);
					printf(">");
				}
			}
			break;

		case DOWN:
			{
				if (y < 14)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, ++y);
					printf(">");
				}
			}
			break;

		case SUBMIT:
			{
				return 0;
			}
		}
	}
}

int keyControl()
{
	char temp = getch();

	if(temp == 'W' || temp == 'w')
	{
		return UP;
	}
	else if (temp == 'S' || temp == 's')
	{
		return DOWN;
	}
	else if (temp == 'O' || temp == 'o')
	{
		return SUBMIT;
	}
}