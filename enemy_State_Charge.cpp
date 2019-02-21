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
		enemy->setCountIdY(0);
		enemy->setAtkRc(enemy->getAtkPos());
		enemy->setCurCharge(0.f);
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::ATTACK);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();

		if (enemy->getWhoIM() == GHOUL)
		{
			SOUNDMANAGER->play("goul", OPTIONMANAGER->getSoundEffectVolume());
		}
		if (enemy->getWhoIM() == KNIGHT)
		{
			SOUNDMANAGER->play("KnightAttack", OPTIONMANAGER->getSoundEffectVolume());
		}
	}
}

void enemy_State_Charge::direction_right(enemy * enemy)
{
	float charging = TIMEMANAGER->getElapsedTime();
	enemy->setCurCharge(enemy->getCurCharge() + charging);

	if (enemy->getCurCharge() > enemy->getMaxCharge())
	{
		enemy->setCountIdY(0);
		enemy->setAtkRc(enemy->getAtkPos());
		enemy->setCurCharge(0.f);
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::ATTACK);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();

		if (enemy->getWhoIM() == GHOUL)
		{
			SOUNDMANAGER->play("goul", OPTIONMANAGER->getSoundEffectVolume());
		}
		if (enemy->getWhoIM() == KNIGHT)
		{
			SOUNDMANAGER->play("KnightAttack", OPTIONMANAGER->getSoundEffectVolume());
		}
	}
}

void enemy_State_Charge::update(enemy * enemy)
{
	if (enemy->getCurHP() <= 0)
	{
		enemy->setState(E_STATE::DEATH);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
}
