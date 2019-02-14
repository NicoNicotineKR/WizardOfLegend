#include "stdafx.h"
#include "enemy_State_Attack.h"


enemy_State_Attack::enemy_State_Attack()
{
}


enemy_State_Attack::~enemy_State_Attack()
{
}

void enemy_State_Attack::direction_Left(enemy * enemy)
{
}

void enemy_State_Attack::direction_right(enemy * enemy)
{
}

void enemy_State_Attack::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
}
