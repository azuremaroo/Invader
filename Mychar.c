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

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (my_bullet[i].flag == TRUE)
		{
			if (my_bullet[i].pos.y < 1)
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
			printf("!");
		}
	}
}

void MyBulletshot(UPOINT ptthisMypos)
{
	int i;

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (my_bullet[i].flag == FALSE)
		{
			my_bullet[i].flag = TRUE;
			my_bullet[i].pos.x = ptthisMypos.x + 2;
			my_bullet[i].pos.y = ptthisMypos.y - 1;

			// 기본 미사일 좌우로 미사일 1개씩 추가
			if (myship.bullet_type % MY_BULLET_TYPE_THREE == 0)
			{
				my_bullet[i + 1].flag = TRUE;
				my_bullet[i + 1].pos.x = my_bullet[i].pos.x + 2;
				my_bullet[i + 1].pos.y = my_bullet[i].pos.y;

				my_bullet[i + 2].flag = TRUE;
				my_bullet[i + 2].pos.x = my_bullet[i].pos.x - 2;
				my_bullet[i + 2].pos.y = my_bullet[i].pos.y;
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

void SetMyShipBulletType(int bulletType)
{
	if (myship.bullet_type % bulletType != 0)
	{
		myship.bullet_type *= bulletType;
	}
}

int GetMyShipBulletType()
{
	return myship.bullet_type;
}

int HasMyShipBulletType(int myShipBulletType) {
	if (myship.bullet_type % myShipBulletType == 0)
		return TRUE;
	else
		return FALSE;
}