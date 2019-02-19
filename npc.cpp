#include "stdafx.h"
#include "npc.h"

npc::npc()
{
}


npc::~npc()
{
}

HRESULT npc::init()
{
	IMAGEMANAGER->addFrameImage("fButton", "images/npc/Fbutton.bmp", 170, 36, 5, 1, true, 0xff00ff);
	_fButton = IMAGEMANAGER->findImage("fButton");

	int fButton_idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("fButton_Idle", "fButton", fButton_idle, 1, 10, false);

	int fButton_pop[] = { 0 , 1 , 2 , 3 , 4 , 3 , 2 , 1 , 0 };
	KEYANIMANAGER->addArrayFrameAnimation("fButton_Pop", "fButton", fButton_pop, 9, 20, false);

	_fButtonAni = KEYANIMANAGER->findAnimation("fButton_Idle");
	return S_OK;
}

void npc::release()
{
}

void npc::update()
{
	_distance = getDistance(_pos.x, _pos.y, _playerPos1.x, _playerPos1.y);

	if (_distance > 10000)
	{
		_playerClose = false;
	}
	else if (_distance <= 10000)
	{
		_playerClose = true;
	}


	if (_playerClose == true)
	{
		if (_isOncePop == false)
		{
			_fButtonAni = KEYANIMANAGER->findAnimation("fButton_Pop");
			_fButtonAni->start();
			_isOncePop = true;
		}
	}

	if (_playerClose == false)
	{
		_isOncePop = false;
	}

	_rc = RectMake(_pos.x, _pos.y, _img->getFrameWidth(), _img->getFrameHeight());
}

void npc::render()
{
	//if (_state == stateNpc::IDLE_R || _state == stateNpc::IDLE_L || _state == stateNpc::IDLE_ACT1 || _state == stateNpc::IDLE_ACT2 || _state == stateNpc::IDLE_CHANGE_L || _state == stateNpc::IDLE_CHANGE_R)
	//{
	if (_playerClose == true)
	{
		_fButton->aniRender(getMemDC(), _rc.left + (_img->getFrameWidth()) / 2 - 15 - CAMERA2D->getCamPosX(), _rc.top - 30 - CAMERA2D->getCamPosY(), _fButtonAni);
	}
	//}
}

void npc::setPos(POINT pos)
{
	_pos.x = pos.x;
	_pos.y = pos.y;
}

void npc::isOnceAniPlay(stateNpc EnumNumber)
{
}
