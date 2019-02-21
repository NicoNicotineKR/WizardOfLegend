#include "stdafx.h"
#include "boss_State_Mock.h"


boss_State_Mock::boss_State_Mock()
{
}


boss_State_Mock::~boss_State_Mock()
{
}

void boss_State_Mock::update(boss * boss)
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

	if (boss->getIsStun())
	{
		boss->setState(B_STATE::STUN);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}

	
	if (!boss->getAni()->isPlay())
	{
		boss->setBossStateCasting();
	}
}
