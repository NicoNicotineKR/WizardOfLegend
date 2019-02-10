#pragma once
class enemy_Knight
{
public:
	enemy_Knight();
	~enemy_Knight();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemyKeyAnimationInit();

	static void knight_rightMoving(void* obj);
};

