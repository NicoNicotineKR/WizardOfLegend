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

	enemy->setCountIdY(enemy->getCountIdY() + 1);

	if (enemy->getCountIdY() % 10 == 1)
	{
		enemy->setAtkIdY(0);
	}
	if (enemy->getCountIdY() % 10 == 2)
	{
		enemy->setAtkIdY(1);
	}
	if (enemy->getCountIdY() % 10 == 3)
	{
		enemy->setAtkIdY(2);
	}
}
