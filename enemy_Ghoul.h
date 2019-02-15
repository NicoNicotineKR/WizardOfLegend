#pragma once
#include "enemy.h"
class enemy_Ghoul : public enemy
{
private:
	const int POS_Y_IMAGE_SHAVE = 60;
	const int POS_Y_HIT_SHAVE = 50;
	const int HIT_RC_WIDTH = 50;
	const int HIT_RC_HEIGHT = 120;

	const int ATTACK_RANGE = 100 * 100;
	const int WEAPON_RANGE = 60;
public:
	enemy_Ghoul();
	~enemy_Ghoul();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemyKeyAnimationInit();
	void enemyArrStateInit();
	void startAni();

	void move();

	int getAtkRange() { return ATTACK_RANGE; }
	int getWeaponRange() { return WEAPON_RANGE; }

	static void ghoul_Move(void* obj);
};

