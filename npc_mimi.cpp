#include "stdafx.h"
#include "npc_mimi.h"


npc_mimi::npc_mimi()
{
}


npc_mimi::~npc_mimi()
{
}

HRESULT npc_mimi::init()
{
	npc::init();

	IMAGEMANAGER->addFrameImage("mimi", "images/npc/mimi.bmp", 1000, 800, 5, 4, true, 0xff00ff);
	_img = IMAGEMANAGER->findImage("mimi");

	// Ãß°¡ - ´ÙÀÌ¾ó·Î±×
	IMAGEMANAGER->addImage("mimiFace", "images/npc/mimiFace.bmp", 188, 189, true, 0xff00ff);
	_npcFaceImg = IMAGEMANAGER->findImage("mimiFace");
	_npcFaceText = "¹»¹ÙÀÌ³ğ¾Ó";

	int idle[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("mimi_Idle", "mimi", idle, 1, 10, false);

	int idle_Act1[] = { 2,11,10,9,10,11,2 };
	KEYANIMANAGER->addArrayFrameAnimation("mimi_Idle_Act1", "mimi", idle_Act1, 7, 10, false, idle2, this);

	int idle_Act2[] = { 2,12,14,13,14,12,16,15,16,12,2 };
	KEYANIMANAGER->addArrayFrameAnimation("mimi_Idle_Act2", "mimi", idle_Act2, 11, 10, false, idle2, this);

	//_state = stateNpc::IDLE;
	_ani = KEYANIMANAGER->findAnimation("mimi_Idle");
	_ani->start();


	return S_OK;
}

void npc_mimi::release()
{
}

void npc_mimi::update()
{
	npc::update();

	if (_state == stateNpc::IDLE || _state == stateNpc::IDLE_ACT1)
	{
		_idleCount += TIMEMANAGER->getElapsedTime();

		//1ÃÊ¸¶´Ù
		if (_idleCount >= 4)
		{
			_idleCount = 0;

			int RndNumber;
			RndNumber = RND->getFromIntTo(0, 3);

			if (_state == stateNpc::IDLE || _state == stateNpc::IDLE_ACT1 || _state == stateNpc::IDLE_ACT2)
			{
				if (RndNumber == 0)
				{
					_state = stateNpc::IDLE;
					isOnceAniPlay(_state);
				}
				else if (RndNumber == 1)
				{
					_state = stateNpc::IDLE_ACT1;
					isOnceAniPlay(_state);
				}
				else if (RndNumber == 2)
				{
					_state = stateNpc::IDLE_ACT2;
					isOnceAniPlay(_state);
				}
			}
		}

		if (_playerClose == true)
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_state = stateNpc::TALK;
				_ani = KEYANIMANAGER->findAnimation("mimi_Idle");
				_ani->start();
			}
		}
	}

	if (_state == stateNpc::UI1_ING)
	{
		_state = stateNpc::IDLE;
	}



}

void npc_mimi::render()
{
	npc::render();
	_img->aniRender(getMemDC(), _pos.x - CAMERA2D->getCamPosX(), _pos.y - CAMERA2D->getCamPosY(), _ani);


}

void npc_mimi::isOnceAniPlay(stateNpc EnumNumber)
{
	switch (_state)
	{
	case stateNpc::IDLE:
		_ani = KEYANIMANAGER->findAnimation("mimi_Idle");
		_ani->start();
		break;
	case stateNpc::IDLE_CHANGE_L:
		break;
	case stateNpc::IDLE_CHANGE_R:
		break;
	case stateNpc::IDLE_ACT1:
		_ani = KEYANIMANAGER->findAnimation("mimi_Idle_Act1");
		_ani->start();
		break;
	case stateNpc::IDLE_ACT2:
		_ani = KEYANIMANAGER->findAnimation("mimi_Idle_Act2");
		_ani->start();
		break;
		//case stateNpc::UI1_ING:
		//	_ani = KEYANIMANAGER->findAnimation("mimi_Idle");
		//	_ani->start();
	case stateNpc::TALK:
		break;
	default:
		break;
	}
}

void npc_mimi::idle2(void * obj)
{
	npc_mimi* mimi = (npc_mimi*)obj;

	mimi->_state = stateNpc::IDLE;
	mimi->isOnceAniPlay(mimi->_state);
}
