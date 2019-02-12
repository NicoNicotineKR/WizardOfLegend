#include "stdafx.h"
#include "player.h"
#include "enemy_Knight.h"
#include "enemy_State_Idle.h"
#include "enemy_State_Spawn.h"
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
	_pos.x =  _img->getFrameWidth();
	_pos.y =  _img->getFrameHeight();

	_vec.x = 0;
	_vec.y = 0;

	_aniDirection = E_ANIDIRECTION::RIGHT;
	_state = E_STATE::IDLE;

	_isAniOnce = false;
	_isClose = true;

	_curCharge = 0.f;
	_maxCharge = 0.5f;

	return S_OK;
}

void enemy_Knight::release()
{
}

void enemy_Knight::update()
{
	_vec.x = 0;
	_vec.y = 0;

	_enemyState->update(this);

	//플레이어가 사정거리 or 구역에 들어오면 그곳에 있는 적들의 _isClose를 트루로 바꿔줘야함 -> 한번 트루되면 계속 트루인상태로 고정임
	move();

	_playerPos = _player->getPos();

	_pos.x += _vec.x;
	_pos.y += _vec.y;
}

void enemy_Knight::render()
{
	_img->aniRender(getMemDC(), _pos.x, _pos.y, _ani);
}

void enemy_Knight::enemyKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("knight", "images/enemy/knight.bmp", 1032, 2016, 6, 8, true, 0xff00ff);

	//idle
	int rightIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_RightIdle", "knight", rightIdle, 1, 1, true);
	int leftIdle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_LeftIdle", "knight", leftIdle, 1, 1, true);

	//spawn -> 추후에 추가할것.

	//move
	int rightMove[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightMove", "knight", rightMove, 6, 5, true);
	int leftMove[] = { 17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftMove", "knight", leftMove, 6, 5, true);

	//charge
	int rightCharge[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightCharge", "knight", rightCharge, 1, 5, true);
	int leftCharge[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftCharge", "knight", leftCharge, 1, 5, true);

	//attack
	int rightAttack[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightAttack", "knight", rightAttack, 1, 1, false, knight_Move, this);
	int leftAttack[] = { 20 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_leftAttack", "knight", leftAttack, 1, 1, false, knight_Move, this);

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
	if (_isAniOnce)
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
		_isAniOnce = false;
	}
}

void enemy_Knight::move()
{
	//잠에서 깨어나면 
	if (_isClose)
	{
		if (_aniDirection == E_ANIDIRECTION::LEFT)
		{
			_enemyState->direction_Left(this);
		}
		else if (_aniDirection == E_ANIDIRECTION::RIGHT)
		{
			_enemyState->direction_right(this);
		}
	}
}

void enemy_Knight::knight_Move(void * obj)
{
	enemy_Knight* knight = (enemy_Knight*)obj;

	knight->setState(E_STATE::MOVE);
	knight->fixDirection();
	knight->currentEnemyState();
	knight->setIsAniOnce(true);
	knight->startAni();
}

void enemy_Knight::knight_rightAttack(void * obj)
{
	enemy_Knight* knight = (enemy_Knight*)obj;
	knight->setState(E_STATE::ATTACK);
	knight->currentEnemyState();
	knight->setIsAniOnce(true);
	knight->startAni();
}

void enemy_Knight::knight_leftAttack(void * obj)
{
	enemy_Knight* knight = (enemy_Knight*)obj;
	knight->setState(E_STATE::ATTACK);
	knight->currentEnemyState();
	knight->setIsAniOnce(true);
	knight->startAni();
}
