#include "stdafx.h"
#include "enemy_State_Idle.h"


enemy_State_Idle::enemy_State_Idle()
{
}


enemy_State_Idle::~enemy_State_Idle()
{
}

void enemy_State_Idle::direction_Left(enemy * enemy)
{
	enemy->setAniDirection(E_ANIDIRECTION::LEFT);
	enemy->setState(E_STATE::MOVESTART);
	enemy->currentEnemyState();
	enemy->startAni();
}

void enemy_State_Idle::direction_right(enemy * enemy)
{
	enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
	enemy->setState(E_STATE::MOVESTART);
	enemy->currentEnemyState();
	enemy->startAni();
}

void enemy_State_Idle::update(enemy * enemy)
{
}
