#include "main.h"

char  enemyship_shape[5] = "^V^";

ENEMYSHIP enemyship[MAX_ENEMY_BASE_ROW][MAX_ENEMY_BASE_COL];
UPOINT ptOld[MAX_ENEMY_BASE_ROW][MAX_ENEMY_BASE_COL];
BULLET enemy_bullet[MAX_ENEMY_BULLET];
short flag; // 기체 이동 방향 결정 TRUE: right, FALSE: left


void Initenemyship()
{
	int i, j;

	flag = FALSE;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			enemyship[i][j].flag = TRUE;
			enemyship[i][j].pos.x = ENEMY_SHIP_BASE_POSX + j * 4;
			enemyship[i][j].pos.y = ENEMY_SHIP_BASE_POSY + i * 2;
			ptOld[i][j].x = ENEMY_SHIP_BASE_POSX + j * 4;
			ptOld[i][j].y = ENEMY_SHIP_BASE_POSY + i * 2;
		}
	}
	InitBullet();
}

void CalenemyshipPos()
{
	int i, j, XAdd, YAdd;

	YAdd = Calflag();
	if (flag == FALSE)
		XAdd = 1;
	else
		XAdd = -1;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			ptOld[i][j].x = enemyship[i][j].pos.x;
			ptOld[i][j].y = enemyship[i][j].pos.y;
			enemyship[i][j].pos.x += XAdd;
			enemyship[i][j].pos.y += YAdd;
		}
	}
}

int Calflag()
{
	int add;

	if (enemyship[0][0].pos.x < 1 || enemyship[0][MAX_ENEMY_BASE_COL].pos.x > 40)
	{
		if (flag == TRUE)
			flag = FALSE;
		else
			flag = TRUE;
		add = 1;
	}
	else
		add = 0;
	return add;
}

void Drawenemyship()
{
	UPOINT pos, posOld;
	int i, j;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			if (enemyship[i][j].flag == TRUE)
			{
				posOld.x = ptOld[i][j].x;
				posOld.y = ptOld[i][j].y;

				pos.x = enemyship[i][j].pos.x;
				pos.y = enemyship[i][j].pos.y;

				gotoxy(posOld);
				printf("   ");

				gotoxy(pos);
				printf("%s", enemyship_shape);
			}
		}
	}
}

void InitBullet()
{
	int i;

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		enemy_bullet[i].flag = FALSE;
		enemy_bullet[i].pos.x = 0;
		enemy_bullet[i].pos.y = 0;
	}
}

void Bulletshot()
{
	int i, randRow, randCol;

	while (1)
	{
		randRow = rand() % MAX_ENEMY_BASE_ROW;
		randCol = rand() % MAX_ENEMY_BASE_COL;
		if (enemyship[randRow][randCol].flag == FALSE)
			continue;
		break;
	}

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == FALSE)
		{
			enemy_bullet[i].flag = TRUE;
			enemy_bullet[i].pos.x = enemyship[randRow][randCol].pos.x;
			enemy_bullet[i].pos.y = enemyship[randRow][randCol].pos.y;
			break;
		}
	}
}

void DrawBullet()
{
	int i;
	UPOINT ptpos, oldpos;

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == TRUE)
		{
			if (enemy_bullet[i].pos.y > 23)
			{
				enemy_bullet[i].flag = FALSE;
				oldpos.x = enemy_bullet[i].pos.x;
				oldpos.y = enemy_bullet[i].pos.y;
				gotoxy(oldpos);
				printf(" ");
				break;
			}
			oldpos.x = enemy_bullet[i].pos.x;
			oldpos.y = enemy_bullet[i].pos.y;
			++enemy_bullet[i].pos.y;
			ptpos.x = enemy_bullet[i].pos.x;
			ptpos.y = enemy_bullet[i].pos.y;
			gotoxy(oldpos);
			printf(" ");
			gotoxy(ptpos);
			printf("|");
		}
	}
}

int Checkenemypos()
{
	int flag = FALSE, i, j;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			if (enemyship[i][j].flag == TRUE && enemyship[i][j].pos.y == 23)
			{
				flag = TRUE;
				return flag;
			}
		}
	}

	return flag;
}

void CheckEnemyBullet()
{
	int i, j, k;
	static BULLET boompos[MAX_MY_BULLET];
	static int flag;

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (boompos[i].flag == TRUE)
		{
			gotoxy(boompos[i].pos);
			printf("   ");
			boompos[i].flag = FALSE;
		}
	}

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (myship_bullet[i].flag == TRUE)
		{
			for (j = 0; j < MAX_ENEMY_BASE_ROW; j++)
			{
				for (k = 0; k < MAX_ENEMY_BASE_COL; k++)
				{
					if (enemyship[j][k].flag == TRUE)
					{
						if (enemyship[j][k].pos.x <= myship_bullet[i].pos.x &&
							myship_bullet[i].pos.x <= (enemyship[j][k].pos.x + 2) &&
							(enemyship[j][k].pos.y == myship_bullet[i].pos.y))
						{
							enemyship[j][k].flag = FALSE;
							gotoxy(enemyship[j][k].pos);
							printf(" *** ");
							myship_bullet[i].flag = FALSE;

							if (GetMyShipBulletType() == MY_BULLET_TYPE_BOMB)
							{
								for (int l = -1; l < 2; l++)
								{
									for (int m = -1; m < 2; m++)
									{
										if (l == 0 && m == 0)
											continue;
										int row = 0, col = 0;
										row = j + l;
										if (row < 0 || row > MAX_ENEMY_BASE_ROW)
											continue;

										col = k + m;
										if (row < 0 || row > MAX_ENEMY_BASE_COL)
											continue;

										if (enemyship[row][col].flag == TRUE)
										{
											enemyship[row][col].flag = FALSE;
											gotoxy(enemyship[row][col].pos);
											printf(" *** ");
											score += 100;
											killnum++;
										}
									}
								}

							}

							score += 100;
							killnum++;
							boompos[i].pos = enemyship[j][k].pos;
							boompos[i].flag = TRUE;
						}
					}
				}
			}
		}
	}
}


