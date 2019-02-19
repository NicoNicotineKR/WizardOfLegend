#include "stdafx.h"
#include "npc_warp.h"


npc_warp::npc_warp()
{
}


npc_warp::~npc_warp()
{
}

HRESULT npc_warp::init()
{
	npc::init();

	IMAGEMANAGER->addFrameImage("warpNpc", "images/npc/warpNpc.bmp", 107, 164, 1, 1, true, 0xff00ff);
	_img = IMAGEMANAGER->findImage("warpNpc");

	// 추가 - 다이얼로그
	IMAGEMANAGER->addImage("warpNpcFace", "images/npc/warpNpcFace.bmp", 187, 189, true, 0xff00ff);
	_npcFaceImg = IMAGEMANAGER->findImage("warpNpcFace");
	_npcFaceText = "좋은 여행이야";

	int idle[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("warpNpc_Idle", "warpNpc", idle, 1, 10, false);

	_ani = KEYANIMANAGER->findAnimation("warpNpc_Idle");
	_ani->start();


	return S_OK;
}

void npc_warp::release()
{
}

void npc_warp::update()
{
	npc::update();

	if (_state == stateNpc::IDLE)
	{
		if (_playerClose == true)
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				_state = stateNpc::TALK;
				_ani = KEYANIMANAGER->findAnimation("warpNpc_Idle");
				_ani->start();
			}
		}
	}

	if (_state == stateNpc::UI1_ING)
	{
		_state = stateNpc::IDLE;
	}


}

void npc_warp::render()
{
	npc::render();

	_img->aniRender(getMemDC(), _pos.x - CAMERA2D->getCamPosX(), _pos.y - CAMERA2D->getCamPosY(), _ani);

}

void npc_warp::isOnceAniPlay(stateNpc EnumNumber)
{
	switch (_state)
	{
	case stateNpc::IDLE:
		_ani = KEYANIMANAGER->findAnimation("warpNpc_Idle");
		_ani->start();
		break;
	case stateNpc::TALK:
		break;
	default:
		break;
	}
}

void npc_warp::idle2(void * obj)
{
}
