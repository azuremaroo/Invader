

#include <windows.h>
#include <wincon.h>

/// <summary>
/// �ܼ� ��ǥ�� ��Ÿ���� ����ü�Դϴ�.
/// </summary>
typedef struct{  
	int x;
	int y;
} UPOINT;


void InitConsole();
void gotoxy(UPOINT pt);
void ClearScreen();