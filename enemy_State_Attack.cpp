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
	if (enemy->getCurHP() < 0)
	{
		enemy->setState(E_STATE::DEATH);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
	if (!enemy->getAni()->isPlay())
	{
		enemy->setState(E_STATE::MOVE);
		enemy->fixDirection();
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}

	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}

	enemy->setCountIdY(enemy->getCountIdY() + 1);

	if (enemy->getCountIdY() / (enemy->getEffectTime() / 3) == 0)
	{
		enemy->setAtkIdY(0);
	}
	if (enemy->getCountIdY() / (enemy->getEffectTime() / 3) == 1)
	{
		enemy->setAtkIdY(1);
	}
	if (enemy->getCountIdY() / (enemy->getEffectTime() / 3) == 2)
	{
		enemy->setAtkIdY(2);
	}

	if (enemy->getCountIdY() == enemy->getEffectTime())
	{
		enemy->defaultAtkRc();
	}
}
