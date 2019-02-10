#pragma once
#include "enemyState.h"

class enemy_State_Charge : public enemyState
{
public:
	enemy_State_Charge();
	~enemy_State_Charge();
public:
	virtual void direction_Left(enemy* enemy) override;
	virtual void direction_right(enemy* enemy) override;
	virtual void update(enemy* enemy) override;
};

