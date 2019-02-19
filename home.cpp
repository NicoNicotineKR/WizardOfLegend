#include "stdafx.h"
#include "home.h"


home::home()
{
}


home::~home()
{
}

HRESULT home::init()
{
	IMAGEMANAGER->addFrameImage("tileCommon", "images/map/CommonBaseTileSet.bmp", 3584, 448, 112, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objCommon", "images/map/CommonBaseObjSet.bmp", 3584, 448, 112, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objEarth", "images/map/EarthBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);

	_stageMapLoader = new stageMapLoader;
	_enemyMgr = new enemyMgr;
	//_player = new player;

	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;

	_player->init(_vvMap);
	_player->enemyLink(_enemyMgr);

	_enemyMgr->setPlayerAdress(_player);
	_enemyMgr->setMapAdress(_vvMap);

	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 13);
	_stageMapLoader->MakeObjects(&_vvMap, &_vObjects, _enemyMgr);
	_enemyMgr->init();

	delete _stageMapLoader;
	_stageMapLoader = nullptr;

	CAMERA2D->getMapSize(_tileNumX*TOP_TILESIZE, _tileNumY*TOP_TILESIZE);

	_dialogueMaker = new dialogueMaker;
	_dialogueMaker->init();

	_nm = new npcMgr;
	_nm->init();

	//시작지점
	_player->setPosX(1000);
	_player->setPosY(1000);

	return S_OK;
}

void home::release()
{
}

void home::update()
{
	if (_allStop == false)
	{
		_player->update();
		_player->tileCheckFunc();

		_enemyMgr->update();

		CAMERA2D->setPos(_player->getPos());

		//========================================

		_dialogueMaker->update();
		_nm->update();
		_nm->setPlayerPos(_player->getPos());

		for (int i = 0; i < _nm->getvNpce().size(); i++)
		{
			//말하기 상태가되면
			if (_nm->getvNpce()[i]->getState() == stateNpc::TALK)
			{
				//길이 0 일때
				if (_dialogueMaker->getPrintLen() == 0)
				{
					_dialogueMaker->setDialogue(_nm->getvNpce()[i]->getNpcFaceImg(), _nm->getvNpce()[i]->getNpcFaceText(), 0.1);
					_dialogueMaker->setIsStart(true);
				}
				else if (_dialogueMaker->getisStart() == false)
				{
					_dialogueMaker->setPrintLen(0);
					_nm->getvNpce()[i]->setNpcState(stateNpc::UI1_ING);
					_nm->getvNpce()[i]->isOnceAniPlay(stateNpc::UI1_ING);
				}
			}
		}

		if (_nm->getvNpce()[4]->getState() == stateNpc::UI1_ING)
		{
			SCENEMANAGER->changeScene("stage1_1");
			CAMERA2D->setPos({ 0,0 });
		}
	}

	if (_allStop == false)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			_allStop = true;
			OPTIONMANAGER->setIsStartOption(true);
		}
	}
	else if (_allStop == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			_allStop = false;
			OPTIONMANAGER->setIsStartOption(false);
		}
	}

	_allStop = OPTIONMANAGER->getIsStartOption();
}

void home::render()
{
	TileMapRender();
	VObjectRender();

	_player->CamRender(getMemDC());
	_enemyMgr->render();
	_nm->render();
	_dialogueMaker->render();

	char str[128];
	sprintf_s(str, "%d,%d", CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY());
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));

	sprintf_s(str, "%d,%d", _player->getLeftBottomIndex().x, _player->getLeftBottomIndex().y);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 + 100, str, strlen(str));
}

void home::TileMapRender()
{
	for (int i = _player->getLeftBottomIndex().x - 52; i < _player->getLeftBottomIndex().x + 52; i++)
	{
		for (int j = _player->getLeftBottomIndex().y - 30; j < _player->getLeftBottomIndex().y + 30; j++)
		{
			if (j < 0)continue;
			if (i < 0)continue;
			if (j >= _tileNumY)continue;
			if (i >= _tileNumX)continue;

			_vvMap[j][i]->CamTileRender(CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY());
		}
	}
}

void home::VObjectRender()
{
	for (int i = 0; i < _vObjects.size(); i++)
	{
		if (_vObjects[i]->getIdx().x < _player->getLeftBottomIndex().x - 52)continue;
		if (_vObjects[i]->getIdx().x > _player->getLeftBottomIndex().x + 52)continue;
		if (_vObjects[i]->getIdx().y < _player->getLeftBottomIndex().y - 35)continue;
		if (_vObjects[i]->getIdx().y > _player->getLeftBottomIndex().y + 35)continue;

		_vObjects[i]->CamRender(CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY());
	}
}
