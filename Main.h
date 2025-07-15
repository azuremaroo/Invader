#define MAX_ENEMY           40  
#define MAX_ENEMY_BASE_ROW    4   
#define MAX_ENEMY_BASE_COL   10  
#define MAX_ENEMY_BULLET     10  
#define ENEMY_SHIP_BASE_POSX 20   
#define ENEMY_SHIP_BASE_POSY  2  
#define TRUE                 1
#define FALSE                0

#define MAX_MY_BULLET         30  
#define MY_SHIP_BASE_POSX    38  
#define MY_SHIP_BASE_POSY    23  

#define MY_BULLET_TYPE_DEFAULT	 10
#define MY_BULLET_TYPE_THREE	 11

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <wincon.h>
#include "console.h"

typedef struct{  
	int flag;
	UPOINT pos;
	short bullet_type;
} MYSHIP;

typedef struct{ 
	int flag;
	UPOINT pos;
} BULLET;

typedef struct{ 
	int flag;
	UPOINT pos;
} ENEMYSHIP;

extern BULLET     myship_bullet[MAX_MY_BULLET];
extern BULLET     enemy_bullet[MAX_ENEMY_BULLET];
extern ENEMYSHIP  enemyship[MAX_ENEMY];
extern int        score,killnum;

void DrawMyship(UPOINT *pt,UPOINT*);
void InitMyship();
void MyBulletshot(UPOINT );
void DrawMyBullet();
int  CheckMybullet(UPOINT ptthisMypos);
void SetMyShipBulletType(short bulletType);

void Drawenemyship( );
void Initenemyship();
void CalenemyshipPos();
int  Checkenemypos();
int  Calflag();
void CalTime();
void Bulletshot();
void DrawBullet();
void InitBullet();
void CheckenemyBullet(ENEMYSHIP*);

void boom(UPOINT pt,int );
void play();

