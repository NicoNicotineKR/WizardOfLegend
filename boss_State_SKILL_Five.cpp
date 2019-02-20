#include "stdafx.h"
#include "boss_State_SKILL_Five.h"


boss_State_SKILL_Five::boss_State_SKILL_Five()
{
}


boss_State_SKILL_Five::~boss_State_SKILL_Five()
{
}

void boss_State_SKILL_Five::update(boss * boss)
{
	if (!boss->getAni()->isPlay())
	{
		boss->useSkill();
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
