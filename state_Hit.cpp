#include "stdafx.h"
#include "state_Hit.h"


state_Hit::state_Hit()
{
}


state_Hit::~state_Hit()
{
}

void state_Hit::onButtonW(player* Player)
{
}

void state_Hit::onButtonS(player* Player)
{
}

void state_Hit::onButtonA(player* Player)
{
}

void state_Hit::onButtonD(player* Player)
{
}

void state_Hit::offButtonW(player * Player)
{
}

void state_Hit::offButtonS(player * Player)
{
}

void state_Hit::offButtonA(player * Player)
{
}

void state_Hit::offButtonD(player * Player)
{
}

void state_Hit::onButtonQ(player* Player)
{
}

void state_Hit::onButtonE(player* Player)
{
}

void state_Hit::onButtonR(player* Player)
{
}

void state_Hit::onButtonSpace(player* Player)
{
}
void state_Hit::onButtonLB(player* Player)
{
}

void state_Hit::onButtonRB(player* Player)
{
}

void state_Hit::update(player* Player)
{
	if (Player->getAniDirection() == ANIDIRECTION::LEFT)
	{
		Player->setVecX(1);
	}
	else if (Player->getAniDirection() == ANIDIRECTION::RIGHT)
	{
		Player->setVecX(-1);
	}
	else if (Player->getAniDirection() == ANIDIRECTION::FRONT)
	{
		Player->setVecY(-1);
	}
	else if (Player->getAniDirection() == ANIDIRECTION::BACK)
	{
		Player->setVecY(1);
	}
}
