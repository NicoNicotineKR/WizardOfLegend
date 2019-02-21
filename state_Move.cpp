#include "stdafx.h"
#include "state_Move.h"


state_Move::state_Move()
{
}


state_Move::~state_Move()
{
}

void state_Move::onButtonW(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		Player->setMoveDirection(MOVEDIRECTION::RIGHT_TOP);
		if (Player->getAniDirection() != ANIDIRECTION::RIGHT)
		{
			Player->setAniDirection(ANIDIRECTION::RIGHT);
			Player->startAni();
		}
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		Player->setMoveDirection(MOVEDIRECTION::LEFT_TOP);
		if (Player->getAniDirection() != ANIDIRECTION::LEFT)
		{
			Player->setAniDirection(ANIDIRECTION::LEFT);
			Player->startAni();
		}
	}
	else if (!KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isStayKeyDown('D'))
	{
		if (Player->getMoveDirection() != MOVEDIRECTION::TOP)
		{
			Player->setMoveDirection(MOVEDIRECTION::TOP);
			Player->setAniDirection(ANIDIRECTION::BACK);
			Player->startAni();
		}
	}

}

void state_Move::onButtonS(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		Player->setMoveDirection(MOVEDIRECTION::RIGHT_BOTTOM);
		if (Player->getAniDirection() != ANIDIRECTION::RIGHT)
		{
			Player->setAniDirection(ANIDIRECTION::RIGHT);
			Player->startAni();
		}
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		Player->setMoveDirection(MOVEDIRECTION::LEFT_BOTTOM);
		if (Player->getAniDirection() != ANIDIRECTION::LEFT)
		{
			Player->setAniDirection(ANIDIRECTION::LEFT);
			Player->startAni();
		}
	}
	else if (!KEYMANAGER->isStayKeyDown('A') && !KEYMANAGER->isStayKeyDown('D'))
	{
		if (Player->getMoveDirection() != MOVEDIRECTION::BOTTOM)
		{
			Player->setMoveDirection(MOVEDIRECTION::BOTTOM);
			Player->setAniDirection(ANIDIRECTION::FRONT);
			Player->startAni();
		}
	}
}

void state_Move::onButtonA(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		Player->setMoveDirection(MOVEDIRECTION::LEFT_TOP);

		Player->setAniDirection(ANIDIRECTION::LEFT);
		Player->startAni();

	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		Player->setMoveDirection(MOVEDIRECTION::LEFT_BOTTOM);
		Player->setAniDirection(ANIDIRECTION::LEFT);
		Player->startAni();
	}
	else if (Player->getMoveDirection() != MOVEDIRECTION::LEFT)
	{
		Player->setMoveDirection(MOVEDIRECTION::LEFT);
		Player->setAniDirection(ANIDIRECTION::LEFT);
		Player->startAni();
	}

}

void state_Move::onButtonD(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		Player->setMoveDirection(MOVEDIRECTION::RIGHT_TOP);
		Player->setAniDirection(ANIDIRECTION::RIGHT);
		Player->startAni();

	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		Player->setMoveDirection(MOVEDIRECTION::RIGHT_BOTTOM);
		Player->setAniDirection(ANIDIRECTION::RIGHT);
		Player->startAni();
	}
	else if (Player->getMoveDirection() != MOVEDIRECTION::RIGHT)
	{
		Player->setMoveDirection(MOVEDIRECTION::RIGHT);
		Player->setAniDirection(ANIDIRECTION::RIGHT);
		Player->startAni();
	}

}

void state_Move::offButtonW(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (Player->getAniDirection() == ANIDIRECTION::LEFT)
		{
			Player->setMoveDirection(MOVEDIRECTION::LEFT);
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (Player->getAniDirection() == ANIDIRECTION::RIGHT)
		{
			Player->setMoveDirection(MOVEDIRECTION::RIGHT);
		}
	}
}

void state_Move::offButtonS(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (Player->getAniDirection() == ANIDIRECTION::LEFT)
		{
			Player->setMoveDirection(MOVEDIRECTION::LEFT);
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (Player->getAniDirection() == ANIDIRECTION::RIGHT)
		{
			Player->setMoveDirection(MOVEDIRECTION::RIGHT);
		}
	}
}

void state_Move::offButtonA(player* Player)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//if (Player->getAniDirection() == ANIDIRECTION::LEFT)
		//{
		//	Player->setMoveDirection(MOVEDIRECTION::LEFT);
		//}
		Player->setMoveDirection(MOVEDIRECTION::TOP);
		Player->setAniDirection(ANIDIRECTION::BACK);
		Player->startAni();
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//if (Player->getAniDirection() == ANIDIRECTION::LEFT)
		//{
		//	Player->setMoveDirection(MOVEDIRECTION::LEFT);
		//}
		Player->setMoveDirection(MOVEDIRECTION::BOTTOM);
		Player->setAniDirection(ANIDIRECTION::FRONT);
		Player->startAni();
	}
}

void state_Move::offButtonD(player * Player)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//if (Player->getAniDirection() == ANIDIRECTION::RIGHT)
		//{
		//	Player->setMoveDirection(MOVEDIRECTION::RIGHT);
		//}
		Player->setMoveDirection(MOVEDIRECTION::TOP);
		Player->setAniDirection(ANIDIRECTION::BACK);
		Player->startAni();
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//if (Player->getAniDirection() == ANIDIRECTION::FRONT)
		//{
			Player->setMoveDirection(MOVEDIRECTION::BOTTOM);
			Player->setAniDirection(ANIDIRECTION::FRONT);
			Player->startAni();
		//}
	}
}

void state_Move::onButtonQ(player* Player)
{
	skillUse(3, Player->getCurSkills1()->getName(), Player);
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

void state_Move::onButtonE(player* Player)
{
}

void state_Move::onButtonR(player* Player)
{
}

void state_Move::onButtonSpace(player* Player)
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


void state_Move::onButtonLB(player* Player)
{
	skillUse(0, Player->getCurSkills1()->getName(), Player);
}

void state_Move::onButtonRB(player* Player)
{
	skillUse(2, Player->getCurSkills1()->getName(), Player);
	//if (Player->getCurSkills3()->getName() == "shockNova")
	//{
	//	if (!Player->getCurSkills3()->getIsSkill())
	//	{
	//		Player->getCurSkills3()->setIsSkill(true);
	//		Player->getCurSkills3()->skillPosSet(Player);
	//		Player->getCurSkills3()->setReLoadCount(0);
	//		Player->getSkillUI()->UseIdxSkill(2);
	//		Player->setUsingSkillName(Player->getCurSkills3()->getName());
	//		if (Player->getPlayerAngle() * (180 / PI) > 45 &&
	//			Player->getPlayerAngle() * (180 / PI) < 135)
	//		{
	//			Player->setState(STATE::SKILL_THREE);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::BACK);
	//			Player->startAni();
	//		}
	//		else
	//		{
	//			Player->setState(STATE::SKILL_THREE);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::FRONT);
	//			Player->startAni();
	//		}
	//	}
	//}
	//else if (Player->getCurSkills3()->getName() == "thunderingChain")
	//{
	//	if (!Player->getCurSkills3()->getIsSkill())
	//	{
	//		Player->setUsingSkillName(Player->getCurSkills3()->getName());
	//		if ((Player->getPlayerAngle()* (180 / PI) <= 45 && Player->getPlayerAngle() * (180 / PI) >= 0) ||
	//			(Player->getPlayerAngle()*(180 / PI) <= 360 && Player->getPlayerAngle() * (180 / PI) >= 315))
	//		{
	//			Player->setState(STATE::SKILL_THREE);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::RIGHT);
	//			Player->startAni();
	//		}
	//		if ((Player->getPlayerAngle()* (180 / PI) > 135 &&
	//			Player->getPlayerAngle() * (180 / PI) < 225))
	//		{
	//			Player->setState(STATE::SKILL_THREE);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::LEFT);
	//			Player->startAni();
	//		}
	//		if (Player->getPlayerAngle()* (180 / PI) > 45 &&
	//			Player->getPlayerAngle() * (180 / PI) <= 135)
	//		{
	//			Player->setState(STATE::SKILL_THREE);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::BACK);
	//			Player->startAni();
	//		}
	//		if (Player->getPlayerAngle()* (180 / PI) >= 225 &&
	//			Player->getPlayerAngle() * (180 / PI) < 315)
	//		{
	//			Player->setState(STATE::SKILL_THREE);
	//			Player->currentPlayerState();
	//			Player->setAniDirection(ANIDIRECTION::FRONT);
	//			Player->startAni();
	//		}
	//
	//		Player->getCurSkills3()->skillPosSet(Player);
	//		Player->getSkillUI()->UseIdxSkill(2);
	//		Player->getCurSkills3()->setReLoadCount(0);
	//		Player->getCurSkills3()->setIsSkill(true);
	//	}
	//}
}

void state_Move::update(player* Player)
{
	if (!KEYMANAGER->isStayKeyDown('W') &&
		!KEYMANAGER->isStayKeyDown('S') &&
		!KEYMANAGER->isStayKeyDown('A') &&
		!KEYMANAGER->isStayKeyDown('D'))
	{
		Player->setState(STATE::IDLE);
		Player->currentPlayerState();
		Player->startAni();
	}
	else if (KEYMANAGER->isStayKeyDown('W') ||
		KEYMANAGER->isStayKeyDown('S') ||
		KEYMANAGER->isStayKeyDown('A') ||
		KEYMANAGER->isStayKeyDown('D'))
	{
		//Player->setState(STATE::MOVE);
		//Player->currentPlayerState();

		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::LEFT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::LEFT_TOP);
			Player->setAniDirection(ANIDIRECTION::LEFT);

		}
		else if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::RIGHT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::RIGHT_TOP);
			Player->setAniDirection(ANIDIRECTION::RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::LEFT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::LEFT_BOTTOM);
			Player->setAniDirection(ANIDIRECTION::LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::RIGHT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::RIGHT_BOTTOM);
			Player->setAniDirection(ANIDIRECTION::RIGHT);
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::BACK)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::TOP);
			Player->setAniDirection(ANIDIRECTION::BACK);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::FRONT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::BOTTOM);
			Player->setAniDirection(ANIDIRECTION::FRONT);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::LEFT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::LEFT);
			Player->setAniDirection(ANIDIRECTION::LEFT);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (Player->getAniDirection() != ANIDIRECTION::RIGHT)
			{
				Player->setIsPlayerAniOnce(true);
			}
			Player->setMoveDirection(MOVEDIRECTION::RIGHT);
			Player->setAniDirection(ANIDIRECTION::RIGHT);
		}
		if (Player->getIsPlayerAniOnce())
		{
			Player->setIsPlayerAniOnce(false);
			Player->startAni();
		}
	}
	switch (Player->getMoveDirection())
	{
	case MOVEDIRECTION::TOP:
		Player->setVecX(0);
		Player->setVecY(-Player->getSpeed()* TIMEMANAGER->getElapsedTime());
		break;
	case MOVEDIRECTION::BOTTOM:
		//vec.x = 0;
		//vec.y =;
		Player->setVecX(0);
		Player->setVecY(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		break;
	case MOVEDIRECTION::LEFT:
		//vec.x = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		//vec.y = 0;
		Player->setVecX(-Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecY(0);
		break;
	case MOVEDIRECTION::RIGHT:
		//vec.x = Player->getSpeed() * TIMEMANAGER->getElapsedTime();
		//vec.y = 0;
		Player->setVecX(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecY(0);
		break;
	case MOVEDIRECTION::LEFT_TOP:
		//vec.x = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		//vec.y = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecX(-Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecY(-Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		break;
	case MOVEDIRECTION::LEFT_BOTTOM:
		//vec.x = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		//vec.y = Player->getSpeed() * TIMEMANAGER->getElapsedTime();
		Player->setVecX(-Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecY(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		break;
	case MOVEDIRECTION::RIGHT_TOP:
		//vec.x =  Player->getSpeed() * TIMEMANAGER->getElapsedTime();
		//vec.y = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecX(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecY(-Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		break;
	case MOVEDIRECTION::RIGHT_BOTTOM:
		//vec.x = Player->getSpeed() * TIMEMANAGER->getElapsedTime();
		//vec.y = Player->getSpeed() * TIMEMANAGER->getElapsedTime();
		Player->setVecX(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		Player->setVecY(Player->getSpeed() * TIMEMANAGER->getElapsedTime());
		break;
	}

}

void state_Move::skillUse(int index,string skillName, player* Player)
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
	if (skillName == "FlameStrike" || skillName == "stoneShot")
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
