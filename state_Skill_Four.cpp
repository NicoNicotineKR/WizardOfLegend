#include "stdafx.h"
#include "state_Skill_Four.h"


state_Skill_Four::state_Skill_Four()
{
}


state_Skill_Four::~state_Skill_Four()
{
}

void state_Skill_Four::onButtonW(player* Player)
{
}

void state_Skill_Four::onButtonS(player* Player)
{
}

void state_Skill_Four::onButtonA(player* Player)
{
}

void state_Skill_Four::onButtonD(player* Player)
{
}

void state_Skill_Four::offButtonW(player * Player)
{
}

void state_Skill_Four::offButtonS(player * Player)
{
}

void state_Skill_Four::offButtonA(player * Player)
{
}

void state_Skill_Four::offButtonD(player * Player)
{
}

void state_Skill_Four::onButtonQ(player* Player)
{
	int num;
	for (int i = 0; i < 4; ++i)
	{
		if (Player->getArrCurSkills(i)->getName() == "stoneShot" || Player->getArrCurSkills(i)->getName() == "FlameStrike")
		{
			num = i;
			Player->setBasicSkillNum(num);
			break;
		}
	}

	if (Player->getArrCurSkills(num)->getName() == "stoneShot")
	{
		if (Player->getArrCurSkills(num)->getReLoadCount() < 2)
		{
			Player->getArrCurSkills(num)->setReLoadCount(Player->getArrCurSkills(num)->getReLoadCount() + 1);
		}
		else
		{
			return;
		}
	}
	Player->setUsingSkillName(Player->getArrCurSkills(num)->getName());
	if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
		(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
	{
		Player->setAniDirection(ANIDIRECTION::RIGHT);
		Player->startAni();
	}
	if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
		Player->getPlayerAngle() * (180 / PI) < 225))
	{
		Player->setAniDirection(ANIDIRECTION::LEFT);
		Player->startAni();
	}
	if (Player->getPlayerAngle()* (180 / PI) > 45 &&
		Player->getPlayerAngle() * (180 / PI) <= 135)
	{
		Player->setAniDirection(ANIDIRECTION::BACK);
		Player->startAni();
	}
	if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
		Player->getPlayerAngle() * (180 / PI) < 315)
	{
		Player->setAniDirection(ANIDIRECTION::FRONT);
		Player->startAni();
	}
	if (Player->getArrCurSkills(num)->getName() == "FlameStrike")
	{
		if (Player->getArrCurSkills(num)->getReLoadCount() < 3)
		{
			Player->getArrCurSkills(num)->setReLoadCount(Player->getArrCurSkills(num)->getReLoadCount() + 1);
		}

	}
}

void state_Skill_Four::onButtonE(player* Player)
{
}

void state_Skill_Four::onButtonR(player* Player)
{
}

void state_Skill_Four::onButtonSpace(player* Player)
{
}

void state_Skill_Four::onButtonLB(player* Player)
{
}

void state_Skill_Four::onButtonRB(player* Player)
{
}

void state_Skill_Four::update(player* Player)
{
}
