#include "stdafx.h"
#include "boss_State_Death.h"


boss_State_Death::boss_State_Death()
{
}


boss_State_Death::~boss_State_Death()
{
}

void boss_State_Death::update(boss * boss)
{
	if (!boss->getCrystalAni()->isPlay())
	{
		boss->setPos({ -1000, -1000 });
		//여기다 엔딩으로가는거 넣자
	}
}
