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
	//if(��ó�� �뽬���ɶ� �����ص� �÷��̾ �ִ����� �����ϸ�)  ��ų 4�� ����
	{
		boss->setState(B_STATE::SKILL_FOUR);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
