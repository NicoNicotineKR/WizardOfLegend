#include "stdafx.h"
#include "state_Skill_One.h"


state_Skill_One::state_Skill_One()
{
}


state_Skill_One::~state_Skill_One()
{
}

void state_Skill_One::onButtonW(player* Player)
{
}

void state_Skill_One::onButtonS(player* Player)
{
}

void state_Skill_One::onButtonA(player* Player)
{
}

void state_Skill_One::onButtonD(player* Player)
{
}

void state_Skill_One::offButtonW(player * Player)
{
}

void state_Skill_One::offButtonS(player * Player)
{
}

void state_Skill_One::offButtonA(player * Player)
{
}

void state_Skill_One::offButtonD(player * Player)
{
}

void state_Skill_One::onButtonQ(player* Player)
{
}

void state_Skill_One::onButtonE(player* Player)
{
}

void state_Skill_One::onButtonR(player* Player)
{
}

void state_Skill_One::onButtonSpace(player* Player)
{
}

void state_Skill_One::onButtonLB(player* Player)
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
				SOUNDMANAGER->play("flameStrike", OPTIONMANAGER->getSoundEffectVolume());
				Player->getArrCurSkills(num)->setReLoadCount(Player->getArrCurSkills(num)->getReLoadCount() + 1);
			}

		}
}

void state_Skill_One::onButtonRB(player* Player)
{
	
}

void state_Skill_One::update(player* Player)
{
}
