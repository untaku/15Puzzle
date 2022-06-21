#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

BOOL changeConsoleSize(int x, int y) {
	HANDLE hStdout;
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SMALL_RECT rectConsoleSize;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//�E�B���h�E�T�C�Y��ړI�̑傫���ɐݒ�ɂ���
	rectConsoleSize.Right = x - 1;
	rectConsoleSize.Bottom = y - 1;
	SetConsoleWindowInfo(hStdout, TRUE, &rectConsoleSize);
	return TRUE;
}

//�{�[�h�̃}�X��
#define BOARD_WIDTH		(4)
#define BOARD_HEIGHT		(BOARD_WIDTH)
#define BLANK_NUMBER	(16)

typedef struct {
	int x, y;
}VEC2;

int board[BOARD_HEIGHT][BOARD_WIDTH];

VEC2 getBlankPos() {
	VEC2 blankPos = {-1,-1};
	for (int y = 0; y < BOARD_HEIGHT; y++)
		for (int x = 0; x < BOARD_WIDTH; x++)
			if (board[y][x] == BLANK_NUMBER)
				blankPos = { x,y };

	return blankPos;
}

void moveToBlank(VEC2 _movePos) {
	//�}�X�O�̏ꏊ�ŏ������N���Ȃ��悤����
	if (
		(_movePos.x < 0)
		|| (_movePos.x >= BOARD_WIDTH)
		|| (_movePos.y < 0)
		|| (_movePos.y >= BOARD_HEIGHT)
		)
		return;

	VEC2 blankPos = getBlankPos();
	int temp = board[blankPos.y][blankPos.x];
	board[blankPos.y][blankPos.x] = board[_movePos.y][_movePos.x];
	board[_movePos.y][_movePos.x] = temp;
}

int main(void) {
	//�R���\�[���T�C�Y�ύX�l
	changeConsoleSize(30, 20);
	//���̎����ŃV���b�t��
	srand((unsigned int)time(NULL));

	for (int y = 0; y < BOARD_HEIGHT; y++) 
		for (int x = 0; x < BOARD_WIDTH; x++) 
			board[y][x] = y * BOARD_WIDTH + x+1;

	for (int i = 0; i < 1000; i++) {
		VEC2 blankPos = getBlankPos();
		VEC2 movePos = blankPos;
		//�S�Ŋ������]��̒l�ɂ���ă����_���ɔz�u��ς���
		switch (rand() % 4) {
		case 0:movePos.y++;		break;
		case 1:movePos.y--;		break;
		case 2:movePos.x++;		break;
		case 3:movePos.x--;		break;
		}
		moveToBlank(movePos);
	}

	while (true) {
		system("cls");
		printf("  15Puzzle\n\n");//�^�C�g��
		printf("+--+--+--+--+\n");
		for (int y = 0; y < BOARD_HEIGHT; y++) {
			for (int x = 0; x < BOARD_WIDTH; x++)
				if (board[y][x] == BLANK_NUMBER)
					printf("|�@");
				else
					printf("|%2d", board[y][x]);
			printf("|\n");
			printf("+--+--+--+--+\n");
		}
		printf("\n\n  ������@\n");//�������
		printf("W:�󔒂̉��̐��Ɠ���ւ���\n");
		printf("A:�󔒂̉E�̐��Ɠ���ւ���\n");
		printf("S:�󔒂̏�̐��Ɠ���ւ���\n");
		printf("D:�󔒂̍��̐��Ɠ���ւ���\n");
		//�p�Y�������̏�Ԃɖ߂�ƕ\���Ⴄ�Ɣ�\��
		bool isClear = true;
		for (int y = 0; y < BOARD_HEIGHT; y++)
			for (int x = 0; x < BOARD_WIDTH; x++)
				if (board[y][x] != y * BOARD_WIDTH + x + 1)
					isClear = false;
		if (isClear)
			printf("Congratulations!\n");

		VEC2 blankPos = getBlankPos();
		VEC2 movePos = blankPos;
		//WASD�L�[���������Ƃ��̑I���}�X�̎擾
		switch (_getch()) {
		case 'w':movePos.y++;		break;
		case 's':movePos.y--;		break;
		case 'a':movePos.x++;		break;
		case 'd':movePos.x--;		break;
		}
		moveToBlank(movePos);
	}
}