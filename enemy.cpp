#include "stdafx.h"
#include "enemy.h"
#include "player.h"
#include "enemy_State_Idle.h"
#include "enemy_State_Spawn.h"
#include "enemy_State_Move.h"
#include "enemy_State_Charge.h"
#include "enemy_State_Attack.h"
#include "enemy_State_Hit.h"
#include "enemy_State_Death.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

void enemy::CamRender()
{
}

void enemy::enemyKeyAnimationInit()
{
}

void enemy::enemyArrStateInit()
{
}

void enemy::startAni()
{
}

void enemy::fixDirection()
{
	if (_pos.x < _playerPos.x)
	{
		_aniDirection = E_ANIDIRECTION::RIGHT;
	}
	if (_pos.x >= _playerPos.x)
	{
		_aniDirection = E_ANIDIRECTION::LEFT;
	}
}

void enemy::moveDirection()
{
	if (_pos.x < _listPath.front().x)
	{
		_aniDirection = E_ANIDIRECTION::RIGHT;
	}
	if (_pos.x >= _listPath.front().x)
	{
		_aniDirection = E_ANIDIRECTION::LEFT;
	}
}

void enemy::currentEnemyState()
{
	switch (_state)
	{
		case E_STATE::IDLE:
			_enemyState = _arrState[static_cast<const int>(E_STATE::IDLE)];
		break;
		case E_STATE::SPAWN:
			_enemyState = _arrState[static_cast<const int>(E_STATE::SPAWN)];
		break;
		case E_STATE::MOVE:
			_enemyState = _arrState[static_cast<const int>(E_STATE::MOVE)];
		break;
		case E_STATE::CHARGE:
			_enemyState = _arrState[static_cast<const int>(E_STATE::CHARGE)];
		break;
		case E_STATE::ATTACK:
			_enemyState = _arrState[static_cast<const int>(E_STATE::ATTACK)];
		break;
		case E_STATE::HIT:
			_enemyState = _arrState[static_cast<const int>(E_STATE::HIT)];
		break;
		case E_STATE::DEATH:
			_enemyState = _arrState[static_cast<const int>(E_STATE::DEATH)];
		break;
	}
}

void enemy::move()
{
}
