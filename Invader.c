#include "main.h"

UPOINT ptthisMypos;
int    timeflag = FALSE;
int    score, hiscore = 2000, killnum;
char* Aboom[8];
char* message;

void main(void)
{
	UPOINT        ptend;
	int	loop = 1;
	timeflag = FALSE;

	Aboom[0] = "i<^>i";
	Aboom[1] = "i(*)i";
	Aboom[2] = "(* *)";
	Aboom[3] = "(** **)";
	Aboom[4] = " (* *) ";
	Aboom[5] = "  (*)  ";
	Aboom[6] = "   *   ";
	Aboom[7] = "       ";
	ptend.x = 36;
	ptend.y = 12;

	system("mode con cols=80 lines=25"); // 콘솔창 화면 크기 조정(win11은 관리자 권한으로 실행해야 적용됨)

	while (loop)
	{
		DWORD         thisTickCount = GetTickCount();
		DWORD         bcount = thisTickCount;
		int           bp = 0;

		Play();

		for (;;)
		{
			if (timeflag == FALSE)
			{
				thisTickCount = GetTickCount();
				message = "당신의 비행기는 파괴되었습니다.";

				if (thisTickCount - bcount > 100)
				{
					gotoxy(ptthisMypos);
					printf("%s", Aboom[bp]);
					bp++;
					if (bp > 7)
						break;
					bcount = thisTickCount;
				}
			}
			else
				break;
		}

		gotoxy(ptend);
		printf(message);
		ptend.y += 1;
		gotoxy(ptend);
		printf("다시 할까요? (y/n)\n");

		do
		{
			char input = _getch();
			if (input == 'y')
			{
				ClearScreen();
				bp = 0;
				killnum = 0;
				score = 0;
				InitMyship();
				InitEnemyship();
				timeflag = FALSE;
				ptend.y = 12;
				loop = 1;
				break;
			}
			else if (input == 'n')
			{
				loop = 0;
				break;
			}
		} while (1);

	}
}

void  Play()
{
	static UPOINT ptMyoldpos;
	DWORD         gthisTickCount = GetTickCount();
	DWORD         gCount = gthisTickCount;
	DWORD         Count = gthisTickCount;
	DWORD         bulletcount = gthisTickCount;
	UPOINT        ptscore, pthi;
	int           juckspeed = 500;

	InitConsole();
	InitMyship();
	InitEnemyship();

	ptthisMypos.x = ptMyoldpos.x = MY_SHIP_BASE_POSX;
	ptthisMypos.y = ptMyoldpos.y = MY_SHIP_BASE_POSY;

	ptscore.x = 68;
	ptscore.y = 1;

	pthi.x = 2;
	pthi.y = 1;


	while (TRUE)
	{
		gthisTickCount = GetTickCount();

		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				if (gthisTickCount - bulletcount > 500) // 연사 속도
				{
					ShotMyBullet(ptthisMypos);
					bulletcount = gthisTickCount;
				}
				break;
			case 'j':
				ptMyoldpos.x = ptthisMypos.x;
				if (--ptthisMypos.x < 1) ptthisMypos.x = 1;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			case 'l':
				ptMyoldpos.x = ptthisMypos.x;
				if (++ptthisMypos.x > 75)ptthisMypos.x = 75;
				DrawMyship(&ptthisMypos, &ptMyoldpos);
				break;
			}
		}

		if (gthisTickCount - Count > 150)
		{

			if (CheckMybullet(ptthisMypos) == 0)
			{
				if (score > 2000)
					hiscore = score;
				break;
			}
			timeflag = CheckKilledEnemy();
			DrawMyBullet();
			DrawMyship(&ptthisMypos, &ptMyoldpos);
			gotoxy(ptscore);

			printf("점수 : %d", score);

			if (timeflag)
			{
				message = " 모든 적을 파괴했습니다. ";
				break;
			}

			// 난이도 수정
			if (killnum > 20)
			{
				if (juckspeed > 100)
				{
					SetMyBulletType(MY_BULLET_TYPE_BOMB);
					juckspeed = 100;
				}
			}
			else if (killnum > 10)
			{
				if (juckspeed > 200)
				{
					juckspeed = 200;
				}
			}
			else if (killnum > 5)
			{
				SetMyBulletType(MY_BULLET_TYPE_THREE);
			}

			gotoxy(pthi);

			Count = gthisTickCount;
		}

		if (gthisTickCount - gCount > juckspeed)
		{
			ShotBullet();
			DrawBullet();
			CalenemyshipPos();
			Drawenemyship();
			if (CheckEnemyPos() == TRUE)
				break;
			gCount = gthisTickCount;
		}
	}

}
