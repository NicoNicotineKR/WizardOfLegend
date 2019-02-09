#include "stdafx.h"
#include "player.h"
#include "state_Move.h"
#include "state_Idle.h"
#include "state_Dash.h"
#include "state_Skill_One.h"
#include "state_Skill_Two.h"
#include "state_Skill_Three.h"
#include "state_Skill_Four.h"
#include "state_Skill_Five.h"
#include "state_Hit.h"
#include "state_Dead.h"

player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	playerKeyAnimationInit();
	arrStateInit();
	_img = IMAGEMANAGER->findImage("player");
	_ani = KEYANIMANAGER->findAnimation("frontIdle");

	//_collisionRc = RectMake(WINSIZEX/2,WINSIZEY/2,30,30);			

	_maxHp = 500;					
	_curHp = 500;					

	_speed = 300.0f;					
	//_angle = ;					
	_pos.x = WINSIZEX/2;
	_pos.y = WINSIZEY / 2;

	_vec.x = 0;
	_vec.y = 0;

	_aniDirection = ANIDIRECTION::FRONT;		
	_moveDirection = MOVEDIRECTION::BOTTOM;
	_state = STATE::IDLE;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	KEYANIMANAGER->update();
	_playerState->update(this);
	inPutKey();
	playerMove();
	_pos.x += _vec.x;
	_pos.y += _vec.y;
}

void player::render(HDC hdc)
{
	_img->aniRender(hdc, _pos.x, _pos.y, _ani);
	char str[128];
	sprintf_s(str, "%d : state", _state, strlen(str));
	TextOut(hdc, 50, 50, str, strlen(str));
}

void player::playerKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("player", "images/player/player.bmp", 1700, 1530, 10, 9, true, RGB(255, 0, 255));

	int frontIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("frontIdle", "player", frontIdle, 1, 10, false);

	int backIdle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("backIdle", "player", backIdle, 1, 10, false);

	int rightIdle[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("rightIdle", "player", rightIdle, 1, 10, false);

	int leftIdle[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("leftIdle", "player", leftIdle, 1, 10, false);

	int frontMove[] = { 10,11,12,13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("frontMove", "player", frontMove, 10, 10, true);

	int backMove[] = { 20,21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("backMove", "player", backMove, 10, 10, true);

	int rightMove[] = { 30,31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("rightMove", "player", rightMove, 10, 10, true);

	int leftMove[] = { 49,48,47,46,45,44,43,42,41,40 };
	KEYANIMANAGER->addArrayFrameAnimation("leftMove", "player", leftMove, 10, 10, true);

	int frontDash[] = { 10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("frontDash", "player", frontDash, 5, 10, false, playerIdle,this);

	int backDash[] = { 20,21,22,23,24,25 };
	KEYANIMANAGER->addArrayFrameAnimation("backDash", "player", backDash, 5, 10, false, playerIdle, this);

	int rightDash[] = { 70,71,72,73,74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("rightDash", "player", rightDash, 8, 10, false, playerIdle, this);

	int leftDash[] = { 87,86,85,84,83,82,81,80 };
	KEYANIMANAGER->addArrayFrameAnimation("leftDash", "player", leftDash, 8, 10, false, playerIdle, this);

}

void player::inPutKey()
{
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_playerState->onButtonW(this);
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_playerState->onButtonS(this);
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_playerState->onButtonD(this);
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_playerState->onButtonA(this);
	}

	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_playerState->offButtonW(this);
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_playerState->offButtonS(this);
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_playerState->offButtonD(this);
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_playerState->offButtonA(this);
	}



	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_playerState->onButtonSpace(this);
	}
}

void player::startAni()
{
	//MOVE 애니메이션
	if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::MOVE)
	{
		_ani = KEYANIMANAGER->findAnimation("rightMove");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::MOVE)
	{
		_ani = KEYANIMANAGER->findAnimation("leftMove");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::MOVE)
	{
		_ani = KEYANIMANAGER->findAnimation("backMove");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::MOVE)
	{
		_ani = KEYANIMANAGER->findAnimation("frontMove");
		_ani->start();
	}

	//IDLE 애니메이션
	if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::IDLE)
	{
		_ani = KEYANIMANAGER->findAnimation("rightIdle");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::IDLE)
	{
		_ani = KEYANIMANAGER->findAnimation("leftIdle");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::IDLE)
	{
		_ani = KEYANIMANAGER->findAnimation("backIdle");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::IDLE)
	{
		_ani = KEYANIMANAGER->findAnimation("frontIdle");
		_ani->start();
	}
	
	//DASH 애니메이션
	if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::DASH)
	{
		_ani = KEYANIMANAGER->findAnimation("rightDash");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::DASH)
	{
		_ani = KEYANIMANAGER->findAnimation("leftDash");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::DASH)
	{
		_ani = KEYANIMANAGER->findAnimation("backDash");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::DASH)
	{
		_ani = KEYANIMANAGER->findAnimation("frontDash");
		_ani->start();
	}
}

void player::arrStateInit()
{
	_arrState[static_cast<const int>(STATE::IDLE)] = new state_Idle();
	_arrState[static_cast<const int>(STATE::MOVE)] = new state_Move();
	_arrState[static_cast<const int>(STATE::DASH)] = new state_Dash();
	_arrState[static_cast<const int>(STATE::SKILL_ONE)] = new state_Skill_One();
	_arrState[static_cast<const int>(STATE::SKILL_TWO)] = new state_Skill_Two();
	_arrState[static_cast<const int>(STATE::SKILL_THREE)] = new state_Skill_Three();
	_arrState[static_cast<const int>(STATE::SKILL_FOUR)] = new state_Skill_Four();
	_arrState[static_cast<const int>(STATE::SKILL_FIVE)] = new state_Skill_Five();
	_arrState[static_cast<const int>(STATE::HIT)] = new state_Hit();
	_arrState[static_cast<const int>(STATE::DEAD)] = new state_Dead();

	_playerState = _arrState[static_cast<const int>(STATE::IDLE)];

}

void player::currentPlayerState()
{
	switch (_state)
	{
	case STATE::IDLE:
		_playerState = _arrState[static_cast<const int>(STATE::IDLE)];
		break;
	case STATE::MOVE:
		_playerState = _arrState[static_cast<const int>(STATE::MOVE)];
		break;
	case STATE::DASH:
		_playerState = _arrState[static_cast<const int>(STATE::DASH)];
		break;
	case STATE::SKILL_ONE:
		_playerState = _arrState[static_cast<const int>(STATE::SKILL_ONE)];
		break;
	case STATE::SKILL_TWO:
		_playerState = _arrState[static_cast<const int>(STATE::SKILL_TWO)];
		break;
	case STATE::SKILL_THREE:
		_playerState = _arrState[static_cast<const int>(STATE::SKILL_THREE)];
		break;
	case STATE::SKILL_FOUR:
		_playerState = _arrState[static_cast<const int>(STATE::SKILL_FOUR)];
		break;
	case STATE::SKILL_FIVE:
		_playerState = _arrState[static_cast<const int>(STATE::SKILL_FIVE)];
		break;
	case STATE::HIT:
		_playerState = _arrState[static_cast<const int>(STATE::HIT)];
		break;
	case STATE::DEAD:
		_playerState = _arrState[static_cast<const int>(STATE::DEAD)];
		break;


	}
}

void player::playerMove()
{
	if (_state == STATE::IDLE)
	{
		_vec.x = 0;
		_vec.y = 0;
	}

	if (_state == STATE::MOVE)
	{
		switch (_moveDirection)
		{
		case MOVEDIRECTION::TOP:
			_vec.y = -_speed * TIMEMANAGER->getElapsedTime();
			_vec.x = 0;
			break;
		case MOVEDIRECTION::BOTTOM:
			_vec.y = _speed * TIMEMANAGER->getElapsedTime();
			_vec.x = 0;
			break;
		case MOVEDIRECTION::LEFT:
			_vec.x = -_speed * TIMEMANAGER->getElapsedTime();
			_vec.y = 0;
			break;
		case MOVEDIRECTION::RIGHT:
			_vec.x = _speed * TIMEMANAGER->getElapsedTime();
			_vec.y = 0;
			break;
		case MOVEDIRECTION::LEFT_TOP:
			_vec.x = -_speed * TIMEMANAGER->getElapsedTime();
			_vec.y = -_speed * TIMEMANAGER->getElapsedTime();
			break;
		case MOVEDIRECTION::LEFT_BOTTOM:
			_vec.x = -_speed * TIMEMANAGER->getElapsedTime();
			_vec.y = _speed * TIMEMANAGER->getElapsedTime();
			break;
		case MOVEDIRECTION::RIGHT_TOP:
			_vec.x = _speed * TIMEMANAGER->getElapsedTime();
			_vec.y = -_speed * TIMEMANAGER->getElapsedTime();
			break;
		case MOVEDIRECTION::RIGHT_BOTTOM:
			_vec.x = _speed * TIMEMANAGER->getElapsedTime();
			_vec.y = _speed * TIMEMANAGER->getElapsedTime();
			break;
		}
	}
}

void player::playerIdle(void * obj)
{
	player* Player = (player*)obj;

	Player->setState(STATE::IDLE);
	Player->currentPlayerState();
	Player->startAni();

}