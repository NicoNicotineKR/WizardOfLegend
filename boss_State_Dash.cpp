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
	//if(맨처음 대쉬가될때 저장해둔 플레이어가 있던곳에 도착하면)  스킬 4로 변경
	{
		boss->setState(B_STATE::SKILL_FOUR);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
