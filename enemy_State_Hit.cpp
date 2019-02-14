#include "stdafx.h"
#include "enemy_State_Hit.h"


enemy_State_Hit::enemy_State_Hit()
{
}


enemy_State_Hit::~enemy_State_Hit()
{
}

void enemy_State_Hit::direction_Left(enemy * enemy)
{
}

void enemy_State_Hit::direction_right(enemy * enemy)
{
}

void enemy_State_Hit::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
}
