#pragma once
#include "enemyState.h"
class enemy_State_Spawn : public enemyState
{
public:
	enemy_State_Spawn();
	~enemy_State_Spawn();
public:
	virtual void direction_Left(enemy* enemy) override;
	virtual void direction_right(enemy* enemy) override;
	virtual void update(enemy* enemy) override;
};

