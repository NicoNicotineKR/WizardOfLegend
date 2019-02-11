#pragma once
#include "enemy.h"

class enemy_Knight : public enemy
{
public:
	enemy_Knight();
	~enemy_Knight();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemyKeyAnimationInit();
	void enemyArrStateInit();
	void startAni();

	static void knight_Moving(void* obj);
};

