#include <stdio.h>
#include "console.h"

HANDLE hout;


void ClearScreen()
{
	int i, j;
	UPOINT pos;

	for (i = 1; i < 25; i++)
	{
		for (j = 1; j < 80; j++)
		{
			pos.x = j;
			pos.y = i;
			gotoxy(pos);
			printf(" ");
		}
	}
}

/// <summary>
/// �ܼ� Ŀ���� �ʱ�ȭ�մϴ�.
/// </summary>
void InitConsole()
{
	CONSOLE_CURSOR_INFO coninfo;

	coninfo.bVisible = FALSE;
	coninfo.dwSize = 1;

	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorInfo(hout, &coninfo);
}

/// <summary>
/// �ܼ� Ŀ���� ������ ��ǥ�� �̵���ŵ�ϴ�.
/// </summary>
/// <param name="pt">�̵��� ��ǥ�� ��Ÿ���� UPOINT ����ü�Դϴ�.</param>
void gotoxy(UPOINT pt)
{
	COORD pos;

	pos.X = pt.x;
	pos.Y = pt.y;

	SetConsoleCursorPosition(hout, pos);
}
