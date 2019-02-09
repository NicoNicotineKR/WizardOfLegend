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
}

void state_Idle::onButtonE(player* Player)
{
}

void state_Idle::onButtonR(player* Player)
{
}

void state_Idle::onButtonSpace(player* Player)
{
	Player->setState(STATE::DASH);
	Player->currentPlayerState();
	Player->startAni();
}

void state_Idle::onButtonLB(player* Player)
{
}

void state_Idle::onButtonRB(player* Player)
{
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
		Player->startAni();
	}
}
