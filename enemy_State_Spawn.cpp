#include "stdafx.h"
#include "enemy_State_Spawn.h"


enemy_State_Spawn::enemy_State_Spawn()
{
}


enemy_State_Spawn::~enemy_State_Spawn()
{
}

void enemy_State_Spawn::direction_Left(enemy * enemy)
{
}

void enemy_State_Spawn::direction_right(enemy * enemy)
{
}

void enemy_State_Spawn::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
}
