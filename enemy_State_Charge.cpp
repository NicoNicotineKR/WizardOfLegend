#include "stdafx.h"
#include "enemy_State_Charge.h"


enemy_State_Charge::enemy_State_Charge()
{
}


enemy_State_Charge::~enemy_State_Charge()
{
}

void enemy_State_Charge::direction_Left(enemy * enemy)
{
	float charging = TIMEMANAGER->getElapsedTime();
	enemy->setCurCharge(enemy->getCurCharge() + charging);

	if (enemy->getCurCharge() > enemy->getMaxCharge())
	{
		enemy->setCurCharge(0.f);
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::ATTACK);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Charge::direction_right(enemy * enemy)
{
	float charging = TIMEMANAGER->getElapsedTime();
	enemy->setCurCharge(enemy->getCurCharge() + charging);

	if (enemy->getCurCharge() > enemy->getMaxCharge())
	{
		enemy->setCurCharge(0.f);
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::ATTACK);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Charge::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
}
