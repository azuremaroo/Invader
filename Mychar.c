#include "main.h"

MYSHIP  myship;
BULLET my_bullet[MAX_MY_BULLET];

char  myship_shape[10] = "-i^i-";

void InitMyship()
{
	myship.flag = TRUE;
	myship.pos.x = MY_SHIP_BASE_POSX;
	myship.pos.y = MY_SHIP_BASE_POSY;
	myship.bullet_type = MY_BULLET_TYPE_DEFAULT;
	InitMyBullet();
}

void InitMyBullet()
{
	int i;

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		my_bullet[i].flag = FALSE;
		my_bullet[i].pos.x = 0;
		my_bullet[i].pos.y = 0;
	}
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

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (my_bullet[i].flag == TRUE)
		{
			if (my_bullet[i].pos.y <= 2)
			{
				my_bullet[i].flag = FALSE;
				oldpos.x = my_bullet[i].pos.x;
				oldpos.y = my_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				break;
			}

			oldpos.x = my_bullet[i].pos.x;
			oldpos.y = my_bullet[i].pos.y;
			--my_bullet[i].pos.y;
			ptpos.x = my_bullet[i].pos.x;
			ptpos.y = my_bullet[i].pos.y;
			gotoxy(oldpos);
			printf(" ");
			gotoxy(ptpos);
			if (CheckMyBulletType(MY_BULLET_TYPE_BOMB))
			{
				printf("@");
			}
			else
			{
				printf("!");
			}
		}
	}
}

void ShotMyBullet(UPOINT ptthisMypos)
{
	int i;

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (my_bullet[i].flag == FALSE)
		{
			int posX = ptthisMypos.x + 2, posY = ptthisMypos.y - 1;
			ActiveMyBullet(&my_bullet[i], ptthisMypos.x + 2, ptthisMypos.y - 1);

			// 기본 미사일 좌우로 미사일 1개씩 추가
			if (CheckMyBulletType(MY_BULLET_TYPE_THREE))
			{
				ActiveMyBullet(&my_bullet[i + 1], posX + 2, posY);
				ActiveMyBullet(&my_bullet[i + 2], posX - 2, posY);
			}

			break;
		}
	}
}

void ActiveMyBullet(BULLET* bullet, int x, int y)
{
	bullet->flag = TRUE;
	bullet->pos.x = x;
	bullet->pos.y = y;
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
				(enemy_bullet[i].pos.x <= ptthisMypos.x + 4) && enemy_bullet[i].pos.y == ptthisMypos.y)
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

void SetMyBulletType(int bulletType)
{
	if (myship.bullet_type % bulletType != 0)
	{
		myship.bullet_type *= bulletType;
	}
}

int GetMyBulletType()
{
	return myship.bullet_type;
}

int CheckMyBulletType(int myShipBulletType) {
	if (myship.bullet_type % myShipBulletType == 0)
		return TRUE;
	else
		return FALSE;
}