#define MAX_ENEMY           40  
#define MAX_ENEMY_BASE_ROW    4
#define MAX_ENEMY_BASE_COL   10  
#define MAX_ENEMY_BULLET     10  
#define ENEMY_SHIP_BASE_POSX 20   
#define ENEMY_SHIP_BASE_POSY  2  
#define MAX_ENEMY_SHIP_POSY  23

#define TRUE                 1
#define FALSE                0

#define MAX_MY_BULLET         30  
#define MY_SHIP_BASE_POSX    38  
#define MY_SHIP_BASE_POSY    23  

#define MY_BULLET_TYPE_DEFAULT	 1
#define MY_BULLET_TYPE_THREE	 3
#define MY_BULLET_TYPE_BOMB		 5

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <wincon.h>
#include "console.h"

typedef struct {
	int flag;
	UPOINT pos;
	int bullet_type;
} MYSHIP;

typedef struct {
	int flag;
	UPOINT pos;
} BULLET;

typedef struct {
	int flag;
	UPOINT pos;
} ENEMYSHIP;

extern BULLET     my_bullet[MAX_MY_BULLET];
extern BULLET     enemy_bullet[MAX_ENEMY_BULLET];
extern ENEMYSHIP enemyShip[MAX_ENEMY_BASE_ROW][MAX_ENEMY_BASE_COL];

extern int        score, killnum;

void DrawMyship(UPOINT* pt, UPOINT*);
void InitMyship();
void ShotMyBullet(UPOINT);
void ActiveMyBullet(BULLET* bullet, int x, int y);
void DrawMyBullet();
int  CheckMybullet(UPOINT ptthisMypos);
void SetMyBulletType(int bulletType);
int GetMyBulletType();
int CheckMyBulletType(int bulletType);
void InitMyBullet();

void Drawenemyship();
void InitEnemyship();
void CalenemyshipPos();

/// <summary>
/// 적 기체가 바닥까지 내려왔는지 확인
/// </summary>
/// <returns>1: 바닥 도착, 0: 아직 미도착</returns>
int  CheckEnemyPos();
int  Calflag();
void CalTime();
void ShotBullet();
void DrawBullet();
void InitEnemyBullet();

/// <summary>
/// 적 기체 사망 확인
/// </summary>
/// <returns>TRUE: 모든 기체가 소멸한 경우</returns>
int CheckKilledEnemy();
void AddEnemyShip(ENEMYSHIP* enemyShip, UPOINT* oldPoint, int x, int y);
void KillEnemyShip(ENEMYSHIP* enemyShip);

void boom(UPOINT pt, int);
void Play();

