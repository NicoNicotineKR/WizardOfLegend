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
	if (!Player->getCurSkills4()->getIsSkill())
	{
		Player->getCurSkills4()->setIsSkill(true);
		Player->getCurSkills4()->skillPosSet(Player);
		Player->getCurSkills4()->setReLoadCount(0);
		Player->getSkillUI()->UseIdxSkill(3);
		Player->setUsingSkillName(Player->getCurSkills4()->getName());
		if (Player->getPlayerAngle() * (180 / PI) > 45 &&
			Player->getPlayerAngle() * (180 / PI) < 135)
		{
			Player->setState(STATE::SKILL_FOUR);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::BACK);
			Player->startAni();
		}
		else
		{
			Player->setState(STATE::SKILL_FOUR);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::FRONT);
			Player->startAni();
		}


		//Player->setState(STATE::SKILL_FOUR);
		//Player->currentPlayerState();
		//
		//Player->startAni();
	}

}

void state_Idle::onButtonE(player* Player)
{

}

void state_Idle::onButtonR(player* Player)
{

}

void state_Idle::onButtonSpace(player* Player)
{
	if (!Player->getCurSkills3()->getIsSkill())
	{
		Player->getCurSkills3()->setIsSkill(true);
		Player->getCurSkills3()->skillPosSet(Player);
		Player->getCurSkills3()->setReLoadCount(0);
		Player->getSkillUI()->UseIdxSkill(2);
	}
	Player->setState(STATE::DASH);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Idle::onButtonLB(player* Player)
{
	if (!Player->getCurSkills1()->getIsSkill())
	{

		Player->setUsingSkillName(Player->getCurSkills1()->getName());
		Player->getCurSkills1()->skillPosSet(Player);
		Player->getSkillUI()->UseIdxSkill(0);
		Player->getCurSkills1()->setIsSkill(true);

		if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
			(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
		{
			Player->setState(STATE::SKILL_ONE);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::RIGHT);
			Player->startAni();
		}
		if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
			Player->getPlayerAngle() * (180 / PI) < 225))
		{
			Player->setState(STATE::SKILL_ONE);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::LEFT);
			Player->startAni();
		}
		if (Player->getPlayerAngle()* (180 / PI) > 45 &&
			Player->getPlayerAngle() * (180 / PI) <= 135)
		{
			Player->setState(STATE::SKILL_ONE);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::BACK);
			Player->startAni();
		}
		if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
			Player->getPlayerAngle() * (180 / PI) < 315)
		{
			Player->setState(STATE::SKILL_ONE);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::FRONT);
			Player->startAni();
		}
		if (Player->getCurSkills1()->getName() == "FlameStrike")
		{
			Player->getCurSkills1()->setReLoadCount(Player->getCurSkills1()->getReLoadCount() + 1);
		}
	}
}

void state_Idle::onButtonRB(player* Player)
{
	if (!Player->getCurSkills2()->getIsSkill())
	{

		Player->setUsingSkillName(Player->getCurSkills2()->getName());
		if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
			(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
		{
			Player->setState(STATE::SKILL_TWO);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::RIGHT);
			Player->startAni();
		}
		if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
			Player->getPlayerAngle() * (180 / PI) < 225))
		{
			Player->setState(STATE::SKILL_TWO);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::LEFT);
			Player->startAni();
		}
		if (Player->getPlayerAngle()* (180 / PI) > 45 &&
			Player->getPlayerAngle() * (180 / PI) <= 135)
		{
			Player->setState(STATE::SKILL_TWO);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::BACK);
			Player->startAni();
		}
		if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
			Player->getPlayerAngle() * (180 / PI) < 315)
		{
			Player->setState(STATE::SKILL_TWO);
			Player->currentPlayerState();
			Player->setAniDirection(ANIDIRECTION::FRONT);
			Player->startAni();
		}

		Player->getCurSkills2()->skillPosSet(Player);
		Player->getSkillUI()->UseIdxSkill(1);
		Player->getCurSkills2()->setReLoadCount(0);
		Player->getCurSkills2()->setIsSkill(true);
	}
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
