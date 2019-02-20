#include "stdafx.h"
#include "npc_broomStick.h"


npc_broomStick::npc_broomStick()
{
}


npc_broomStick::~npc_broomStick()
{
}

HRESULT npc_broomStick::init()
{
	//npc::init();

	IMAGEMANAGER->addFrameImage("broomStick", "images/npc/broomStick.bmp", 800, 320, 5, 2, true, 0xff00ff);

	_img = IMAGEMANAGER->findImage("broomStick");

	int idle[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("broomStick_Idle", "broomStick", idle, 1, 10, false);

	int idle_Act[] = { 0,1,2,3,4,5,6,7,6,5,4,3,2,1 };
	KEYANIMANAGER->addArrayFrameAnimation("broomStick_Act", "broomStick", idle_Act, 14, 10, true);

	_pos.x = 300;
	_pos.y = 400;

	_state = stateNpc::IDLE_ACT1;
	_ani = KEYANIMANAGER->findAnimation("broomStick_Act");
	_ani->start();

	yameMove1 = false;

	return S_OK;
}

void npc_broomStick::release()
{
}

void npc_broomStick::update()
{
	//npc::update();

	if (_state == stateNpc::IDLE || _state == stateNpc::IDLE_ACT1)
	{
		_idleCount += TIMEMANAGER->getElapsedTime();

		//1초마다
		if (_idleCount >= 2)
		{
			_idleCount = 0;

			int RndNumber;
			RndNumber = RND->getFromIntTo(0, 2);

			if (_state == stateNpc::IDLE)
			{
				if (RndNumber == 0)
				{
					_state = stateNpc::IDLE;
					isOnceAniPlay(_state);
				}
				if (RndNumber == 1)
				{
					_state = stateNpc::IDLE_ACT1;
					isOnceAniPlay(_state);
				}
			}
			else if (_state == stateNpc::IDLE_ACT1)
			{
				if (RndNumber == 0)
				{
					_state = stateNpc::IDLE;
					isOnceAniPlay(_state);
				}
				if (RndNumber == 1)
				{
					_state = stateNpc::IDLE_ACT1;
					isOnceAniPlay(_state);
				}
			}
		}
	}

	//움직임을 줘보자
	if (_state == stateNpc::IDLE_ACT1)
	{
		if (yameMove1 == false)
		{
			if (_pos.x < 1800)
			{
				_pos.x += STICK_SPEED;
			}
			else
			{
				yameMove1 = true;
			}

		}
		else if (yameMove1 == true)
		{
			if (_pos.x > 600)
			{
				_pos.x -= STICK_SPEED;
			}
			else
			{
				yameMove1 = false;
			}
		}
	}


}

void npc_broomStick::render()
{
	npc::render();

	_img->aniRender(getMemDC(), _pos.x - CAMERA2D->getCamPosX(), _pos.y - CAMERA2D->getCamPosY(), _ani);

}

void npc_broomStick::isOnceAniPlay(stateNpc EnumNumber)
{
	switch (_state)
	{
	case stateNpc::IDLE:
		_ani = KEYANIMANAGER->findAnimation("broomStick_Idle");
		_ani->start();
		break;
	case stateNpc::IDLE_ACT1:
		_ani = KEYANIMANAGER->findAnimation("broomStick_Act");
		_ani->start();
		break;
	default:
		break;
	}
}
