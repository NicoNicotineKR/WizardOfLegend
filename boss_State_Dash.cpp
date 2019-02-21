#include "stdafx.h"
#include "boss_State_Dash.h"


boss_State_Dash::boss_State_Dash()
{
}


boss_State_Dash::~boss_State_Dash()
{
}

void boss_State_Dash::update(boss * boss)
{
	//주금
	if (boss->getIsDead())
	{
		boss->setState(B_STATE::DEATH_START);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
		boss->setIsDead(false);
	}

	//if(맨처음 대쉬가될때 저장해둔 플레이어가 있던곳에 도착하면)  스킬 4로 변경
	if(!boss->getSkill4()->getIsStart())
	{
		boss->useSkill();
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
