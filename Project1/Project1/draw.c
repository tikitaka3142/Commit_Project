#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

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
void draw_menu() {
	gotoxy(16 - 2, 10);
	printf(">  게임시작  ");
	gotoxy(16, 11);
	printf("사용자추가");
	gotoxy(16, 12);
	printf("   설정   ");
	gotoxy(16, 13);
	printf(" 불러오기 ");
	gotoxy(16, 14);
	printf("   종료   ");
}
