#pragma once
#include "enemyState.h"
class enemy_State_MoveStart : public enemyState
{
public:
	enemy_State_MoveStart();
	~enemy_State_MoveStart();
public:
	virtual void direction_Left(enemy* enemy) override;
	virtual void direction_right(enemy* enemy) override;
	virtual void update(enemy* enemy) override;
};

