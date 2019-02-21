#include "stdafx.h"
#include "boss_State_SKILL_Three.h"


boss_State_SKILL_Three::boss_State_SKILL_Three()
{
}


boss_State_SKILL_Three::~boss_State_SKILL_Three()
{
}

void boss_State_SKILL_Three::update(boss * boss)
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
