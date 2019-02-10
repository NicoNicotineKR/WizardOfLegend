#include "stdafx.h"
#include "enemy_Knight.h"


enemy_Knight::enemy_Knight()
{
}


enemy_Knight::~enemy_Knight()
{
}

HRESULT enemy_Knight::init()
{
	return S_OK;
}

void enemy_Knight::release()
{
}

void enemy_Knight::update()
{
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
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightMoveStart", "knight", rightMoveStart, 5, 5, false, knight_rightMoving, this);
	int rightMoving[] = { 6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("knight_rightMoving", "knight", rightMoving, 6, 5, true);

	//charge

	//attack
}

void enemy_Knight::knight_rightMoving(void * obj)
{
}
