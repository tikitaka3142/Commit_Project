#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "draw.h"

int check_33(int x, int y);
int check_44(int x, int y);									// ���� ������Ģ (3 x 3)�� üũ�ϴ� �Լ�
int Omok_Board[20][20] = { 0 };								// ���� ������ �������� �ʱ�ȭ�ϴ� �������� 
int Color = 2;												// ���� ���� ������ ���ϴ� �������� ( 1 == �鵹 , 2 == �浹 ), �浹�� ���� ����
int Winner_Checking(int Board[][20]);						// ���ڸ� üũ�ϴ� �Լ� (�������� �ּҸ� ���ڷκ����� 5���� ���ڸ� üũ)
void Gotoxy(int x, int y);									// X,Y ��ǥ�� ����������Ʈ�� ������ �Լ�  
void Game_Start();											// ������ �����ϴ� �Լ�
void Draw_Omok_Board();										// 19 x 19 �������� �׸��� �Լ�
void Key_Down(int Board[][20], char key, int* x, int* y);	// Ű�� �Է¹޾� �����̴� �Լ�
void Erase_Stone(int x, int y);								// Ŀ���� �ű��� ���� �ٽ� �׸��� �Լ� 
void Draw_Stone();											// ���� �׸��� �Լ� (1�̸� �� , 2�̸� ��)�� ���� (�������Ѽ� ������ ����)
void Put_Stone(int Board[][20], int x, int y);              // 0���� �ʱ�ȭ�� 2���� �迭�� 1�Ǵ� 2�� ���� ����
void Draw_Put_Stone(int Board[][20]);						// ������Ʈ�� �ִ� ��ġ�� (1�̸� �� , 2�̸� ��)�� ����
void Re_Game();												// ������ ���� ��, ������ �ٽ� �����ϴ� �Լ�
void Player_Change(int a);									// ���� �� ���� ������ �ٲ��ٴ� �� ǥ�����ִ� �Լ�

/********* ���� ���� �Լ� *********/
void Game_Start() {
	int x = 18, y = 8, i, j;
	char Key;                                    // Ű�� �ԷµǾ��� �� �� ASCII �ڵ带 ���� ����
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++) {
			Omok_Board[i][j] = 0;
		}
	Gotoxy(50, 5);
	printf("�� ���� �����Դϴ�\n");
	Gotoxy(0, 0);
	Draw_Omok_Board();
	Gotoxy(x, y);
	Draw_Stone();
	do {                                            // do while��. �ϴ� �ѹ� �����ϰ� ���ǿ� ������ ���� ����
		Key = _getch();                              // Ű �ϳ��� �Է¹޾� �װ��� ASCII �ڵ带 Key ������ ����
		Erase_Stone(x, y);
		Key_Down(Omok_Board, Key, &x, &y);           // Ű�� �������� �� ó���ϴ� �Լ� ȣ��
		Draw_Put_Stone(Omok_Board);                  // ������ ���� �׸��� �Լ� ȣ��
		if (Winner_Checking(Omok_Board))             // ���ڸ� üũ�ϴ� �Լ� ȣ��
			return;
		Gotoxy(x, y);
		Draw_Stone();                                // �� ���� �Լ�, Ŀ���� �̵��������� �״����� �� ����
	} while (Key != 27);                            // Key���� 27�� �ƴҰ��� ������ 27���� ESCŰ
}
//--------------------------------------------

//---------�� ������ �Լ�---------------------
void Erase_Stone(int x, int y) {                   // x,y�� ��ǥ���� �Ű������� ����
	Gotoxy(x, y);                                   // ���� ���� ��ġ�� ������ �̵� 
	if (x == 0 && y == 0)                           // �װ��� ���� 0,0 (���� �� �𼭸�)�� ����
		printf("��");
	else if (x == 36 && y == 0)                     // �װ��� ���� 36,0 (������ �� �𼭸�)�� ����
		printf("��");
	else if (x == 0 && y == 18)                     // �װ��� ���� 0,18 (���� �Ʒ� �𼭸�)�� ����
		printf("��");
	else if (x == 36 && y == 18)                    // �װ��� ���� 36,18 (������ �Ʒ� �𼭸�)�� ����
		printf("��");
	else if (x == 0)                                // �װ��� ���� 0,* (������)�� ����                 
		printf("��");
	else if (y == 0)                                // �װ��� ���� *,0 (����)�� ����
		printf("��");
	else if (x == 36)                               // �װ��� ���� 36,* (��������)�� ����
		printf("��");
	else if (y == 18)                               // �װ��� ���� *,18 (�Ʒ���)�� ����
		printf("��");
	else                                           // �� ���� ����
		printf("��");
}

//-------------�� �׸��� �Լ�--------------------
void Draw_Stone() {
	if (Color == 1) printf("��");
	else
		printf("��");
}
//-----------------------------------------------

//----------Ű�� ������ �� ó���ϴ� �Լ�-------------
void Key_Down(int Board[][20], char key, int* x, int* y) {
	int checking3x3, checking4x4;
	int a, b;
	switch (key) {
	case 72:                                    // key���� ASCII�ڵ尡 72���� �� (���� ����Ű)
		if (*y - 1 < 0)                          // y-1 ���� �� 0 �̸��̸� ó�� ����
			break;
		else                                     // 0 �̸��� �ƴҰ��쿡�� y���� 1 ����
			*y -= 1;
		break;
	case 80:                                    // key���� ASCII�ڵ尡 80���� �� (�Ʒ��� ����Ű)
		if (*y + 1 > 18)                         // y+1 ���� �� 18�� �ʰ��ϸ� ó�� ����
			break;
		else                                     // 18�� �ʰ����� �ʾ��� ���� y�� 1 ����
			*y += 1;
		break;
	case 75:                                    // key���� ASCII�ڵ尡 75���� �� (���� ����Ű)
		if (*x - 2 < 0)                          // x-2 ���� �� 0 �̸��̸� ���� ó�� ����
			break;
		else                                     // 0 �̸��� �ƴҰ��쿡�� x�� 2 ����
			*x -= 2;
		break;
	case 77:                                   // key���� ASCII�ڵ尡 77���� �� (������ ����Ű)
		if (*x + 2 > 36)                           // x+2���� �� 36�� �ʰ��ϸ� ó�� ����
			break;
		else                                     // 36�� �ʰ����� �ʾ��� ���� x�� 2 ����
			*x += 2;
		break;
	case 32: {
		a = *x;
		b = *y;
		checking3x3 = check_33(a, b);
		checking4x4 = check_44(a, b);

		if (Color == 1)
		{
			Put_Stone(Board, *x, *y);
			Player_Change(1);
			break;
		}
		else {
			Put_Stone(Board, *x, *y);
			Player_Change(2);
			if (checking3x3 == 1)
			{
				Gotoxy(50, 11);
				printf("3x3�� ��ġ���� ������ �� �����ϴ�!");
				key = _getch();
				Key_Down(Omok_Board, key, &a, &b);
			}

			if (checking3x3 == 1)
			{
				Omok_Board[*y][*x / 2] = 0;
				Color = 2;
				Player_Change(1);
			}
			if (checking4x4 == 1)
			{
				Gotoxy(50, 11);
				printf("4x4�� ��ġ���� ������ �� �����ϴ�!");
				key = _getch();
				Key_Down(Omok_Board, key, &a, &b);
			}

			if (checking4x4 == 1)
			{
				Omok_Board[*y][*x / 2] = 0;
				Color = 2;
				Player_Change(1);
			}
		}
	}
		   break;
	default:                                           //�� ���� ����, ó�� ����
		break;
	}
}
//-------------------------------------------------

//-----------------�� ���� �Լ�--------------------
void Put_Stone(int Board[][20], int x, int y) {
	if (Board[y][x / 2] == 0) {
		if (Color == 1) {
			Board[y][x / 2] = 1;                        // Board[y][x/2] �� 1�� �ְ�  Color�� 2�� ����  
			Color = 2;
		}
		else {									    // Board[y][x/2] �� 2�� �ְ�  Color�� 1�� ����
			Board[y][x / 2] = 2;
			Color = 1;
		}
	}
}
void Draw_Put_Stone(int Board[][20]) {
	int i;
	int j;
	for (i = 0; i < 20; i++) {                        // �ٵ��ǿ� 1 �Ǵ� 2�� ���ڰ� �ִ��� Ȯ��
		for (j = 0; j < 20; j++) {
			if (Board[j][i] == 1) {
				Gotoxy(i * 2, j);                        // Ŀ���� i*2,j �� ������ �� �� ����
				printf("��");
			}
			else if (Board[j][i] == 2) {
				Gotoxy(i * 2, j);                        // Ŀ���� i*2,j �� ������ �� �� ����
				printf("��");
			}
		}
	}
}
//----------------------------------------------------

//-------------�¸� üũ �Լ�-------------------------
int Winner_Checking(int Board[][20]) {
	int i;
	int j;
	int count = 0;
	char Over;
	for (i = 2; i < 18; i++) {
		for (j = 0; j < 20; j++) {
			if (Board[j][i - 2] == 1 && Board[j][i - 1] == 1 && Board[j][i] == 1 && Board[j][i + 1] == 1 && Board[j][i + 2] == 1) {
				Gotoxy(50, 10);                                          // 2�� �迭�� 5���� ���ӵ� ���ڰ� �ִ��� Ȯ�� 
				printf("*** �ܴ��� �¸��ϼ̽��ϴ� ***");				 // ���ڸ� ����
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {                                             // ���� ���� �� �̾ ������ ������ �� �ִ� ���� ����
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}
			else if (Board[j][i - 2] == 2 && Board[j][i - 1] == 2 && Board[j][i] == 2 && Board[j][i + 1] == 2 && Board[j][i + 2] == 2)
			{
				Gotoxy(50, 10);
				printf("*** �۴��� �¸��ϼ̽��ϴ� ***");
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}
			else if (Board[i - 2][j] == 1 && Board[i - 1][j] == 1 && Board[i][j] == 1 && Board[i + 1][j] == 1 && Board[i + 2][j] == 1) {
				Gotoxy(50, 10);
				printf("*** �ܴ��� �¸��ϼ̽��ϴ� ***");
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}
			else if (Board[i - 2][j] == 2 && Board[i - 1][j] == 2 && Board[i][j] == 2 && Board[i + 1][j] == 2 && Board[i + 2][j] == 2) {
				Gotoxy(50, 10);
				printf("*** �۴��� �¸��ϼ̽��ϴ� ***");
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}
		}
	}
	for (i = 2; i < 18; i++) {
		for (j = 2; j < 18; j++) {
			if (Board[j - 2][i - 2] == 1 && Board[j - 1][i - 1] == 1 && Board[j][i] == 1 && Board[j + 1][i + 1] == 1 && Board[j + 2][i + 2] == 1) {
				Gotoxy(50, 10);
				printf("*** �ܴ��� �¸��ϼ̽��ϴ� ***");
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}
			else if (Board[j - 2][i - 2] == 2 && Board[j - 1][i - 1] == 2 && Board[j][i] == 2 && Board[j + 1][i + 1] == 2 && Board[j + 2][i + 2] == 2) {
				Gotoxy(50, 10);
				printf("*** �۴��� �¸��ϼ̽��ϴ� ***");
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}

			else if (Board[j + 2][i - 2] == 1 && Board[j + 1][i - 1] == 1 && Board[j][i] == 1 && Board[j - 1][i + 1] == 1 && Board[j - 2][i + 2] == 1) {
				Gotoxy(50, 10);
				printf("*** �ܴ��� �¸��ϼ̽��ϴ� ***");
				Gotoxy(50, 12);
				printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
				for (; 1;) {
					Gotoxy(50, 14);
					Over = _getch();
					if (Over == 89 || Over == 121) {
						Color = 2;
						Re_Game();
					}
					if (Over == 78 || Over == 110) return 1;
				}
			}
			else if (Board[j + 2][i - 2] == 2 && Board[j + 1][i - 1] == 2 && Board[j][i] == 2 && Board[j - 1][i + 1] == 2 && Board[j - 2][i + 2] == 2) {
				{
					Gotoxy(50, 10);
					printf("*** �۴��� �¸��ϼ̽��ϴ� ***");

					Gotoxy(50, 12);
					printf("*** ������ ���� �Ͻðڽ��ϱ� ? [ Y / N ] ***");
					for (; 1;) {
						Gotoxy(50, 14);
						Over = _getch();
						if (Over == 89 || Over == 121) {
							Color = 2;
							Re_Game();
						}
						if (Over == 78 || Over == 110) return 1;
					}
				}
			}
		}
	}
	return 0;
}
void Draw_Omok_Board()
{
	int i, j;
	printf("��");
	for (i = 0; i < 17; i++) printf("��");
	printf("��\n");

	for (i = 0; i < 17; i++) {
		printf("��");
		for (j = 0; j < 17; j++)
			printf("��");
		printf("��\n");
	}
	printf("��");
	for (i = 0; i < 17; i++)printf("��");
	printf("��");
}
//----------------------------------------------------

//----------Ŀ�� �̵��Լ�----------------------
void Gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//------------------------------------------------
void Re_Game()
{
	system("cls");
	Game_Start();
}
void Player_Change(int a)
{
	if (a == 1) {
		Gotoxy(50, 5);
		printf("�� ���� �����Դϴ�\n");
	}
	if (a == 2) {
		Gotoxy(50, 5);
		printf("�� ���� �����Դϴ�\n");
		Gotoxy(50, 11);
		printf("������������������������������������������������������");
	}
}

int check_33(int x, int y)
{
	int count = 0;
	// ����üũ. 
	if ((Omok_Board[y][x / 2 - 3] == 0 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 0) ||
		(Omok_Board[y][x / 2 - 2] == 0 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 + 2] == 0) ||
		(Omok_Board[y][x / 2 - 1] == 0 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 3] == 0) ||
		(Omok_Board[y][x / 2 - 4] == 0 && Omok_Board[y][x / 2 - 3] == 2 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 0 && Omok_Board[y][x / 2 + 1] == 0) ||
		(Omok_Board[y][x / 2 + 4] == 0 && Omok_Board[y][x / 2 + 3] == 2 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 1] == 0 && Omok_Board[y][x / 2 - 1] == 0) ||
		(Omok_Board[y][x / 2 - 2] == 0 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 0 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 3] == 0) ||
		(Omok_Board[y][x / 2 + 2] == 0 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 - 1] == 0 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 3] == 0))
		count++;
	// ����üũ. 
	if ((Omok_Board[y - 3][x / 2] == 0 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0) ||
		(Omok_Board[y - 2][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 0) ||
		(Omok_Board[y - 1][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 3][x / 2] == 0) ||
		(Omok_Board[y - 4][x / 2] == 0 && Omok_Board[y - 3][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 0) ||
		(Omok_Board[y + 4][x / 2] == 0 && Omok_Board[y + 3][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 0) ||
		(Omok_Board[y - 2][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 3][x / 2] == 0) ||
		(Omok_Board[y + 2][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 3][x / 2] == 0))
		count++;
	// �밢��üũ. 
	if ((Omok_Board[y - 3][x / 2 - 3] == 0 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0) ||
		(Omok_Board[y - 2][x / 2 - 2] == 0 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0) ||
		(Omok_Board[y - 1][x / 2 - 1] == 0 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 3][x / 2 + 3] == 0) ||
		(Omok_Board[y - 3][x / 2 - 3] == 0 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0) ||
		(Omok_Board[y + 3][x / 2 + 3] == 0 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y - 2][x / 2 - 2] == 0) ||
		(Omok_Board[y - 4][x / 2 - 4] == 0 && Omok_Board[y - 3][x / 2 - 3] == 2 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0 && Omok_Board[y + 1][x / 2 + 1] == 0) ||
		(Omok_Board[y + 4][x / 2 + 4] == 0 && Omok_Board[y + 3][x / 2 + 3] == 2 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0 && Omok_Board[y - 1][x / 2 - 1] == 0))
		count++;
	// �ݴ� �밢��üũ. 
	if ((Omok_Board[y - 3][x / 2 + 3] == 0 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0) ||
		(Omok_Board[y - 2][x / 2 + 2] == 0 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0) ||
		(Omok_Board[y - 1][x / 2 + 1] == 0 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 3][x / 2 - 3] == 0) ||
		(Omok_Board[y - 3][x / 2 + 3] == 0 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0) ||
		(Omok_Board[y + 3][x / 2 - 3] == 0 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y - 2][x / 2 + 2] == 0) ||
		(Omok_Board[y - 4][x / 2 + 4] == 0 && Omok_Board[y - 3][x / 2 + 3] == 2 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0 && Omok_Board[y + 1][x / 2 - 1] == 0) ||
		(Omok_Board[y + 4][x / 2 - 4] == 0 && Omok_Board[y + 3][x / 2 - 3] == 2 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0 && Omok_Board[y - 1][x / 2 + 1] == 0))
		count++;
	if (count > 1) return 1;
	else return 0;
}

int check_44(int x, int y)
{
	int count = 0;
	// ����üũ. 
	if ((Omok_Board[y][x / 2 - 4] == 0 && Omok_Board[y][x / 2 - 3] == 2 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 0) ||
		(Omok_Board[y][x / 2 + 4] == 0 && Omok_Board[y][x / 2 + 3] == 2 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 - 1] == 0) ||
		(Omok_Board[y][x / 2 - 5] == 0 && Omok_Board[y][x / 2 - 4] == 2 && Omok_Board[y][x / 2 - 3] == 0 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 0) ||
		(Omok_Board[y][x / 2 + 5] == 0 && Omok_Board[y][x / 2 + 4] == 2 && Omok_Board[y][x / 2 + 3] == 0 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 - 1] == 0) ||
		(Omok_Board[y][x / 2 - 5] == 0 && Omok_Board[y][x / 2 - 4] == 2 && Omok_Board[y][x / 2 - 3] == 2 && Omok_Board[y][x / 2 - 2] == 0 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 0) ||
		(Omok_Board[y][x / 2 + 5] == 0 && Omok_Board[y][x / 2 + 4] == 2 && Omok_Board[y][x / 2 + 3] == 2 && Omok_Board[y][x / 2 + 2] == 0 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 - 1] == 0) ||
		(Omok_Board[y][x / 2 - 5] == 0 && Omok_Board[y][x / 2 - 4] == 2 && Omok_Board[y][x / 2 - 3] == 2 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 0 && Omok_Board[y][x / 2 + 1] == 0) ||
		(Omok_Board[y][x / 2 + 5] == 0 && Omok_Board[y][x / 2 + 4] == 2 && Omok_Board[y][x / 2 + 3] == 2 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 1] == 0 && Omok_Board[y][x / 2 - 1] == 0) ||
		(Omok_Board[y][x / 2 - 3] == 0 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 + 2] == 0) ||
		(Omok_Board[y][x / 2 + 3] == 0 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 - 2] == 0) ||
		(Omok_Board[y][x / 2 - 4] == 0 && Omok_Board[y][x / 2 - 3] == 2 && Omok_Board[y][x / 2 - 2] == 2 && Omok_Board[y][x / 2 - 1] == 0 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 + 2] == 0) ||
		(Omok_Board[y][x / 2 + 4] == 0 && Omok_Board[y][x / 2 + 3] == 2 && Omok_Board[y][x / 2 + 2] == 2 && Omok_Board[y][x / 2 + 1] == 0 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 - 2] == 0) ||
		(Omok_Board[y][x / 2 - 4] == 0 && Omok_Board[y][x / 2 - 3] == 2 && Omok_Board[y][x / 2 - 2] == 0 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 + 2] == 0) ||
		(Omok_Board[y][x / 2 + 4] == 0 && Omok_Board[y][x / 2 + 3] == 2 && Omok_Board[y][x / 2 + 2] == 0 && Omok_Board[y][x / 2 + 1] == 2 && Omok_Board[y][x / 2 - 1] == 2 && Omok_Board[y][x / 2 - 2] == 0))
		count++;
	// ����üũ. 
	if ((Omok_Board[y - 4][x / 2] == 0 && Omok_Board[y - 3][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0) ||
		(Omok_Board[y + 4][x / 2] == 0 && Omok_Board[y + 3][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0) ||
		(Omok_Board[y - 5][x / 2] == 0 && Omok_Board[y - 4][x / 2] == 2 && Omok_Board[y - 3][x / 2] == 0 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0) ||
		(Omok_Board[y + 5][x / 2] == 0 && Omok_Board[y + 4][x / 2] == 2 && Omok_Board[y + 3][x / 2] == 0 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0) ||
		(Omok_Board[y - 5][x / 2] == 0 && Omok_Board[y - 4][x / 2] == 2 && Omok_Board[y - 3][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0) ||
		(Omok_Board[y + 5][x / 2] == 0 && Omok_Board[y + 4][x / 2] == 2 && Omok_Board[y + 3][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0) ||
		(Omok_Board[y - 5][x / 2] == 0 && Omok_Board[y - 4][x / 2] == 2 && Omok_Board[y - 3][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 0) ||
		(Omok_Board[y + 5][x / 2] == 0 && Omok_Board[y + 4][x / 2] == 2 && Omok_Board[y + 3][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 0) ||
		(Omok_Board[y - 3][x / 2] == 0 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 0) ||
		(Omok_Board[y + 3][x / 2] == 0 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 0) ||
		(Omok_Board[y - 4][x / 2] == 0 && Omok_Board[y - 3][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 0) ||
		(Omok_Board[y + 4][x / 2] == 0 && Omok_Board[y + 3][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 0) ||
		(Omok_Board[y - 4][x / 2] == 0 && Omok_Board[y - 3][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 0 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 0) ||
		(Omok_Board[y + 4][x / 2] == 0 && Omok_Board[y + 3][x / 2] == 2 && Omok_Board[y + 2][x / 2] == 0 && Omok_Board[y + 1][x / 2] == 2 && Omok_Board[y - 1][x / 2] == 2 && Omok_Board[y - 2][x / 2] == 0))
		count++;
	// �밢��üũ. 
	if ((Omok_Board[y - 4][x / 2 - 4] == 0 && Omok_Board[y - 3][x / 2 - 3] == 2 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0) ||
		(Omok_Board[y + 4][x / 2 + 4] == 0 && Omok_Board[y + 3][x / 2 + 3] == 2 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0) ||
		(Omok_Board[y - 5][x / 2 - 5] == 0 && Omok_Board[y - 4][x / 2 - 4] == 2 && Omok_Board[y - 3][x / 2 - 3] == 0 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0) ||
		(Omok_Board[y + 5][x / 2 + 5] == 0 && Omok_Board[y + 4][x / 2 + 4] == 2 && Omok_Board[y + 3][x / 2 + 3] == 0 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0) ||
		(Omok_Board[y - 5][x / 2 - 5] == 0 && Omok_Board[y - 4][x / 2 - 4] == 2 && Omok_Board[y - 3][x / 2 - 3] == 2 && Omok_Board[y - 2][x / 2 - 2] == 0 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0) ||
		(Omok_Board[y + 5][x / 2 + 5] == 0 && Omok_Board[y + 4][x / 2 + 4] == 2 && Omok_Board[y + 3][x / 2 + 3] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0) ||
		(Omok_Board[y - 5][x / 2 - 5] == 0 && Omok_Board[y - 4][x / 2 - 4] == 2 && Omok_Board[y - 3][x / 2 - 3] == 2 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0 && Omok_Board[y + 1][x / 2 + 1] == 0) ||
		(Omok_Board[y + 5][x / 2 + 5] == 0 && Omok_Board[y + 4][x / 2 + 4] == 2 && Omok_Board[y + 3][x / 2 + 3] == 2 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0 && Omok_Board[y - 1][x / 2 - 1] == 0) ||
		(Omok_Board[y - 3][x / 2 - 3] == 0 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0) ||
		(Omok_Board[y + 3][x / 2 + 3] == 0 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y - 2][x / 2 - 2] == 0) ||
		(Omok_Board[y - 4][x / 2 - 4] == 0 && Omok_Board[y - 3][x / 2 - 3] == 2 && Omok_Board[y - 2][x / 2 - 2] == 2 && Omok_Board[y - 1][x / 2 - 1] == 0 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0) ||
		(Omok_Board[y + 4][x / 2 + 4] == 0 && Omok_Board[y + 3][x / 2 + 3] == 2 && Omok_Board[y + 2][x / 2 + 2] == 2 && Omok_Board[y + 1][x / 2 + 1] == 0 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y - 2][x / 2 - 2] == 0) ||
		(Omok_Board[y - 4][x / 2 - 4] == 0 && Omok_Board[y - 3][x / 2 - 3] == 2 && Omok_Board[y - 2][x / 2 - 2] == 0 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0) ||
		(Omok_Board[y + 4][x / 2 + 4] == 0 && Omok_Board[y + 3][x / 2 + 3] == 2 && Omok_Board[y + 2][x / 2 + 2] == 0 && Omok_Board[y + 1][x / 2 + 1] == 2 && Omok_Board[y - 1][x / 2 - 1] == 2 && Omok_Board[y - 2][x / 2 - 2] == 0))
		count++;
	// �ݴ� �밢��üũ. 
	if ((Omok_Board[y - 4][x / 2 + 4] == 0 && Omok_Board[y - 3][x / 2 + 3] == 2 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0) ||
		(Omok_Board[y + 4][x / 2 - 4] == 0 && Omok_Board[y + 3][x / 2 - 3] == 2 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0) ||
		(Omok_Board[y - 5][x / 2 + 5] == 0 && Omok_Board[y - 4][x / 2 + 4] == 2 && Omok_Board[y - 3][x / 2 + 3] == 0 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0) ||
		(Omok_Board[y + 5][x / 2 - 5] == 0 && Omok_Board[y + 4][x / 2 - 4] == 2 && Omok_Board[y + 3][x / 2 - 3] == 0 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0) ||
		(Omok_Board[y - 5][x / 2 + 5] == 0 && Omok_Board[y - 4][x / 2 + 4] == 2 && Omok_Board[y - 3][x / 2 + 3] == 2 && Omok_Board[y - 2][x / 2 + 2] == 0 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0) ||
		(Omok_Board[y + 5][x / 2 - 5] == 0 && Omok_Board[y + 4][x / 2 - 4] == 2 && Omok_Board[y + 3][x / 2 - 3] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0) ||
		(Omok_Board[y - 5][x / 2 - 5] == 0 && Omok_Board[y - 4][x / 2 + 4] == 2 && Omok_Board[y - 3][x / 2 + 3] == 2 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0 && Omok_Board[y + 1][x / 2 - 1] == 0) ||
		(Omok_Board[y + 5][x / 2 + 5] == 0 && Omok_Board[y + 4][x / 2 - 4] == 2 && Omok_Board[y + 3][x / 2 - 3] == 2 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0 && Omok_Board[y - 1][x / 2 + 1] == 0) ||
		(Omok_Board[y - 3][x / 2 + 3] == 0 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0) ||
		(Omok_Board[y + 3][x / 2 - 3] == 0 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y - 2][x / 2 + 2] == 0) ||
		(Omok_Board[y - 4][x / 2 + 4] == 0 && Omok_Board[y - 3][x / 2 + 3] == 2 && Omok_Board[y - 2][x / 2 + 2] == 2 && Omok_Board[y - 1][x / 2 + 1] == 0 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0) ||
		(Omok_Board[y + 4][x / 2 - 4] == 0 && Omok_Board[y + 3][x / 2 - 3] == 2 && Omok_Board[y + 2][x / 2 - 2] == 2 && Omok_Board[y + 1][x / 2 - 1] == 0 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y - 2][x / 2 + 2] == 0) ||
		(Omok_Board[y - 4][x / 2 + 4] == 0 && Omok_Board[y - 3][x / 2 + 3] == 2 && Omok_Board[y - 2][x / 2 + 2] == 0 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0) ||
		(Omok_Board[y + 4][x / 2 - 4] == 0 && Omok_Board[y + 3][x / 2 - 3] == 2 && Omok_Board[y + 2][x / 2 - 2] == 0 && Omok_Board[y + 1][x / 2 - 1] == 2 && Omok_Board[y - 1][x / 2 + 1] == 2 && Omok_Board[y - 2][x / 2 + 2] == 0))
		count++;
	if (count > 1) return 1;
	else return 0;
}
