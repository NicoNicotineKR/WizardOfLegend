#pragma once
#include "enemy.h"

class enemy_Knight : public enemy
{
private:
	const int POS_Y_IMAGE_SHAVE = 110;
	const int POS_Y_HIT_SHAVE = 70;
	const int HIT_RC_WIDTH = 50;
	const int HIT_RC_HEIGHT = 140;

	const int ATTACK_RANGE = 120 * 120;
	const int WEAPON_RANGE = 80;
public:
	enemy_Knight();
	~enemy_Knight();

	HRESULT init();
	void release();
	void update();
	void render();
	void CamRender();

	void enemyKeyAnimationInit();
	void enemyArrStateInit();
	void startAni();

	void move();

	int getAtkRange() { return ATTACK_RANGE; }
	int getWeaponRange() { return WEAPON_RANGE; }
};

