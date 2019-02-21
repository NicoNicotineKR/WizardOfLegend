#include "stdafx.h"
#include "boss_State_Stun.h"


boss_State_Stun::boss_State_Stun()
{
}


boss_State_Stun::~boss_State_Stun()
{
}

void boss_State_Stun::update(boss * boss)
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
		boss->setState(B_STATE::CASTING);
		boss->setIsStun(false);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
