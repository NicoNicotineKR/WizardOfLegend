#include "stdafx.h"
#include "boss_State_Casting.h"


boss_State_Casting::boss_State_Casting()
{
}


boss_State_Casting::~boss_State_Casting()
{
}

void boss_State_Casting::update(boss * boss)
{
	//аж╠щ
	if (boss->getIsDead())
	{
		boss->setState(B_STATE::DEATH_START);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
		boss->setIsDead(false);
	}


	if (!boss->getAni()->isPlay())
	{
		boss->useSkill();
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
