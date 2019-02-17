#include "stdafx.h"
#include "enemy_State_Death.h"


enemy_State_Death::enemy_State_Death()
{
}


enemy_State_Death::~enemy_State_Death()
{
}

void enemy_State_Death::direction_Left(enemy * enemy)
{
}

void enemy_State_Death::direction_right(enemy * enemy)
{
}

void enemy_State_Death::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
	enemy->defaultAtkRc();
}
