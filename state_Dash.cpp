#include "stdafx.h"
#include "state_Dash.h"


state_Dash::state_Dash()
{
}


state_Dash::~state_Dash()
{
}

void state_Dash::onButtonW(player* Player)
{
}

void state_Dash::onButtonS(player* Player)
{
}

void state_Dash::onButtonA(player* Player)
{
}

void state_Dash::onButtonD(player* Player)
{
}

void state_Dash::offButtonW(player * Player)
{
}

void state_Dash::offButtonS(player * Player)
{
}

void state_Dash::offButtonA(player * Player)
{
}

void state_Dash::offButtonD(player * Player)
{
}

void state_Dash::onButtonQ(player* Player)
{
}

void state_Dash::onButtonE(player* Player)
{
}

void state_Dash::onButtonR(player* Player)
{
}

void state_Dash::onButtonSpace(player* Player)
{
}

void state_Dash::onButtonLB(player* Player)
{
}

void state_Dash::onButtonRB(player* Player)
{
}

void state_Dash::update(player* Player)
{
		POINTFLOAT vec;
		switch (Player->getMoveDirection())
		{
		case MOVEDIRECTION::TOP:
			vec.y = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime() *  3.0f);
			vec.x = 0;
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::BOTTOM:
			vec.x = 0;
			vec.y = Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f;
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::LEFT:
			vec.x = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f);
			vec.y = 0;
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::RIGHT:
			vec.x = Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f;
			vec.y = 0;
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::LEFT_TOP:
			vec.x = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f);
			vec.y = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f);
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::LEFT_BOTTOM:
			vec.x = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f);
			vec.y = Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f;
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::RIGHT_TOP:
			vec.x =  Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f;
			vec.y = -(Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f);
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		case MOVEDIRECTION::RIGHT_BOTTOM:
			vec.x = Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f;
			vec.y = Player->getSpeed() * TIMEMANAGER->getElapsedTime() * 3.0f;
			Player->setVecX(vec.x);
			Player->setVecY(vec.y);
			break;
		}
}
