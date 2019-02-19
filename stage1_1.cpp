#include "stdafx.h"
#include "stage1_1.h"


stage1_1::stage1_1()
{
}


stage1_1::~stage1_1()
{
}

HRESULT stage1_1::init()
{
	IMAGEMANAGER->addFrameImage("tileIce", "images/map/IceBaseTileSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objIce", "images/map/IceBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objEarth", "images/map/EarthBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objCommon", "images/map/CommonBaseObjSet.bmp", 3584, 448, 112, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("enemyCommon", "images/map/enemyUnitSet.bmp", 384, 160, 12, 5, true, 0xFF00FF);


	_stageMapLoader = new stageMapLoader;
	_enemyMgr = new enemyMgr;
	_player = new player;
	_aStar = new aStar;

	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;
	_aStarCount = 0;

	_player->init(_vvMap);
	_player->enemyLink(_enemyMgr);

	_enemyMgr->setPlayerAdress(_player);
	_enemyMgr->setMapAdress(_vvMap);


	_aStar->init();
	_aStar->setMap(_vvMap);

	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 12);
	_stageMapLoader->MakeObjects(&_vvMap, &_vObjects, _enemyMgr);
	//	로더에서 몹 밀어넣어주고, 에니미 매니저가 몹들 이닛해줘야함 -> 순서주의
	_enemyMgr->init();
	//_stageMapLoader->release();
	delete _stageMapLoader;
	_stageMapLoader = nullptr;

	CAMERA2D->getMapSize(_tileNumX*TOP_TILESIZE, _tileNumY*TOP_TILESIZE);
	//_camera2D->setPos(_player->getPos());

	return S_OK;
}

void stage1_1::release()
{

}

void stage1_1::update()
{

	_player->update();
	_player->tileCheckFunc();

	_enemyMgr->update();

	CAMERA2D->setPos(_player->getPos());



}

void stage1_1::render()
{
	//기능1. 클리핑추가해야됨 ############################################
	TileMapRender();
	//기능2. 클리핑추가해야됨 ############################################
	VObjectRender();

	//_player->render(getMemDC());
	_player->CamRender(getMemDC());
	_enemyMgr->render();


	char str[128];
	sprintf_s(str, "%d,%d", CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY());
	TextOut(getMemDC(), WINSIZEX / 2, 100, str, strlen(str));

}

void stage1_1::TileMapRender()
{
	for (int i = 0; i < _tileNumY; i++)
	{
		for (int j = 0; j < _tileNumX; j++)
		{
			_vvMap[i][j]->CamTileRender(CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY());
		}
	}
}

void stage1_1::VObjectRender()
{
	for (int i = 0; i < _vObjects.size(); i++)
	{
		_vObjects[i]->CamRender(CAMERA2D->getCamPosX(), CAMERA2D->getCamPosY());
	}
}
