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
	if (!boss->getAni()->isPlay())
	{
		boss->setState(B_STATE::CASTING);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
