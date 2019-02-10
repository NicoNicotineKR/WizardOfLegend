#pragma once
#include "enemyState.h"
class enemy_State_Charging : public enemyState
{
public:
	enemy_State_Charging();
	~enemy_State_Charging();
public:
	virtual void direction_Left(enemy* enemy) override;
	virtual void direction_right(enemy* enemy) override;
	virtual void update(enemy* enemy) override;
};

