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
#include "chainLightning.h"
#include "flameStrike.h"
#include "searingRush.h"
#include "enemyMgr.h"
#include "shockNova.h"
#include "stoneShot.h"
player::player()
{
}


player::~player()
{
}

HRESULT player::init(vvMap& vvMapLink)
{


	_vvMap = &vvMapLink;
	playerKeyAnimationInit();

	//arrStateInit();
	_img = IMAGEMANAGER->findImage("player");
	_ani = KEYANIMANAGER->findAnimation("frontIdle");
	_playerCircleImg = IMAGEMANAGER->findImage("playerCircle");
	_playerCircleDirectionImg = IMAGEMANAGER->findImage("playerCircleDirection");
	//_collisionRc = RectMake(WINSIZEX/2,WINSIZEY/2,30,30);			
	_playerCircleDirectionAngle = -90 * (180 / PI);
	_playerCircleRadius = 50;
	_maxHp = 500;					
	_curHp = 500;					

	_speed = 300.0f;					
	//_angle = ;					
	_pos.x = 200;
	_pos.y = WINSIZEY / 2;

	_vec.x = 0;
	_vec.y = 0;
	_aniDirection = ANIDIRECTION::FRONT;		
	_moveDirection = MOVEDIRECTION::BOTTOM;
	_state = STATE::IDLE;

	_isPlayerAniOnce = false;


	_boolMoveDirection = BOOLMOVEDIRECTION::NONE;
	_isLeftTopCheck = false;
	_isRightTopCheck = false;
	_isLeftBottomCheck = false;
	_isRightBottomCheck = false;

	_playerCirclePos.x = _pos.x + (_img->getFrameWidth() / 2) - (_playerCircleImg->GetWidth() / 2);
	_playerCirclePos.y = _pos.y + _img->getFrameHeight() - (_playerCircleImg->GetHeight() - 20);

	_tileCheckRcPos.x = _playerCirclePos.x + (_playerCircleImg->GetWidth() / 2) - 15;
	_tileCheckRcPos.y = _playerCirclePos.y + (_playerCircleImg->GetHeight() / 2) - 15;
	_tileCheckRc = RectMake(_tileCheckRcPos.x, _tileCheckRcPos.y, 28, 28);
	_tileCheckIndex[0].x = _tileCheckRc.left / 32 + _vec.x;
	_tileCheckIndex[0].y = _tileCheckRc.top / 32 + _vec.y;

	_tileCheckIndex[1].x = _tileCheckRc.right / 32 + _vec.x;
	_tileCheckIndex[1].y = _tileCheckRc.top / 32 + _vec.y;

	_tileCheckIndex[2].x = _tileCheckRc.left / 32 + _vec.x;
	_tileCheckIndex[2].y = _tileCheckRc.bottom / 32 + _vec.y;

	_tileCheckIndex[3].x = _tileCheckRc.right / 32 + _vec.x;
	_tileCheckIndex[3].y = _tileCheckRc.bottom / 32 + _vec.y;

	_tileCollVec[0].x =  _tileCollVec[0].y = 0;
	_tileCollVec[1].x = _tileCollVec[1].y = 0;
	_tileCollVec[2].x = _tileCollVec[2].y = 0;
	_tileCollVec[3].x = _tileCollVec[3].y = 0;

	//IMAGEMANAGER->findImage("thunder")->SetFrameX(0);

	_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth() / 2, _pos.y + _img->getFrameHeight() / 2, 100, 150);
	_isHit = false;
	_isAlive = true;
	_hitCount = 0;
	_dashLastPos.x = _dashLastPos.y = 0;
	for (int i = 0; i < 25; ++i)
	{
		_tileBlanket[i] = nullptr;
		_tileBlanketIndex[i].x = NULL;
		_tileBlanketIndex[i].y = NULL;
	}
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	_skillUI->update();
	_vec.x = 0;
	_vec.y = 0;

	//KEYANIMANAGER->update();
	_playerState->update(this);
	inPutKey();
	_playerStatusUI->update();

	if (_isHit)
	{
		_hitCount += TIMEMANAGER->getElapsedTime();
		if (_hitCount > 1.0f)
		{
			_hitCount = 0;
			_isHit = false;
		}
	}
	_playerCirclePos.x = _pos.x + (_img->getFrameWidth() / 2) - (_playerCircleImg->GetWidth() / 2);
	_playerCirclePos.y = _pos.y + _img->getFrameHeight() - (_playerCircleImg->GetHeight() - 20);
	_playerCircleDirectionAngle = getAngle(_playerCirclePos.x  + (_playerCircleImg->GetWidth() / 2) - CAMERA2D->getCamPosX(),
		_playerCirclePos.y + (_playerCircleImg->GetHeight() / 2) - CAMERA2D->getCamPosY(),
		_ptMouse.x, 
		_ptMouse.y);
	playerCirclePosition();
	_tileCheckRcPos.x = _playerCirclePos.x + (_playerCircleImg->GetWidth() / 2) - 15;
	_tileCheckRcPos.y = _playerCirclePos.y + (_playerCircleImg->GetHeight() / 2) - 15;
	_tileCheckRc = RectMake(_tileCheckRcPos.x, _tileCheckRcPos.y, 28, 28);

	_curSkills[0]->update(this);
	_curSkills[1]->update(this);
	_curSkills[2]->update(this);
	_curSkills[3]->update(this);

	_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth() / 2, _pos.y + _img->getFrameHeight() / 2, 80, 150);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	RECT temp;
	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		if (IntersectRect(&temp, &_collisionRc, &_em->getVEnemy()[i]->getAtkRc()))
		{
			if (!_isHit)
			{
				_isHit = true;
				_curHp -= 100;
				_playerStatusUI->setCurHp(_curHp);

				CAMERA2D->ShakeYourBodyBabe(OPTIONMANAGER->getShakingValue(), 20);

				if(_curHp<=0)
				{
					_state = STATE::DEAD;
					currentPlayerState();
				}
				else
				{
					_state = STATE::HIT;
					currentPlayerState();
					enemyAngleCal(_em->getVEnemy()[i]->getAngle());
					_vec.x = _vec.y = 0;
				}

			}
		}
	
	}

}

void player::render(HDC hdc)
{

	_playerStatusUI->render();
	_skillUI->render();
	//IMAGEMANAGER->findImage("thunder")->frameRender(getMemDC(), _tileCheckRc.left - 
	//	IMAGEMANAGER->findImage("thunder")->getFrameWidth()/2
	//	, _tileCheckRc.top - IMAGEMANAGER->findImage("thunder")->getFrameHeight() / 2);

	_curSkills[0]->render(this);
	_curSkills[1]->render(this);
	_curSkills[2]->render(this);
	_curSkills[3]->render(this);


//	Rectangle(getMemDC(), _collisionRc);

	Rectangle(getMemDC(), _tileCheckRc);
	_img->aniRender(hdc, _pos.x, _pos.y, _ani);
	if (_state == STATE::FALL)
	{
		for (int i = 0; i < 25; ++i)
		{
			if (_tileBlanket[i] == nullptr) continue;
			_tileBlanket[i]->frameRender(getMemDC(), _tileBlanketPos[i].x, _tileBlanketPos[i].y, _tileBlanketIndex[i].x, _tileBlanketIndex[i].y);
		}
	}
	else
	{
		_playerCircleImg->alphaRender(getMemDC(), _playerCirclePos.x, _playerCirclePos.y, 125);
		_playerCircleDirectionImg->alphaRender(getMemDC(), _playerCircleDirectionPos.x, _playerCircleDirectionPos.y, 200);
	}


}

void player::CamRender(HDC hdc)
{
	_playerStatusUI->render();
	//_skillUI->render();

	_curSkills[0]->render(this);
	_curSkills[1]->render(this);
	_curSkills[2]->render(this);
	_curSkills[3]->render(this);

	//Rectangle(getMemDC(), _tileCheckRc);
	if (_state == STATE::FALL)
	{
		for (int i = 0; i < 25; ++i)
		{
			if (_tileBlanket[i] == nullptr) continue;
			_tileBlanket[i]->frameRender(getMemDC(), _tileBlanketPos[i].x - CAMERA2D->getCamPosX(), _tileBlanketPos[i].y - CAMERA2D->getCamPosY(),
				_tileBlanketIndex[i].x, _tileBlanketIndex[i].y);
		}
	}
	else
	{
		_playerCircleImg->alphaRender(getMemDC(), _playerCirclePos.x - CAMERA2D->getCamPosX(), _playerCirclePos.y - CAMERA2D->getCamPosY(), 125);
		_playerCircleDirectionImg->alphaRender(getMemDC(), _playerCircleDirectionPos.x - CAMERA2D->getCamPosX(), _playerCircleDirectionPos.y - CAMERA2D->getCamPosY(), 200);
	}
	_img->aniRender(hdc, _pos.x - CAMERA2D->getCamPosX(), _pos.y - CAMERA2D->getCamPosY(), _ani);
}

void player::playerKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("player", "images/player/player.bmp", 1700, 4080, 10, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerCircle", "images/player/player_circle.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerCircleDirection", "images/player/player_circleDirection.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shockNova", "images/player/shockNova.bmp", 2100, 700, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lightningChain", "images/player/lightningChain.bmp", 540, 1800, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flameStrike", "images/player/flameStrike.bmp", 2560, 256, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("thunderFloor", "images/player/thunderFloor.bmp",540, 124, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("searingRush1", "images/player/searingRush.bmp", 2048, 64, 32, 1, true, RGB(255, 0, 255));

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
	int frontDash[] = { 183,184,185 };
	KEYANIMANAGER->addArrayFrameAnimation("frontDash", "player", frontDash, 3, 10, false, playerIdle,this);

	int backDash[] = { 180,181,182 };
	KEYANIMANAGER->addArrayFrameAnimation("backDash", "player", backDash, 3, 10, false, playerIdle, this);

	int rightDash[] = { 72,73,75 };
	KEYANIMANAGER->addArrayFrameAnimation("rightDash", "player", rightDash, 3, 10, false, playerIdle, this);

	int leftDash[] = {85,84,82};
	KEYANIMANAGER->addArrayFrameAnimation("leftDash", "player", leftDash, 3, 10, false, playerIdle, this);
	//hit
	int frontHit[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("frontHit", "player", frontHit, 1, 2, false, playerIdle, this);

	int backHit[] = { 5};
	KEYANIMANAGER->addArrayFrameAnimation("backHit", "player", backHit, 1, 2, false, playerIdle, this);

	int leftHit[] = { 6};
	KEYANIMANAGER->addArrayFrameAnimation("leftHit", "player", leftHit, 1, 2, false, playerIdle, this);

	int rightHit[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("rightHit", "player", rightHit, 1, 2, false, playerIdle, this);
	//fall
	int frontFall[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("frontFall", "player", frontFall, 1, 1, false);

	int backFall[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("backFall", "player", backFall, 1, 1, false);

	int leftFall[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("leftFall", "player", leftFall, 1, 1, false);

	int rightFall[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("rightFall", "player", rightFall, 1, 1, false);

	//LightningChain
	int frontLightningChain[] = { 50,51,52,53,54,55 };
	KEYANIMANAGER->addArrayFrameAnimation("frontLightningChain", "player", frontLightningChain, 6, 20, false, playerIdle, this);

	int backLightningChain[] = { 110,111,112,113,114,115,116,117,118,119 };
	KEYANIMANAGER->addArrayFrameAnimation("backLightningChain", "player", backLightningChain, 10, 30, false, playerIdle, this);

	int rightLightningChain[] = { 120,121,122,123,124,125,126,127 };
	KEYANIMANAGER->addArrayFrameAnimation("rightLightningChain", "player", rightLightningChain, 8, 20, false, playerIdle, this);

	int leftLightningChain[] = { 137,136,135,134,133,132,131,130 };
	KEYANIMANAGER->addArrayFrameAnimation("leftLightningChain", "player", leftLightningChain, 8, 20, false, playerIdle, this);

	//flameStrike
	int frontFlameStrikeStart[] = { 50,51,52,53,54,55,56,57 };
	KEYANIMANAGER->addArrayFrameAnimation("frontFlameStrikeStart", "player", frontFlameStrikeStart, 8, 20, false);

	int frontFlameStrikeSecond[] = { 60,61,62,63,64,65,66,67 };
	KEYANIMANAGER->addArrayFrameAnimation("frontFlameStrikeSecond", "player", frontFlameStrikeSecond, 8, 20, false);

	int frontFlameStrikeEnd[] = { 50,51,52,53,54,55,56,57 };
	KEYANIMANAGER->addArrayFrameAnimation("frontFlameStrikeEnd", "player", frontFlameStrikeEnd, 8, 20, false,playerIdle,this);

	int backFlameStrikeStartEnd[] = { 110,111,112,113,114,115,116,117,118,119 };
	KEYANIMANAGER->addArrayFrameAnimation("backFlameStrikeStart", "player", backFlameStrikeStartEnd, 10, 20, false);
	KEYANIMANAGER->addArrayFrameAnimation("backFlameStrikeEnd", "player", backFlameStrikeStartEnd, 10, 20, false,playerIdle,this);

	int backFlameStrikeSecond[] = { 140,141,142,143,144,145,146,147,148,149 };
	KEYANIMANAGER->addArrayFrameAnimation("backFlameStrikeSecond", "player", backFlameStrikeSecond, 10, 20, false);

	int rightFlameStrikeStartEnd[] = { 120,121,122,123,124,125,126,127 };
	KEYANIMANAGER->addArrayFrameAnimation("rightFlameStrikeStart", "player", rightFlameStrikeStartEnd, 8, 20, false);
	KEYANIMANAGER->addArrayFrameAnimation("rightFlameStrikeEnd", "player", rightFlameStrikeStartEnd, 8, 20, false,playerIdle,this);

	int rightFlameStrikeSecond[] = { 150,151,152,153,154,155,156,157,158,159 };
	KEYANIMANAGER->addArrayFrameAnimation("rightFlameStrikeSecond", "player", rightFlameStrikeSecond, 10, 20, false);

	int leftFlameStrikeStartEnd[] = { 137,136,135,134,133,132,131,130 };
	KEYANIMANAGER->addArrayFrameAnimation("leftFlameStrikeStart", "player", leftFlameStrikeStartEnd, 8, 20, false);
	KEYANIMANAGER->addArrayFrameAnimation("leftFlameStrikeEnd", "player", leftFlameStrikeStartEnd, 8, 20, false,playerIdle,this);

	int leftFlameStrikeSecond[] = { 169,168,167,166,165,164,163,162,161,160 };
	KEYANIMANAGER->addArrayFrameAnimation("leftFlameStrikeSecond", "player", leftFlameStrikeSecond, 10, 20, false);

	int dead[] = { 90,91,92,93,94,95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("dead", "player", dead, 10, 5, false);

	int frontShockNova[] = { 100,101,102,103,104,105,106,107,108,109 };
	KEYANIMANAGER->addArrayFrameAnimation("frontShockNova", "player", frontShockNova, 10, 20, false,playerIdle,this);

	int backShockNova[] = { 190,191,192,193,194,195,196,197,198,199 };
	KEYANIMANAGER->addArrayFrameAnimation("backShockNova", "player", backShockNova, 10, 20, false, playerIdle, this);

	int frontStoneShotEnd[] = {210,211,212,213,214,215,216,217};
	KEYANIMANAGER->addArrayFrameAnimation("frontStoneShotEnd", "player", frontStoneShotEnd, 8, 20, false, playerIdle, this);

	int backStoneShotEnd[] = { 200,201,202,203,204,205,206,207 };
	KEYANIMANAGER->addArrayFrameAnimation("backStoneShotEnd", "player", backStoneShotEnd, 8, 20, false, playerIdle, this);

	int rightStoneShotEnd[] = { 220,221,222,223,224,225,226,227 };
	KEYANIMANAGER->addArrayFrameAnimation("rightStoneShotEnd","player", rightStoneShotEnd, 8, 20, false, playerIdle, this);

	int leftStoneShotEnd[] = { 230,231,232,233,234,235,236,237, };
	KEYANIMANAGER->addArrayFrameAnimation("leftStoneShotEnd", "player", leftStoneShotEnd, 8, 20, false, playerIdle, this);



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
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_playerState->onButtonQ(this);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_playerState->onButtonLB(this);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_playerState->onButtonRB(this);
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
	if (_state == STATE::DEAD)
	{
		_ani = KEYANIMANAGER->findAnimation("dead");
		_ani->start();
	}
	//MOVE 애니메이션
	if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::MOVE)
	{
		SOUNDMANAGER->play("PlayerFootstep", OPTIONMANAGER->getSoundEffectVolume());
		_ani = KEYANIMANAGER->findAnimation("rightMove");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::MOVE)
	{
		SOUNDMANAGER->play("PlayerFootstep", OPTIONMANAGER->getSoundEffectVolume());
		_ani = KEYANIMANAGER->findAnimation("leftMove");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::MOVE)
	{
		SOUNDMANAGER->play("PlayerFootstep", OPTIONMANAGER->getSoundEffectVolume());
		_ani = KEYANIMANAGER->findAnimation("backMove");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::MOVE)
	{
		SOUNDMANAGER->play("PlayerFootstep", OPTIONMANAGER->getSoundEffectVolume());
		_ani = KEYANIMANAGER->findAnimation("frontMove");
		_ani->start();
	}

	//IDLE 애니메이션
	if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::IDLE)
	{
		SOUNDMANAGER->stop("PlayerFootstep");
		_ani = KEYANIMANAGER->findAnimation("rightIdle");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::IDLE)
	{
		SOUNDMANAGER->stop("PlayerFootstep");
		_ani = KEYANIMANAGER->findAnimation("leftIdle");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::IDLE)
	{
		SOUNDMANAGER->stop("PlayerFootstep");
		_ani = KEYANIMANAGER->findAnimation("backIdle");
		_ani->start();
	}
	else if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::IDLE)
	{
		SOUNDMANAGER->stop("PlayerFootstep");
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
		_ani = KEYANIMANAGER->findAnimation("leftHit");
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
		_ani = KEYANIMANAGER->findAnimation("leftFall");
		_ani->start();
	}

	if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::FALL)
	{
		_ani = KEYANIMANAGER->findAnimation("frontFall");
		_ani->start();
	}
	
	//번개 선더
	if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::SKILL_THREE)
	{
		if (_usingSkillName == "thunderingChain")
		{
			_ani = KEYANIMANAGER->findAnimation("frontLightningChain");
			_ani->start();
		}
	}
	if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::SKILL_THREE)
	{
		if (_usingSkillName == "thunderingChain")
		{
			_ani = KEYANIMANAGER->findAnimation("backLightningChain");
			_ani->start();
		}
	}
	else if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::SKILL_THREE)
	{
		if (_usingSkillName == "thunderingChain")
		{
			_ani = KEYANIMANAGER->findAnimation("rightLightningChain");
			_ani->start();
		}
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::SKILL_THREE)
	{
		if (_usingSkillName == "thunderingChain")
		{
			_ani = KEYANIMANAGER->findAnimation("leftLightningChain");
			_ani->start();
		}
	}

	//플레임 화염
	if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::SKILL_ONE)
	{
		if (_usingSkillName == "FlameStrike")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("frontFlameStrikeStart");
				_ani->start();
			}
			else if(_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("frontFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("frontFlameStrikeEnd");
				_ani->start();
			}
		}
		if (_usingSkillName == "stoneShot")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("frontFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("frontFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("frontStoneShotEnd");
				_ani->start();
			}
		}
	}
	if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::SKILL_ONE)
	{
		if (_usingSkillName == "FlameStrike")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("backFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("backFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("backFlameStrikeEnd");
				_ani->start();
			}
		}
		if (_usingSkillName == "stoneShot")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("backFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("backFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("backStoneShotEnd");
				_ani->start();
			}
		}
	}
	else if (_aniDirection == ANIDIRECTION::RIGHT && _state == STATE::SKILL_ONE)
	{
		if (_usingSkillName == "FlameStrike")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("rightFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("rightFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("rightFlameStrikeEnd");
				_ani->start();
			}
		}
		if (_usingSkillName == "stoneShot")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("rightFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("rightFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("rightStoneShotEnd");
				_ani->start();
			}
		}
	}
	else if (_aniDirection == ANIDIRECTION::LEFT && _state == STATE::SKILL_ONE)
	{
		if (_usingSkillName == "FlameStrike")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("leftFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("leftFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("leftFlameStrikeEnd");
				_ani->start();
			}
		}
		if (_usingSkillName == "stoneShot")
		{
			if (_curSkills[0]->getReLoadCount() == 0)
			{
				_ani = KEYANIMANAGER->findAnimation("leftFlameStrikeStart");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 1)
			{
				_ani = KEYANIMANAGER->findAnimation("leftFlameStrikeSecond");
				_ani->start();
			}
			else if (_curSkills[0]->getReLoadCount() == 2)
			{
				_ani = KEYANIMANAGER->findAnimation("leftStoneShotEnd");
				_ani->start();
			}
		}
	}

	if (_aniDirection == ANIDIRECTION::FRONT && _state == STATE::SKILL_FOUR)
	{
		if (_usingSkillName == "shockNova")
		{
			_ani = KEYANIMANAGER->findAnimation("frontShockNova");
			_ani->start();
		}
	}
	else if (_aniDirection == ANIDIRECTION::BACK && _state == STATE::SKILL_FOUR)
	{
		if (_usingSkillName == "shockNova")
		{
			_ani = KEYANIMANAGER->findAnimation("backShockNova");
			_ani->start();
		}
	}

	
}

void player::arrStateInit()
{
	_skillUI = new skillCooldownUI;
	_skillUI->init();

	_playerStatusUI = new playerStatusUI;
	_playerStatusUI->init();

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
	
	_arrSkills[static_cast<const int>(CURRENTSKILL::CHAINLIGHTNING)] = new chainLightning;
	

	_arrSkills[static_cast<const int>(CURRENTSKILL::FLAMESTRIKE)] = new flameStrike;


	_arrSkills[static_cast<const int>(CURRENTSKILL::SEARINGRUSH)] = new searingRush;


	_arrSkills[static_cast<const int>(CURRENTSKILL::SHOCKNOVA)] = new shockNova;


	_arrSkills[static_cast<const int>(CURRENTSKILL::STONESHOT)] = new stoneShot;


	_arrSkills[static_cast<const int>(CURRENTSKILL::CHAINLIGHTNING)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::FLAMESTRIKE)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::SEARINGRUSH)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::SHOCKNOVA)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::STONESHOT)]->init(this);
	_curSkills[0] = _arrSkills[static_cast<const int>(CURRENTSKILL::STONESHOT)];
	_curSkills[1] = _arrSkills[static_cast<const int>(CURRENTSKILL::SEARINGRUSH)];
	_curSkills[2] = _arrSkills[static_cast<const int>(CURRENTSKILL::CHAINLIGHTNING)];
	_curSkills[3] = _arrSkills[static_cast<const int>(CURRENTSKILL::SHOCKNOVA)];
	_playerState = _arrState[static_cast<const int>(STATE::IDLE)];

}

void player::arrSkillInit()
{
	_arrSkills[static_cast<const int>(CURRENTSKILL::CHAINLIGHTNING)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::SEARINGRUSH)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::FLAMESTRIKE)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::SHOCKNOVA)]->init(this);
	_arrSkills[static_cast<const int>(CURRENTSKILL::STONESHOT)]->init(this);
}

void player::skillIconInit()
{
	_skillUI->ChangeSkill(0, _curSkills[0]->getName(),
		_curSkills[0]->getMaxReLoadAddress(),
		_curSkills[0]->getReLoadCountAddress(),
		_curSkills[0]->getTotalCoolTimeAddress(),
		_curSkills[0]->getCurCoolTimeAddress());

	_skillUI->ChangeSkill(1, _curSkills[1]->getName(),
		_curSkills[1]->getMaxReLoadAddress(),
		_curSkills[1]->getReLoadCountAddress(),
		_curSkills[1]->getTotalCoolTimeAddress(),
		_curSkills[1]->getCurCoolTimeAddress());

	_skillUI->ChangeSkill(2, _curSkills[2]->getName(),
		_curSkills[2]->getMaxReLoadAddress(),
		_curSkills[2]->getReLoadCountAddress(),
		_curSkills[2]->getTotalCoolTimeAddress(),
		_curSkills[2]->getCurCoolTimeAddress());

	_skillUI->ChangeSkill(3, _curSkills[3]->getName(),
		_curSkills[3]->getMaxReLoadAddress(),
		_curSkills[3]->getReLoadCountAddress(),
		_curSkills[3]->getTotalCoolTimeAddress(),
		_curSkills[3]->getCurCoolTimeAddress());
}

void player::changeSkillIcon(int index)
{
	_skillUI->ChangeSkill(index, _curSkills[index]->getName(),
		_curSkills[index]->getMaxReLoadAddress(),
		_curSkills[index]->getReLoadCountAddress(),
		_curSkills[index]->getTotalCoolTimeAddress(),
		_curSkills[index]->getCurCoolTimeAddress());
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
		_dashLastPos.x = _pos.x;
		_dashLastPos.y = _pos.y;
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
	case STATE::FALL:
		_playerState = _arrState[static_cast<const int>(STATE::FALL)];
		_curHp -= 25;
		_playerStatusUI->setCurHp(_curHp);
		break;


	}
}

void player::playerCirclePosition()
{
	_playerCircleDirectionPos.x = cosf(_playerCircleDirectionAngle) * _playerCircleRadius + (_playerCirclePos.x + (_playerCircleImg->GetWidth()/2)-15);
	_playerCircleDirectionPos.y = -sinf(_playerCircleDirectionAngle) * _playerCircleRadius +  (_playerCirclePos.y + (_playerCircleImg->GetHeight() / 2)-15);
}
void player::isMoveOff()
{
}

void player::vecZero()
{
	if (_state != STATE::FALL && _state != STATE::HIT)
	{
		if (_isLeftTopCheck)
		{
			if (_state == STATE::HIT)
			{
				if (!(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[0].x]->getIsAvailMove() || (*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[0].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.x = -_tileCollVec[0].x;

				if (!(*_vvMap)[_tileCheckIndex[0].y][_tileCheckRc.left / 32]->getIsAvailMove() || (*_vvMap)[_tileCheckIndex[0].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.y = -_tileCollVec[0].y;
			}
			else if (_moveDirection == MOVEDIRECTION::LEFT_TOP)
			{
				if (!(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[0].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[0].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE&& _state != STATE::DASH))
					_vec.x = -_tileCollVec[0].x;

				if (!(*_vvMap)[_tileCheckIndex[0].y][_tileCheckRc.left / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[0].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE&& _state != STATE::DASH))
					_vec.y = -_tileCollVec[0].y;
			}
			else if (_moveDirection == MOVEDIRECTION::LEFT)
			{
				if (!(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[0].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[0].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE&& _state != STATE::DASH))
					_vec.x = -_tileCollVec[0].x;
			}
			else if (_moveDirection == MOVEDIRECTION::TOP)
			{

				if (!(*_vvMap)[_tileCheckIndex[0].y][_tileCheckRc.left / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[0].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE&& _state != STATE::DASH))
					_vec.y = -_tileCollVec[0].y;
			}

		}

		if (_isRightTopCheck)
		{
			if (_state == STATE::HIT)
			{
				if (!(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[1].x]->getIsAvailMove() || 
					(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[1].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.x = -_tileCollVec[1].x;

				if (!(*_vvMap)[_tileCheckIndex[1].y][_tileCheckRc.left / 32]->getIsAvailMove() || 
					(*_vvMap)[_tileCheckIndex[1].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.y = -_tileCollVec[1].y;
			}
			else if (_moveDirection == MOVEDIRECTION::RIGHT_TOP)
			{
				if (!(*_vvMap)[(_tileCheckRc.top) / 32][_tileCheckIndex[1].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[1].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.x = -_tileCollVec[1].x;
				}
				if (!(*_vvMap)[_tileCheckIndex[1].y][_tileCheckRc.right / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[1].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE&& _state != STATE::DASH))
				{
					_vec.y = -_tileCollVec[1].y;
				}
			}
			else if (_moveDirection == MOVEDIRECTION::RIGHT)
			{
				if (!(*_vvMap)[(_tileCheckRc.top) / 32][_tileCheckIndex[1].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[1].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.x = -_tileCollVec[1].x;
				}
			}
			else if (_moveDirection == MOVEDIRECTION::TOP)
			{
				if (!(*_vvMap)[_tileCheckIndex[1].y][_tileCheckRc.right / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[1].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE&& _state != STATE::DASH))
				{
					_vec.y = -_tileCollVec[1].y;
				}
			}

		}
		if (_isLeftBottomCheck)
		{
			if (_state == STATE::HIT)
			{
				if (!(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[2].x]->getIsAvailMove() ||
					(*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.x = -_tileCollVec[2].x;

				if (!(*_vvMap)[_tileCheckIndex[2].y][_tileCheckRc.left / 32]->getIsAvailMove() ||
					(*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.y = -_tileCollVec[2].y;
			}
			else if (_moveDirection == MOVEDIRECTION::LEFT_BOTTOM)
			{
				if (!(*_vvMap)[(_tileCheckRc.bottom) / 32][_tileCheckIndex[2].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.bottom / 32][_tileCheckIndex[2].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.x = -_tileCollVec[2].x;
				}
				if (!(*_vvMap)[_tileCheckIndex[2].y][_tileCheckRc.left / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[2].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.y = -_tileCollVec[2].y;
				}
			}
			else if (_moveDirection == MOVEDIRECTION::LEFT)
			{
				if (!(*_vvMap)[(_tileCheckRc.bottom) / 32][_tileCheckIndex[2].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.bottom / 32][_tileCheckIndex[2].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.x = -_tileCollVec[2].x;
				}
			}
			else if (_moveDirection == MOVEDIRECTION::BOTTOM)
			{
				if (!(*_vvMap)[_tileCheckIndex[2].y][_tileCheckRc.left / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[2].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.y = -_tileCollVec[2].y;
				}
			}

		}
		if (_isRightBottomCheck)
		{
			if (_state == STATE::HIT)
			{
				if (!(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[3].x]->getIsAvailMove() ||
					(*_vvMap)[_tileCheckRc.top / 32][_tileCheckIndex[3].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.x = -_tileCollVec[3].x;

				if (!(*_vvMap)[_tileCheckIndex[3].y][_tileCheckRc.left / 32]->getIsAvailMove() ||
					(*_vvMap)[_tileCheckIndex[3].y][_tileCheckRc.left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
					_vec.y = -_tileCollVec[3].y;
			}
			else if (_moveDirection == MOVEDIRECTION::RIGHT_BOTTOM)
			{
				if (!(*_vvMap)[(_tileCheckRc.bottom) / 32][_tileCheckIndex[3].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.bottom / 32][_tileCheckIndex[3].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.x = -_tileCollVec[3].x;
				}
				if (!(*_vvMap)[_tileCheckIndex[3].y][_tileCheckRc.right / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[3].y][_tileCheckRc.right / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.y = -_tileCollVec[3].y;
				}
			}
			else if (_moveDirection == MOVEDIRECTION::RIGHT)
			{
				if (!(*_vvMap)[(_tileCheckRc.bottom) / 32][_tileCheckIndex[3].x]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckRc.bottom / 32][_tileCheckIndex[3].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.x = -_tileCollVec[3].x;
				}
			}
			else if (_moveDirection == MOVEDIRECTION::BOTTOM)
			{
				if (!(*_vvMap)[_tileCheckIndex[3].y][_tileCheckRc.right / 32]->getIsAvailMove() ||
					((*_vvMap)[_tileCheckIndex[3].y][_tileCheckRc.right / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE && _state != STATE::DASH))
				{
					_vec.y = -_tileCollVec[3].y;
				}
			}

		}
	}
}

void player::enemyAngleCal(float angle)
{

	if ((angle* (180 / PI) <= 45 && angle * (180 / PI) >= 0) ||
		(angle * (180 / PI) <= 360 && angle * (180 / PI) >= 315))
	{
		setAniDirection(ANIDIRECTION::LEFT);
		startAni();
	}
	if ((angle* (180 / PI) > 135 &&
		angle * (180 / PI) < 225))
	{
		setAniDirection(ANIDIRECTION::RIGHT);
		startAni();
	}
	if (angle* (180 / PI) > 45 &&
		angle * (180 / PI) <= 135)
	{
		setAniDirection(ANIDIRECTION::FRONT);
		startAni();
	}
	if (angle* (180 / PI) >= 225 &&
		angle * (180 / PI) < 315)
	{
		setAniDirection(ANIDIRECTION::BACK);
		startAni();
	}
}



void player::playerIdle(void * obj)
{
	player* Player = (player*)obj;

	Player->setState(STATE::IDLE);
	Player->currentPlayerState();
	Player->startAni();           
	if ((*Player->_vvMap)[Player->getPlayerTileCheckRc().bottom / 32][Player->getPlayerTileCheckRc().left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE ||
		(*Player->_vvMap)[Player->getPlayerTileCheckRc().bottom / 32][Player->getPlayerTileCheckRc().right / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE ||
		(*Player->_vvMap)[Player->getPlayerTileCheckRc().top / 32][Player->getPlayerTileCheckRc().left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE ||
		(*Player->_vvMap)[Player->getPlayerTileCheckRc().top / 32][Player->getPlayerTileCheckRc().right / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
	{
		if (Player->getState() != STATE::FALL)
		{
			Player->setState(STATE::FALL);
			Player->currentPlayerState();
			Player->setIsHit(true);
			Player->_isFall = true;
			Player->_fallVecY = 0;
		}
	}
}

void player::playerFall(void * obj)
{
	player* Player = (player*)obj;

	Player->setState(STATE::IDLE);
	Player->currentPlayerState();
	Player->startAni();
}

void player::tileCheckFunc()
{

	_tileCheckIndex[0].x = (_tileCheckRc.left + _vec.x) / 32;
	_tileCheckIndex[0].y = (_tileCheckRc.top + _vec.y) / 32;

	_tileCheckIndex[1].x = (_tileCheckRc.right + _vec.x) / 32;
	_tileCheckIndex[1].y = (_tileCheckRc.top + _vec.y) / 32;

	_tileCheckIndex[2].x = (_tileCheckRc.left + _vec.x) / 32;
	_tileCheckIndex[2].y = (_tileCheckRc.bottom + _vec.y) / 32;

	_tileCheckIndex[3].x = (_tileCheckRc.right + _vec.x) / 32;
	_tileCheckIndex[3].y = (_tileCheckRc.bottom + _vec.y) / 32;

	if (!(*_vvMap)[_tileCheckIndex[0].y][_tileCheckIndex[0].x]->getIsAvailMove() || (*_vvMap)[_tileCheckIndex[0].y][_tileCheckIndex[0].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
	{
		_tileCollVec[0].x = _tileCheckRc.left - (*_vvMap)[_tileCheckIndex[0].y][_tileCheckIndex[0].x]->getTopTileRc().right;
		_tileCollVec[0].y = _tileCheckRc.top - (*_vvMap)[_tileCheckIndex[0].y][_tileCheckIndex[0].x]->getTopTileRc().bottom;
		_isLeftTopCheck = true;
	}
	else if ((*_vvMap)[_tileCheckIndex[0].y][_tileCheckIndex[0].x]->getIsAvailMove() && (*_vvMap)[_tileCheckIndex[0].y][_tileCheckIndex[0].x]->getTopTileAttr() != E_TILE_ATR::TILE_HOLE)
	{
		_isLeftTopCheck = false;
	}

	if (!(*_vvMap)[_tileCheckIndex[1].y][_tileCheckIndex[1].x]->getIsAvailMove() || (*_vvMap)[_tileCheckIndex[1].y][_tileCheckIndex[1].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
	{
		_tileCollVec[1].x = _tileCheckRc.right - (*_vvMap)[_tileCheckIndex[1].y][_tileCheckIndex[1].x]->getTopTileRc().left+1;
		_tileCollVec[1].y = _tileCheckRc.top - (*_vvMap)[_tileCheckIndex[1].y][_tileCheckIndex[1].x]->getTopTileRc().bottom;
		_isRightTopCheck = true;
	}
	else if ((*_vvMap)[_tileCheckIndex[1].y][_tileCheckIndex[1].x]->getIsAvailMove() && (*_vvMap)[_tileCheckIndex[1].y][_tileCheckIndex[1].x]->getTopTileAttr() != E_TILE_ATR::TILE_HOLE)
	{
		_isRightTopCheck = false;
	}

	if (!(*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getIsAvailMove() || (*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
	{
		_tileCollVec[2].x =  _tileCheckRc.left - (*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getTopTileRc().right;
		_tileCollVec[2].y =  _tileCheckRc.bottom - (*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getTopTileRc().top+1;
		_isLeftBottomCheck = true;
	}
	else if ((*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getIsAvailMove() && (*_vvMap)[_tileCheckIndex[2].y][_tileCheckIndex[2].x]->getTopTileAttr() != E_TILE_ATR::TILE_HOLE)
	{
		_isLeftBottomCheck = false;
	}

	if (!(*_vvMap)[_tileCheckIndex[3].y][_tileCheckIndex[3].x]->getIsAvailMove() || (*_vvMap)[_tileCheckIndex[3].y][_tileCheckIndex[3].x]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
	{
		_tileCollVec[3].x = _tileCheckRc.right - (*_vvMap)[_tileCheckIndex[3].y][_tileCheckIndex[3].x]->getTopTileRc().left+1;
		_tileCollVec[3].y = _tileCheckRc.bottom - (*_vvMap)[_tileCheckIndex[3].y][_tileCheckIndex[3].x]->getTopTileRc().top+1;
		_isRightBottomCheck = true;
	}
	else if ((*_vvMap)[_tileCheckIndex[3].y][_tileCheckIndex[3].x]->getIsAvailMove() && (*_vvMap)[_tileCheckIndex[3].y][_tileCheckIndex[3].x]->getTopTileAttr() != E_TILE_ATR::TILE_HOLE)
	{
		_isRightBottomCheck = false;
	}

	vecZero();
	_pos.x += _vec.x;
	_pos.y += _vec.y;
}
