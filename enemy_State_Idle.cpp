#include "stdafx.h"
#include "enemy_State_Idle.h"


enemy_State_Idle::enemy_State_Idle()
{
}


enemy_State_Idle::~enemy_State_Idle()
{
}

void enemy_State_Idle::direction_Left(enemy * enemy)
{
	enemy->fixDirection();
	if (enemy->getAniDirection() == E_ANIDIRECTION::LEFT)
	{
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::MOVE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
	else if (enemy->getAniDirection() == E_ANIDIRECTION::RIGHT)
	{
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::MOVE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Idle::direction_right(enemy * enemy)
{
	enemy->fixDirection();
	if (enemy->getAniDirection() == E_ANIDIRECTION::LEFT)
	{
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::MOVE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
	else if (enemy->getAniDirection() == E_ANIDIRECTION::RIGHT)
	{
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::MOVE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Idle::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
}
