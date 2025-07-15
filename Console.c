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
/// 콘솔 커서를 초기화합니다.
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
/// 콘솔 커서를 지정한 좌표로 이동시킵니다.
/// </summary>
/// <param name="pt">이동할 좌표를 나타내는 UPOINT 구조체입니다.</param>
void gotoxy(UPOINT pt)
{
	COORD pos;

	pos.X = pt.x;
	pos.Y = pt.y;

	SetConsoleCursorPosition(hout, pos);
}
