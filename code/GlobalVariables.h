#ifndef GLOBAL_H
#define GLOBAL_H

#include "Player.h"
#include "Camera.h"
#include "Bullet.h"
#include "Enemy.h"
#include "HeadsUp.h"

#define GAME_ICON_MAX 9


const float MAX_X = 11;
const float MAX_Y = 8;
const float START_VEL = 4;

const int NUM_ENEMY = 23;

struct {
	uns buttonShoot; // button count

	//variables for icons
	int numIconTimer, iconH, iconW, targetH, targetW;
	float health, wWindow, wOrg, hWindow, hOrg, xScale, yScale, u0, u1, v0, v1;

	int score, ammo;



	Camera *cam;
	//HeadsUp *hud;
	HeadsUp *hud;
	Player *player;
	//Bullet *bullet;
	uns btnUp, btnDown, aDown, sDown;

	qeListBase listOfBullets;
	qeListBase listOfShips;
	qeListBase listOfEnemies;

	Enemy *enemyInstance[NUM_ENEMY];
	Enemy *enemyCol;
	Bullet *bulletCol;

	

	int shipsRemaining; // ships left
	int enemyCount;

	bit validCol;
	Vec3 xyzCol;
	Vec3 nrmCol;
   
	int isMusicPlaying;
	int id;
	int ones;
	int tens;
	int hundreds;
} Game;

#endif