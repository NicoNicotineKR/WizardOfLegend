#include "stdafx.h"
#include "boss_State_SKILL_Two.h"


boss_State_SKILL_Two::boss_State_SKILL_Two()
{
}


boss_State_SKILL_Two::~boss_State_SKILL_Two()
{
}

void boss_State_SKILL_Two::update(boss * boss)
{
	//�ֱ�
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
