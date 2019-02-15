#include "stdafx.h"
#include "enemy_Ghoul.h"
#include "player.h"
#include "enemy_Knight.h"
#include "enemy_State_Idle.h"
#include "enemy_State_Spawn.h"
#include "enemy_State_Move.h"
#include "enemy_State_Charge.h"
#include "enemy_State_Attack.h"
#include "enemy_State_Death.h"


enemy_Ghoul::enemy_Ghoul()
{
}


enemy_Ghoul::~enemy_Ghoul()
{
}

HRESULT enemy_Ghoul::init()
{
	enemyKeyAnimationInit();
	enemyArrStateInit();

	_img = IMAGEMANAGER->findImage("ghoul");
	//spawn이면 카드스폰0으로(0은 아무이미지 없게)
	_ani = KEYANIMANAGER->findAnimation("ghoul_LeftIdle");

	_maxHp = 100;
	_curHp = 100;

	_speed = 200.f;
	//기본 베이스 좌표(타일충돌)
	_pos.x = WINSIZEX / 2;// _img->getFrameWidth();
	_pos.y = WINSIZEY / 2;//_img->getFrameHeight();
	_rc = RectMakeCenter(_pos.x, _pos.y, 32, 32);

	//이미지 출력 좌표
	_imgPos.x = _pos.x;
	_imgPos.y = _pos.y - POS_Y_IMAGE_SHAVE;

	//충돌판정
	_collisionPos.x = _pos.x;
	_collisionPos.y = _pos.y - POS_Y_HIT_SHAVE;
	_collisionRc = RectMakeCenter(_collisionPos.x, _collisionPos.y, HIT_RC_WIDTH, HIT_RC_HEIGHT);

	//벡터값(이동용)
	_vec.x = 0;
	_vec.y = 0;

	_aniDirection = E_ANIDIRECTION::RIGHT;
	_state = E_STATE::IDLE;

	_isAniOnce = false;
	_isClose = true;

	_curCharge = 0.f;
	_maxCharge = 0.3f;

	_atkImg = IMAGEMANAGER->addFrameImage("slash2", "images/enemy/slash2.bmp", 2952, 82, 36, 1, true, 0xff00ff);
	_atkImg->SetFrameX(0);
	_atkImg->SetFrameY(0);




	return S_OK;
}

void enemy_Ghoul::release()
{
}

void enemy_Ghoul::update()
{
	_vec.x = 0;
	_vec.y = 0;

	_enemyState->update(this);

	//플레이어가 사정거리 or 구역에 들어오면 그곳에 있는 적들의 _isClose를 트루로 바꿔줘야함 -> 한번 트루되면 계속 트루인상태로 고정임
	move();

	_playerPos.x = _player->getTileCheckRcPos().x + TOP_TILESIZE / 2;
	_playerPos.y = _player->getTileCheckRcPos().y + TOP_TILESIZE / 2;

	//벡터값에 따른 베이스 좌표의 이동
	_pos.x += _vec.x;
	_pos.y += _vec.y;
	_rc = RectMakeCenter(_pos.x, _pos.y, 32, 32);

	//이미지 이동
	_imgPos.x = _pos.x;
	_imgPos.y = _pos.y - POS_Y_IMAGE_SHAVE;

	//히트판정이동
	_collisionPos.x = _pos.x;
	_collisionPos.y = _pos.y - POS_Y_HIT_SHAVE;
	_collisionRc = RectMakeCenter(_collisionPos.x, _collisionPos.y, HIT_RC_WIDTH, HIT_RC_HEIGHT);
}

void enemy_Ghoul::render()
{
	//에너미 히트판정 출력
	//Rectangle(getMemDC(),_collisionRc);

	//에너미 이미지 출력
	_img->aniRender(getMemDC(), _imgPos.x - (_img->getFrameWidth() / 2), _imgPos.y - (_img->getFrameHeight() / 2), _ani);

	//공격상태일때만 공격이미지 출력
	if (_enemyState == _arrState[static_cast<const int>(E_STATE::ATTACK)])
	{
		//	Rectangle(getMemDC(), _atkRc);
		_atkImg->frameRender(getMemDC(), _atkRc.left, _atkRc.top);
		char str[128];
		sprintf_s(str, "frameX : %d", _atkImg->getFrameX());
		TextOut(getMemDC(), 50, 200, str, strlen(str));
	}
	//플레이어 기준좌표 출력
	//Rectangle(getMemDC(), _playerPos.x, _playerPos.y, _playerPos.x + 10, _playerPos.y + 10);
	//
	////에너미 기준 좌표 출력(타일충돌)
	//Rectangle(getMemDC(), _rc);
	//
	//Rectangle(getMemDC(), _pos.x, _pos.y - 70, _pos.x + 10, _pos.y - 60);
	//Rectangle(getMemDC(), _playerPos.x, _playerPos.y - 50, _playerPos.x + 10, _playerPos.y - 40);
}

void enemy_Ghoul::enemyKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("ghoul", "images/enemy/ghoul.bmp", 1152, 1344, 6, 7, true, 0xff00ff);

	//idle
	int rightIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_RightIdle", "ghoul", rightIdle, 1, 1, true);
	int leftIdle[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_LeftIdle", "ghoul", leftIdle, 1, 1, true);

	//spawn -> 추후에 추가할것.

	//move
	int rightMove[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_rightMove", "ghoul", rightMove, 6, 5, true);
	int leftMove[] = { 17,16,15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_leftMove", "ghoul", leftMove, 6, 5, true);

	//charge
	int rightCharge[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_rightCharge", "ghoul", rightCharge, 1, 1, true);
	int leftCharge[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_leftCharge", "ghoul", leftCharge, 1, 1, true);

	//attack
	int rightAttack[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_rightAttack", "ghoul", rightAttack, 1, 2, false, ghoul_Move, this);
	int leftAttack[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_leftAttack", "ghoul", leftAttack, 1, 2, false, ghoul_Move, this);

	//death
	int rightDeath[] = { 18,19,20,21,22,23,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_rightDeath", "ghoul", rightDeath, 10, 5, false);
	int leftDeath[] = { 35,34,33,32,31,30,41,40,39,38 };
	KEYANIMANAGER->addArrayFrameAnimation("ghoul_leftDeath", "ghoul", leftDeath, 10, 5, false);
}

void enemy_Ghoul::enemyArrStateInit()
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

void enemy_Ghoul::startAni()
{
	if (_isAniOnce)
	{
		//idle
		if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::IDLE)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_rightIdle");
			_ani->start();
		}
		else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::IDLE)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_leftIdle");
			_ani->start();
		}

		//move
		if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::MOVE)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_rightMove");
			_ani->start();
		}
		else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::MOVE)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_leftMove");
			_ani->start();
		}

		//charge
		if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::CHARGE)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_rightCharge");
			_ani->start();
		}
		else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::CHARGE)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_leftCharge");
			_ani->start();
		}

		//attack
		if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::ATTACK)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_rightAttack");
			_ani->start();
		}
		else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::ATTACK)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_leftAttack");
			_ani->start();
		}

		//death
		if (_aniDirection == E_ANIDIRECTION::RIGHT && _state == E_STATE::DEATH)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_rightDeath");
			_ani->start();
		}
		else if (_aniDirection == E_ANIDIRECTION::LEFT && _state == E_STATE::DEATH)
		{
			_ani = KEYANIMANAGER->findAnimation("ghoul_leftDeath");
			_ani->start();
		}
		_isAniOnce = false;
	}
}

void enemy_Ghoul::move()
{
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

void enemy_Ghoul::ghoul_Move(void * obj)
{
	enemy_Ghoul* ghoul = (enemy_Ghoul*)obj;

	ghoul->setState(E_STATE::MOVE);
	ghoul->fixDirection();
	ghoul->currentEnemyState();
	ghoul->setIsAniOnce(true);
	ghoul->startAni();
	ghoul->setAtkRc();
}