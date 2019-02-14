#pragma once
#include "enemyState.h"
class enemy_State_Move : public enemyState
{
private:
	const int ATTACK_RANGE = 100 * 100;

	const int TILE_SIZE = 32;
public:
	enemy_State_Move();
	~enemy_State_Move();
public:
	virtual void direction_Left(enemy* enemy) override;
	virtual void direction_right(enemy* enemy) override;
	virtual void update(enemy* enemy) override;
};

