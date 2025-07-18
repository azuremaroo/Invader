#include "main.h"

char  enemyship_shape[5] = "^V^";
short isRight, addEnemyFlag, enemyLife;
BULLET enemy_bullet[MAX_ENEMY_BULLET];
ENEMYSHIP enemyShip[MAX_ENEMY_BASE_ROW][MAX_ENEMY_BASE_COL];
UPOINT ptOld[MAX_ENEMY_BASE_ROW][MAX_ENEMY_BASE_COL];

void InitEnemyship()
{
	int i, j, posX, posY;

	isRight = FALSE;
	enemyLife = 0;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			posX = ENEMY_SHIP_BASE_POSX + j * 4;
			posY = ENEMY_SHIP_BASE_POSY + i * 2;
			AddEnemyShip(&enemyShip[i][j], &ptOld[i][j], posX, posY);
		}
	}

	InitEnemyBullet();
}

void CalenemyshipPos()
{
	short findEmptyLine = FALSE;
	int i, j, xAdd, yAdd, posX;

	yAdd = Calflag();
	if (isRight == FALSE)
		xAdd = 1;
	else
		xAdd = -1;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			ptOld[i][j].x = enemyShip[i][j].pos.x;
			ptOld[i][j].y = enemyShip[i][j].pos.y;

			enemyShip[i][j].pos.x += xAdd;
			enemyShip[i][j].pos.y += yAdd;
		}
	}
}

int Calflag()
{
	int add, i, j, minX = INT_MAX, maxX = 0;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			if (enemyShip[i][j].flag == TRUE)
			{
				if (enemyShip[i][j].pos.x < minX) minX = enemyShip[i][j].pos.x;
				if (maxX < enemyShip[i][j].pos.x) maxX = enemyShip[i][j].pos.x;
			}
		}
	}

	if (minX < 1 || maxX > 73)
	{
		if (isRight == TRUE)
			isRight = FALSE;
		else
			isRight = TRUE;
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
			if (enemyShip[i][j].flag == TRUE)
			{
				posOld.x = ptOld[i][j].x;
				posOld.y = ptOld[i][j].y;

				pos.x = enemyShip[i][j].pos.x;
				pos.y = enemyShip[i][j].pos.y;

				gotoxy(posOld);
				printf("   ");

				gotoxy(pos);
				printf("%s", enemyship_shape);
			}
		}
	}
}

void InitEnemyBullet()
{
	int i;

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		enemy_bullet[i].flag = FALSE;
		enemy_bullet[i].pos.x = 0;
		enemy_bullet[i].pos.y = 0;
	}
}

void ShotBullet()
{
	int i, randRow, randCol;

	while (1)
	{
		randRow = rand() % MAX_ENEMY_BASE_ROW;
		randCol = rand() % MAX_ENEMY_BASE_COL;
		if (enemyShip[randRow][randCol].flag == FALSE)
			continue;
		break;
	}

	for (i = 0; i < MAX_ENEMY_BULLET; i++)
	{
		if (enemy_bullet[i].flag == FALSE)
		{
			enemy_bullet[i].flag = TRUE;
			enemy_bullet[i].pos.x = enemyShip[randRow][randCol].pos.x;
			enemy_bullet[i].pos.y = enemyShip[randRow][randCol].pos.y;
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

int CheckEnemyPos()
{
	int flag = FALSE, i, j;

	for (i = 0; i < MAX_ENEMY_BASE_ROW; i++)
	{
		for (j = 0; j < MAX_ENEMY_BASE_COL; j++)
		{
			if (enemyShip[i][j].flag == TRUE && enemyShip[i][j].pos.y == MAX_ENEMY_SHIP_POSY)
			{
				flag = TRUE;
				return flag;
			}
		}
	}

	return flag;
}

int CheckKilledEnemy()
{
	int i, j, k;
	static BULLET boompos[MAX_MY_BULLET];
	static int flag;

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (boompos[i].flag == TRUE)
		{
			gotoxy(boompos[i].pos);
			printf("     ");
			boompos[i].flag = FALSE;

			// ÆøÅº¿¡ ¸ÂÀº °æ¿ì »óÇÏÁÂ¿ì 1Ä­µµ ÀÜ»ó Áö¿ì±â
			if (CheckMyBulletType(MY_BULLET_TYPE_BOMB))
			{
				for (int l = -1; l < 2; l++)
				{
					for (int m = -1; m < 2; m++)
					{
						if (l == 0 && m == 0)
							continue;

						UPOINT tempPos = { boompos[i].pos.x + (l * 4), boompos[i].pos.y + (m * 2) };
						gotoxy(tempPos);
						printf("     ");
					}
				}
			}
		}
	}

	for (i = 0; i < MAX_MY_BULLET; i++)
	{
		if (my_bullet[i].flag == TRUE)
		{
			for (j = 0; j < MAX_ENEMY_BASE_ROW; j++)
			{
				for (k = 0; k < MAX_ENEMY_BASE_COL; k++)
				{
					if (enemyShip[j][k].flag == TRUE)
					{
						if (enemyShip[j][k].pos.x <= my_bullet[i].pos.x && my_bullet[i].pos.x <= (enemyShip[j][k].pos.x + 2)
							&& (enemyShip[j][k].pos.y == my_bullet[i].pos.y))
						{
							my_bullet[i].flag = FALSE;

							KillEnemyShip(&enemyShip[j][k]);

							if (CheckMyBulletType(MY_BULLET_TYPE_BOMB))
							{
								for (int l = -1; l < 2; l++)
								{
									for (int m = -1; m < 2; m++)
									{
										if (l == 0 && m == 0)
											continue;

										int row = 0, col = 0;
										row = j + l;

										if (row < 0 || row >= MAX_ENEMY_BASE_ROW)
											continue;

										col = k + m;
										if (row < 0 || row >= MAX_ENEMY_BASE_COL)
											continue;

										if (enemyShip[row][col].flag == TRUE)
										{
											KillEnemyShip(&enemyShip[row][col]);
										}
									}
								}
							}

							boompos[i].pos = enemyShip[j][k].pos;
							boompos[i].flag = TRUE;
						}
					}
				}
			}
		}
	}

	// ¸ðµç Àû ±âÃ¼°¡ Á×Àº °æ¿ì
	if (enemyLife == 0)
	{
		return TRUE;
	}

	return FALSE;
}

void AddEnemyShip(ENEMYSHIP* enemyShip, UPOINT* oldPoint, int x, int y)
{
	enemyShip->flag = TRUE;
	enemyShip->pos.x = x;
	enemyShip->pos.y = y;
	oldPoint->x = x;
	oldPoint->y = y;
	enemyLife++;
}

void KillEnemyShip(ENEMYSHIP* enemyShip)
{
	enemyShip->flag = FALSE;
	gotoxy(enemyShip->pos);
	printf(" *** ");
	score += 100;
	killnum++;
	enemyLife--;
};


