#include "stdafx.h"
#include "boss_State_SKILL_Four.h"


boss_State_SKILL_Four::boss_State_SKILL_Four()
{
}


boss_State_SKILL_Four::~boss_State_SKILL_Four()
{
}

void boss_State_SKILL_Four::update(boss * boss)
{
	if (!boss->getAni()->isPlay())
	{
		boss->useSkill();
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
