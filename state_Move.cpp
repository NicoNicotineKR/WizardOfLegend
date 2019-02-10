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
}

void state_Move::onButtonE(player* Player)
{
}

void state_Move::onButtonR(player* Player)
{
}

void state_Move::onButtonSpace(player* Player)
{
	Player->setState(STATE::DASH);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Move::onButtonLB(player* Player)
{
}

void state_Move::onButtonRB(player* Player)
{
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
