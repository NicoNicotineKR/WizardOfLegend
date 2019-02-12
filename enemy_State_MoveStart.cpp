#include "stdafx.h"
#include "enemy_State_MoveStart.h"


enemy_State_MoveStart::enemy_State_MoveStart()
{
}


enemy_State_MoveStart::~enemy_State_MoveStart()
{
}

void enemy_State_MoveStart::direction_Left(enemy * enemy)
{
}

void enemy_State_MoveStart::direction_right(enemy * enemy)
{
}

void enemy_State_MoveStart::update(enemy * enemy)
{
	E_ANIDIRECTION save = enemy->getAniDirection();
	enemy->fixDirection();
	if (save != enemy->getAniDirection())
	{
		enemy->startAni();
	}
}
