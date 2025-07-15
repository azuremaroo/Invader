

#include <windows.h>
#include <wincon.h>

/// <summary>
/// 콘솔 좌표를 나타내는 구조체입니다.
/// </summary>
typedef struct{  
	int x;
	int y;
} UPOINT;


void InitConsole();
void gotoxy(UPOINT pt);
void ClearScreen();