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
	//�ֱ�
	if (boss->getIsDead())
	{
		boss->setState(B_STATE::DEATH_START);
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
		boss->setIsDead(false);
	}

	//if(��ó�� �뽬���ɶ� �����ص� �÷��̾ �ִ����� �����ϸ�)  ��ų 4�� ����
	if(!boss->getSkill4()->getIsStart())
	{
		boss->useSkill();
		boss->bossCurrentState();
		boss->setIsAniOnce(true);
		boss->startAni();
	}
}
