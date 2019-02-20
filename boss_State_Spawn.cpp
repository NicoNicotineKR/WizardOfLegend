#include "stdafx.h"
#include "boss_State_Spawn.h"


boss_State_Spawn::boss_State_Spawn()
{
}


boss_State_Spawn::~boss_State_Spawn()
{
}

void boss_State_Spawn::update(boss * boss)
{
	if (!boss->getAni()->isPlay())
	{
		boss->setState(B_STATE::IDLE);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
