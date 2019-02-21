#include "stdafx.h"
#include "state_Idle.h"


state_Idle::state_Idle()
{
}


state_Idle::~state_Idle()
{
}

void state_Idle::onButtonW(player* Player)
{
	Player->setMoveDirection(MOVEDIRECTION::TOP);
	Player->setAniDirection(ANIDIRECTION::BACK);
	Player->setState(STATE::MOVE);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Idle::onButtonS(player* Player)
{
	Player->setMoveDirection(MOVEDIRECTION::BOTTOM);
	Player->setAniDirection(ANIDIRECTION::FRONT);
	Player->setState(STATE::MOVE);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Idle::onButtonA(player* Player)
{
	Player->setMoveDirection(MOVEDIRECTION::LEFT);
	Player->setAniDirection(ANIDIRECTION::LEFT);
	Player->setState(STATE::MOVE);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Idle::onButtonD(player* Player)
{
		Player->setMoveDirection(MOVEDIRECTION::RIGHT);
		Player->setAniDirection(ANIDIRECTION::RIGHT);
		Player->setState(STATE::MOVE);
		Player->currentPlayerState();
		Player->startAni();
}

void state_Idle::offButtonW(player * Player)
{
}

void state_Idle::offButtonS(player * Player)
{
}

void state_Idle::offButtonA(player * Player)
{
}

void state_Idle::offButtonD(player * Player)
{
}

void state_Idle::onButtonQ(player* Player)
{
	skillUse(3, Player->getCurSkills4()->getName(), Player);
	//if (Player->getCurSkills4()->getName() == "shockNova")
	//{
	//	if (!Player->getCurSkills4()->getIsSkill())
	//	{
	//		Player->getCurSkills4()->setIsSkill(true);
	//		Player->getCurSkills4()->skillPosSet(Player);
	//		Player->getCurSkills4()->setReLoadCount(0);
	//		Player->getSkillUI()->UseIdxSkill(3);
	//		Player->setUsingSkillName(Player->getCurSkills4()->getName());
	//		if (Player->getPlayerAngle() * (180 / PI) > 45 &&
	//			Player->getPlayerAngle() * (180 / PI) < 135)
	//		{
	//			Player->setState(STATE::SKILL_FOUR);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::BACK);
	//			Player->startAni();
	//		}
	//		else
	//		{
	//			Player->setState(STATE::SKILL_FOUR);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::FRONT);
	//			Player->startAni();
	//		}
	//	}
	//}
	//else if (Player->getCurSkills4()->getName() == "thunderingChain")
	//{
	//	if (!Player->getCurSkills4()->getIsSkill())
	//	{
	//		Player->setUsingSkillName(Player->getCurSkills3()->getName());
	//		if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
	//			(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
	//		{
	//			Player->setState(STATE::SKILL_FOUR);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::RIGHT);
	//			Player->startAni();
	//		}
	//		if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
	//			Player->getPlayerAngle() * (180 / PI) < 225))
	//		{
	//			Player->setState(STATE::SKILL_FOUR);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::LEFT);
	//			Player->startAni();
	//		}
	//		if (Player->getPlayerAngle()* (180 / PI) > 45 &&
	//			Player->getPlayerAngle() * (180 / PI) <= 135)
	//		{
	//			Player->setState(STATE::SKILL_FOUR);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::BACK);
	//			Player->startAni();
	//		}
	//		if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
	//			Player->getPlayerAngle() * (180 / PI) < 315)
	//		{
	//			Player->setState(STATE::SKILL_FOUR);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::FRONT);
	//			Player->startAni();
	//		}
	//
	//		Player->getCurSkills4()->skillPosSet(Player);
	//		Player->getSkillUI()->UseIdxSkill(3);
	//		Player->getCurSkills4()->setReLoadCount(0);
	//		Player->getCurSkills4()->setIsSkill(true);
	//	}
	//}

}

void state_Idle::onButtonE(player* Player)
{

}

void state_Idle::onButtonR(player* Player)
{

}

void state_Idle::onButtonSpace(player* Player)
{
	if (!Player->getCurSkills2()->getIsSkill())
	{
		Player->getCurSkills2()->setIsSkill(true);
		Player->getCurSkills2()->skillPosSet(Player);
		Player->getCurSkills2()->setReLoadCount(0);
		Player->getSkillUI()->UseIdxSkill(1);
	}
	Player->setState(STATE::DASH);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Idle::onButtonLB(player* Player)
{
	skillUse(0, Player->getCurSkills1()->getName(), Player);
	//if (!Player->getCurSkills1()->getIsSkill())
	//{
	//
	//	Player->setUsingSkillName(Player->getCurSkills1()->getName());
	//	Player->getCurSkills1()->skillPosSet(Player);
	//	Player->getSkillUI()->UseIdxSkill(0);
	//	Player->getCurSkills1()->setIsSkill(true);
	//
	//	if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
	//		(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
	//	{
	//		Player->setState(STATE::SKILL_ONE);
	//		Player->currentPlayerState();
	//		Player->setAniDirection(ANIDIRECTION::RIGHT);
	//		Player->startAni();
	//	}
	//	if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
	//		Player->getPlayerAngle() * (180 / PI) < 225))
	//	{
	//		Player->setState(STATE::SKILL_ONE);
	//		Player->currentPlayerState();
	//		Player->setAniDirection(ANIDIRECTION::LEFT);
	//		Player->startAni();
	//	}
	//	if (Player->getPlayerAngle()* (180 / PI) > 45 &&
	//		Player->getPlayerAngle() * (180 / PI) <= 135)
	//	{
	//		Player->setState(STATE::SKILL_ONE);
	//		Player->currentPlayerState();
	//		Player->setAniDirection(ANIDIRECTION::BACK);
	//		Player->startAni();
	//	}
	//	if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
	//		Player->getPlayerAngle() * (180 / PI) < 315)
	//	{
	//		Player->setState(STATE::SKILL_ONE);
	//		Player->currentPlayerState();
	//		Player->setAniDirection(ANIDIRECTION::FRONT);
	//		Player->startAni();
	//	}
	//	if (Player->getCurSkills1()->getName() == "FlameStrike")
	//	{
	//		Player->getCurSkills1()->setReLoadCount(Player->getCurSkills1()->getReLoadCount() + 1);
	//	}
	//}
}

void state_Idle::onButtonRB(player* Player)
{
	skillUse(2, Player->getCurSkills3()->getName(), Player);
}

void state_Idle::update(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('W') ||
		KEYMANAGER->isStayKeyDown('S') ||
		KEYMANAGER->isStayKeyDown('A') ||
		KEYMANAGER->isStayKeyDown('D'))
	{
		Player->setState(STATE::MOVE);
		Player->currentPlayerState();

		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A'))
		{
			Player->setMoveDirection(MOVEDIRECTION::LEFT_TOP);
			Player->setAniDirection(ANIDIRECTION::LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D'))
		{
			Player->setMoveDirection(MOVEDIRECTION::RIGHT_TOP);
			Player->setAniDirection(ANIDIRECTION::RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A'))
		{
			Player->setMoveDirection(MOVEDIRECTION::LEFT_BOTTOM);
			Player->setAniDirection(ANIDIRECTION::LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D'))
		{
			Player->setMoveDirection(MOVEDIRECTION::RIGHT_BOTTOM);
			Player->setAniDirection(ANIDIRECTION::RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			Player->setMoveDirection(MOVEDIRECTION::TOP);
			Player->setAniDirection(ANIDIRECTION::BACK);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			Player->setMoveDirection(MOVEDIRECTION::BOTTOM);
			Player->setAniDirection(ANIDIRECTION::FRONT);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			Player->setMoveDirection(MOVEDIRECTION::LEFT);
			Player->setAniDirection(ANIDIRECTION::LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			Player->setMoveDirection(MOVEDIRECTION::RIGHT);
			Player->setAniDirection(ANIDIRECTION::RIGHT);
		}
		Player->startAni();

	}
}

void state_Idle::skillUse(int index, string skillName, player * Player)
{
	STATE tempState;
	if (index == 0)
	{
		tempState = STATE::SKILL_ONE;
	}
	else if (index == 2)
	{
		tempState = STATE::SKILL_THREE;
	}
	else if (index == 3)
	{
		tempState = STATE::SKILL_FOUR;
	}
	if (skillName == "FlameStrike" || skillName == "stoneShot" && Player->getState() == STATE::IDLE)
	{
		if (!Player->getArrCurSkills(index)->getIsSkill())
		{

			Player->setUsingSkillName(Player->getArrCurSkills(index)->getName());

			Player->getArrCurSkills(index)->skillPosSet(Player);
			Player->getSkillUI()->UseIdxSkill(index);
			Player->getArrCurSkills(index)->setIsSkill(true);

			if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
				(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::RIGHT);
				Player->startAni();
			}
			if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
				Player->getPlayerAngle() * (180 / PI) < 225))
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::LEFT);
				Player->startAni();
			}
			if (Player->getPlayerAngle()* (180 / PI) > 45 &&
				Player->getPlayerAngle() * (180 / PI) <= 135)
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::BACK);
				Player->startAni();
			}
			if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
				Player->getPlayerAngle() * (180 / PI) < 315)
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::FRONT);
				Player->startAni();
			}
			if (Player->getArrCurSkills(index)->getName() == "FlameStrike")
			{
				Player->getArrCurSkills(index)->setReLoadCount(Player->getArrCurSkills(index)->getReLoadCount() + 1);
			}
		}
	}
	else if (Player->getArrCurSkills(index)->getName() == "shockNova")
	{
		if (!Player->getArrCurSkills(index)->getIsSkill())
		{
			Player->getArrCurSkills(index)->setIsSkill(true);
			Player->getArrCurSkills(index)->skillPosSet(Player);
			Player->getArrCurSkills(index)->setReLoadCount(0);
			Player->getSkillUI()->UseIdxSkill(index);
			Player->setUsingSkillName(Player->getArrCurSkills(index)->getName());
			if (Player->getPlayerAngle() * (180 / PI) > 45 &&
				Player->getPlayerAngle() * (180 / PI) < 135)
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::BACK);
				Player->startAni();
			}
			else
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::FRONT);
				Player->startAni();
			}
		}
	}
	else if (Player->getArrCurSkills(index)->getName() == "thunderingChain")
	{
		if (!Player->getArrCurSkills(index)->getIsSkill())
		{
			Player->setUsingSkillName(Player->getArrCurSkills(index)->getName());
			if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
				(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::RIGHT);
				Player->startAni();
			}
			if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
				Player->getPlayerAngle() * (180 / PI) < 225))
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::LEFT);
				Player->startAni();
			}
			if (Player->getPlayerAngle()* (180 / PI) > 45 &&
				Player->getPlayerAngle() * (180 / PI) <= 135)
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::BACK);
				Player->startAni();
			}
			if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
				Player->getPlayerAngle() * (180 / PI) < 315)
			{
				Player->setState(tempState);
				Player->currentPlayerState();
				Player->setAniDirection(ANIDIRECTION::FRONT);
				Player->startAni();
			}

			Player->getArrCurSkills(index)->skillPosSet(Player);
			Player->getSkillUI()->UseIdxSkill(index);
			Player->getArrCurSkills(index)->setReLoadCount(0);
			Player->getArrCurSkills(index)->setIsSkill(true);
		}
	}
}
