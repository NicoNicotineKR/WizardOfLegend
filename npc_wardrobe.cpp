#include "stdafx.h"
#include "npc_wardrobe.h"


npc_wardrobe::npc_wardrobe()
{
}


npc_wardrobe::~npc_wardrobe()
{
}

HRESULT npc_wardrobe::init()
{
	npc::init();

	IMAGEMANAGER->addFrameImage("wardrobe", "images/npc/wardrobe.bmp", 510, 640, 4, 4, true, 0xff00ff);

	_img = IMAGEMANAGER->findImage("wardrobe");

	IMAGEMANAGER->addImage("wardrobeFace", "images/npc/wardrobeFace.bmp", 188, 189, true, 0xff00ff);
	_npcFaceImg = IMAGEMANAGER->findImage("wardrobeFace");
	_npcFaceText = "¿È´¢’A";

	int idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("wardrobe_Idle", "wardrobe", idle, 1, 10, false);

	int idle_Act1[] = { 0,1,2,3,2,1,0 };
	KEYANIMANAGER->addArrayFrameAnimation("wardrobe_act1", "wardrobe", idle_Act1, 7, 10, false);

	int idle_Act2[] = { 0,4,0 };
	KEYANIMANAGER->addArrayFrameAnimation("wardrobe_act2", "wardrobe", idle_Act2, 3, 10, false);

	int idle_ui1_ing[] = { 7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("wardrobe_ui1_ing", "wardrobe", idle_ui1_ing, 3, 10, false, idle_ui1_esc1,this);

	int idle_ui1_esc[] = { 9,8,7,0 };
	KEYANIMANAGER->addArrayFrameAnimation("wardrobe_ui1_esc", "wardrobe", idle_ui1_esc, 4, 10, false, idle1, this);

	_ani = KEYANIMANAGER->findAnimation("wardrobe_Idle");
	this->setPos({ 100,300 });

	return S_OK;
}

void npc_wardrobe::release()
{
	//IMAGEMANAGER->deleteImage("wardrobe");
	//IMAGEMANAGER->deleteImage("wardrobeFace");
}

void npc_wardrobe::update()
{
	npc::update();

	if (_state == stateNpc::IDLE || _state == stateNpc::IDLE_ACT1 || _state == stateNpc::IDLE_ACT2)
	{
		_idleCount += TIMEMANAGER->getElapsedTime();

		//1ÃÊ¸¶´Ù
		if (_idleCount >= 3)
		{
			_idleCount = 0;

			int RndNumber;
			RndNumber = RND->getFromIntTo(0, 3);

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
		if (_state == stateNpc::IDLE || _state == stateNpc::IDLE_ACT1 || _state == stateNpc::IDLE_ACT2)
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_state = stateNpc::TALK;
			}
		}
	}

	if (_state == stateNpc::TALK)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_state = stateNpc::UI1_ING;
			isOnceAniPlay(_state);
		}
	}

	if (_state == stateNpc::UI1_ING)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			_state = stateNpc::UI1_ESC;
			isOnceAniPlay(_state);
		}
	}
}

void npc_wardrobe::render()
{
	npc::render();

	_img->aniRender(getMemDC(), _pos.x - CAMERA2D->getCamPosX(), _pos.y - CAMERA2D->getCamPosY(), _ani);
}

void npc_wardrobe::isOnceAniPlay(stateNpc EnumNumber)
{
	switch (_state)
	{
	case stateNpc::IDLE:
		_ani = KEYANIMANAGER->findAnimation("wardrobe_Idle");
		_ani->start();
		break;
	case stateNpc::IDLE_ACT1:
		_ani = KEYANIMANAGER->findAnimation("wardrobe_act1");
		_ani->start();
		break;
	case stateNpc::IDLE_ACT2:
		_ani = KEYANIMANAGER->findAnimation("wardrobe_act2");
		_ani->start();
		break;
	case stateNpc::TALK:
		break;
	case stateNpc::UI1_ING:
		_ani = KEYANIMANAGER->findAnimation("wardrobe_ui1_ing");
		_ani->start();
		break;
	case stateNpc::UI1_ESC:
		_ani = KEYANIMANAGER->findAnimation("wardrobe_ui1_esc");
		_ani->start();
		break;
	default:
		break;
	}
}

void npc_wardrobe::idle1(void * obj)
{
	npc_wardrobe* wardrobe = (npc_wardrobe*)obj;

	wardrobe->_state = stateNpc::IDLE;
	wardrobe->isOnceAniPlay(wardrobe->_state);
}

void npc_wardrobe::idle_ui1_esc1(void * obj)
{
	npc_wardrobe* wardrobe = (npc_wardrobe*)obj;

	wardrobe->_state = stateNpc::UI1_ESC;
	wardrobe->isOnceAniPlay(wardrobe->_state);
}
