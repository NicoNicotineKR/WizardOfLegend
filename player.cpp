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
#include "state_Fall.h"
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
	_playerCircleImg = IMAGEMANAGER->findImage("playerCircle");
	_playerCircleDirectionImg = IMAGEMANAGER->findImage("playerCircleDirection");
	//_collisionRc = RectMake(WINSIZEX/2,WINSIZEY/2,30,30);			
	_playerCircleDirectionAngle = -90 * (PI / 180);
	_playerCircleRadius = 50;
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

	_isPlayerAniOnce = false;

	_playerStatusUI = new playerStatusUI;
	_playerStatusUI->init();
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_vec.x = 0;
	_vec.y = 0;
	KEYANIMANAGER->update();
	_playerState->update(this);
	inPutKey();
	_playerStatusUI->update();

	_pos.x += _vec.x;
	_pos.y += _vec.y;

	_playerCirclePos.x = _pos.x + (_img->getFrameWidth() / 2) - (_playerCircleImg->GetWidth() / 2);
	_playerCirclePos.y = _pos.y + _img->getFrameHeight() - (_playerCircleImg->GetHeight() - 20);
	_playerCircleDirectionAngle = getAngle(_playerCirclePos.x, _playerCirclePos.y, _ptMouse.x, _ptMouse.y);
	playerCirclePosition();
}

void player::render(HDC hdc)
{
	_playerStatusUI->render();
	_playerCircleImg->alphaRender(getMemDC(), _playerCirclePos.x,_playerCirclePos.y,125);
	_playerCircleDirectionImg->alphaRender(getMemDC(), _playerCircleDirectionPos.x, _playerCircleDirectionPos.y,200);
	
	_img->aniRender(hdc, _pos.x, _pos.y, _ani);
	char str[128];
	sprintf_s(str, "%d : state", _moveDirection, strlen(str));
	TextOut(hdc, 50, 50, str, strlen(str));
}

void player::playerKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("player", "images/player/player.bmp", 1700, 1870, 10, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerCircle", "images/player/player_circle.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerCircleDirection", "images/player/player_circleDirection.bmp", 30, 30, true, RGB(255, 0, 255));
	//idle
	int frontIdle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("frontIdle", "player", frontIdle, 1, 10, false);

	int backIdle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("backIdle", "player", backIdle, 1, 10, false);

	int rightIdle[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("rightIdle", "player", rightIdle, 1, 10, false);

	int leftIdle[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("leftIdle", "player", leftIdle, 1, 10, false);
	//move
	int frontMove[] = { 10,11,12,13,14,15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("frontMove", "player", frontMove, 10, 10, true);

	int backMove[] = { 20,21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("backMove", "player", backMove, 10, 10, true);

	int rightMove[] = { 30,31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("rightMove", "player", rightMove, 10, 10, true);

	int leftMove[] = { 49,48,47,46,45,44,43,42,41,40 };
	KEYANIMANAGER->addArrayFrameAnimation("leftMove", "player", leftMove, 10, 10, true);
	//dash
	int frontDash[] = { 10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("frontDash", "player", frontDash, 5, 15, false, playerIdle,this);

	int backDash[] = { 20,21,22,23,24,25 };
	KEYANIMANAGER->addArrayFrameAnimation("backDash", "player", backDash, 5, 15, false, playerIdle, this);

	int rightDash[] = { 70,71,72,73,74,75,76,77 };
	KEYANIMANAGER->addArrayFrameAnimation("rightDash", "player", rightDash, 8, 15, false, playerIdle, this);

	int leftDash[] = { 87,86,85,84,83,82,81,80 };
	KEYANIMANAGER->addArrayFrameAnimation("leftDash", "player", leftDash, 8, 15, false, playerIdle, this);
	//hit
	int frontHit[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("frontHit", "player", frontHit, 1, 20, false, playerIdle, this);

	int BackHit[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("BackHit", "player", frontHit, 1, 20, false, playerIdle, this);

	int LeftHit[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftHit", "player", LeftHit, 1, 20, false, playerIdle, this);

	int rightHit[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("rightHit", "player", rightHit, 1, 20, false, playerIdle, this);
	//fall
	int frontFall[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("frontFall", "player", frontFall, 1, 20, false);

	int BackFall[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("BackFall", "player", BackFall, 1, 20, false);

	int LeftFall[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftFall", "player", LeftFall, 1, 20, false);

	int rightFall[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("rightFall", "player", rightFall, 1, 20, false);

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

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_playerStatusUI->setCurHp(400);
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

	//Hit 애니메이션
	if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::HIT)
	{
		_ani = KEYANIMANAGER->findAnimation("frontHit");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::HIT)
	{
		_ani = KEYANIMANAGER->findAnimation("backHit");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::HIT)
	{
		_ani = KEYANIMANAGER->findAnimation("rightHit");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::HIT)
	{
		_ani = KEYANIMANAGER->findAnimation("LeftHit");
		_ani->start();
	}

	//Fall 애니메이션
	if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::FALL)
	{
		_ani = KEYANIMANAGER->findAnimation("frontFall");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::FALL)
	{
		_ani = KEYANIMANAGER->findAnimation("backFall");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::FALL)
	{
		_ani = KEYANIMANAGER->findAnimation("rightFall");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::FALL)
	{
		_ani = KEYANIMANAGER->findAnimation("LeftFall");
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
	_arrState[static_cast<const int>(STATE::FALL)] = new state_Fall();
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

void player::playerCirclePosition()
{
	_playerCircleDirectionPos.x = cosf(_playerCircleDirectionAngle) * _playerCircleRadius + (_playerCirclePos.x + (_playerCircleImg->GetWidth()/2)-15);
	_playerCircleDirectionPos.y = -sinf(_playerCircleDirectionAngle) * _playerCircleRadius +  (_playerCirclePos.y + (_playerCircleImg->GetHeight() / 2)-15);
}

void player::playerIdle(void * obj)
{
	player* Player = (player*)obj;

	Player->setState(STATE::IDLE);
	Player->currentPlayerState();
	Player->startAni();                                                                                                                          

}