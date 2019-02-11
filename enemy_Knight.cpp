#include "stdafx.h"
#include "enemy_Knight.h"
#include "enemy_State_Idle.h"
#include "enemy_State_Spawn.h"
#include "enemy_State_MoveStart.h"
#include "enemy_State_Move.h"
#include "enemy_State_Charge.h"
#include "enemy_State_Attack.h"
#include "enemy_State_Death.h"


enemy_Knight::enemy_Knight()
{
}


enemy_Knight::~enemy_Knight()
{
}

HRESULT enemy_Knight::init()
{
	enemyKeyAnimationInit();
	enemyArrStateInit();

	_img = IMAGEMANAGER->findImage("knight");
	//spawn이면 카드스폰0으로(0은 아무이미지 없게)
	_ani = KEYANIMANAGER->findAnimation("knight_LeftIdle");

	_maxHp = 100;
	_curHp = 100;

	_speed = 200.f;
	_pos.x = WINSIZEX - _img->getFrameWidth();
	_pos.y = WINSIZEY - _img->getFrameHeight();

	_vec.x = 0;
	_vec.y = 0;

	_aniDirection = E_ANIDIRECTION::LEFT;
	_moveDirection = E_MOVEDIRECTION::BOTTOM;
	_state = E_STATE::IDLE;

	_isAniOnce = false;


	return S_OK;
}

void enemy_Knight::release()
{
}

void enemy_Knight::update()
{
	_vec.x = 0;
	_vec.y = 0;

	KEYANIMANAGER->update();
	_enemyState->update(this);

	_pos.x += _vec.x;
	_pos.y += _vec.y;
}

void enemy_Knight::render()
{
}

void enemy_Knight::enemyKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("knight", "images/enemy/knight.bmp", 516, 1008, 6, 8, true, 0xff00ff);

	//idle
	int rightIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_RightIdle", "knight", rightIdle, 1, 1, true);
	int leftIdle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_LeftIdle", "knight", leftIdle, 1, 1, true);

	//spawn -> 추후에 추가할것.

	//move
	int rightMoveStart[] = { 7,8,6,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightMoveStart", "knight", rightMoveStart, 5, 5, false, knight_Moving, this);
	int rightMoving[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightMove", "knight", rightMoving, 6, 5, true);

	int leftMoveStart[] = { 16,15,17,14,13 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftMoveStart", "knight", leftMoveStart, 5, 5, false, knight_Moving, this);
	int leftMoving[] = { 17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftMove", "knight", leftMoving, 6, 5, true);

	//charge
	int rightCharge[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightCharge", "knight", rightCharge, 1, 1, true);
	int leftCharge[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftCharge", "knight", leftCharge, 1, 1, true);

	//attack
	int rightAttack[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightAttack", "knight", rightAttack, 1, 3, false, knight_Moving, this);
	int leftAttack[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftAttack", "knight", leftAttack, 1, 3, false, knight_Moving, this);

	//death
	int rightDeath[] = { 24,25,26,27,28,29,30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightDeath", "knight", rightDeath, 9, 5, false);
	int leftDeath[] = { 41,40,39,38,37,36,47,46,45 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftDeath", "knight", leftDeath, 9, 5, false);
}

void enemy_Knight::enemyArrStateInit()
{
	_arrState[static_cast<const int>(E_STATE::IDLE)] = new enemy_State_Idle;
	_arrState[static_cast<const int>(E_STATE::SPAWN)] = new enemy_State_Spawn;
	_arrState[static_cast<const int>(E_STATE::MOVESTART)] = new enemy_State_MoveStart;
	_arrState[static_cast<const int>(E_STATE::MOVE)] = new enemy_State_Move;
	_arrState[static_cast<const int>(E_STATE::CHARGE)] = new enemy_State_Charge;
	_arrState[static_cast<const int>(E_STATE::ATTACK)] = new enemy_State_Attack;
	_arrState[static_cast<const int>(E_STATE::DEATH)] = new enemy_State_Death;

	_enemyState = _arrState[static_cast<const int>(E_STATE::IDLE)];

	//구역 안에서 생성되는 놈이라 카드 스폰을 해줘야 하는놈이면 이프문.
	//필드에 있는 몹이면 그냥 IDLE상태로 대기.
}

void enemy_Knight::startAni()
{
	//idle
	if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::IDLE)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_rightIdle");
		_ani->start();
	}
	else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::IDLE)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_leftIdle");
		_ani->start();
	}

	//moveStart
	if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::MOVESTART)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_rightMoveStart");
		_ani->start();
	}
	else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::MOVESTART)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_leftMoveStart");
		_ani->start();
	}

	//move
	if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::MOVE)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_rightMove");
		_ani->start();
	}
	else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::MOVE)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_leftMove");
		_ani->start();
	}

	//charge
	if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::CHARGE)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_rightCharge");
		_ani->start();
	}
	else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::CHARGE)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_leftCharge");
		_ani->start();
	}

	//attack
	if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::ATTACK)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_rightAttack");
		_ani->start();
	}
	else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::ATTACK)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_leftAttack");
		_ani->start();
	}

	//death
	if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::DEATH)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_rightDeath");
		_ani->start();
	}
	else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::DEATH)
	{
		_ani = KEYANIMANAGER->findAnimation("knight_leftDeath");
		_ani->start();
	}
}

void enemy_Knight::knight_Moving(void * obj)
{
	//플레이어 x 좌표가 나보다 낮으면(왼쪽에있으면) 왼쪽이미지 <-> 나보다 크면 오른쪽이미지와 상태를 부여하자
}
