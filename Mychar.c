#include "main.h"

MYSHIP  myship;
BULLET myship_bullet[MAX_MY_BULLET];

char  myship_shape[10] = "-i^i-";

void InitMyship()
{
	myship.flag = TRUE;
	myship.pos.x = MY_SHIP_BASE_POSX;
	myship.pos.y = MY_SHIP_BASE_POSY;
	myship.bullet_type = MY_BULLET_TYPE_DEFAULT;
}


void DrawMyship(UPOINT* pt, UPOINT* oldpt)
{
	gotoxy(*oldpt);
	printf("     ");
	gotoxy(*pt);
	printf("%s", myship_shape);
}


void DrawMyBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (myship_bullet[i].flag == TRUE)
		{
			if (myship_bullet[i].pos.y < 1)
			{
				myship_bullet[i].flag = FALSE;
				oldpos.x = myship_bullet[i].pos.x;
				oldpos.y = myship_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				break;
			}

			oldpos.x = myship_bullet[i].pos.x;
			oldpos.y = myship_bullet[i].pos.y;
			--myship_bullet[i].pos.y;
			ptpos.x = myship_bullet[i].pos.x;
			ptpos.y = myship_bullet[i].pos.y;
			gotoxy(oldpos);
			printf(" ");
			gotoxy(ptpos);
			printf("!");
		}
	}
}

void MyBulletshot(UPOINT ptthisMypos)
{
	int i;

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (myship_bullet[i].flag == FALSE)
		{
			myship_bullet[i].flag = TRUE;
			myship_bullet[i].pos.x = ptthisMypos.x + 2;
			myship_bullet[i].pos.y = ptthisMypos.y - 1;

			// 기본 미사일 좌우로 미사일 1개씩 추가
			if (myship.bullet_type == MY_BULLET_TYPE_THREE)
			{
				myship_bullet[i + 1].flag = TRUE;
				myship_bullet[i + 1].pos.x = myship_bullet[i].pos.x + 2;
				myship_bullet[i + 1].pos.y = myship_bullet[i].pos.y;

				myship_bullet[i + 2].flag = TRUE;
				myship_bullet[i + 2].pos.x = myship_bullet[i].pos.x - 2;
				myship_bullet[i + 2].pos.y = myship_bullet[i].pos.y;
			}

			break;
		}
	}
}

int CheckMybullet(UPOINT ptthisMypos)
{
	int i, flag;

	flag = FALSE;

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == TRUE)
		{
			if (ptthisMypos.x <= enemy_bullet[i].pos.x &&
				(enemy_bullet[i].pos.x <= ptthisMypos.x + 4) &&
				enemy_bullet[i].pos.y == ptthisMypos.y)
			{
				flag = TRUE;
				break;
			}
		}
	}

	if (flag == TRUE)
		return 0;
	else
		return 1;
}

void SetMyShipBulletType(short bulletType)
{
	myship.bullet_type = bulletType;
}

