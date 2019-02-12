#include "stdafx.h"
#include "enemy_State_Move.h"


enemy_State_Move::enemy_State_Move()
{
}


enemy_State_Move::~enemy_State_Move()
{
}

void enemy_State_Move::direction_Left(enemy * enemy)
{
	if (ATTACK_RANGE > getDistance(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y))
	{
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Move::direction_right(enemy * enemy)
{
	if (ATTACK_RANGE > getDistance(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y))
	{
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Move::update(enemy * enemy)
{
	E_ANIDIRECTION save = enemy->getAniDirection();
	enemy->fixDirection();
	if (save != enemy->getAniDirection())
	{
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}
