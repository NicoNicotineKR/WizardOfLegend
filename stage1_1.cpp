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
	//_aStar = new aStar;

	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;
	//_aStarCount = 0;

	//	재만 순서바꿈 - cuz 스킬과 연결
	_player->enemyLink(_enemyMgr);
	_player->init(_vvMap);
	//_player->enemyLink(_enemyMgr);
	_player->arrSkillInit();
	_player->skillIconInit();

	_enemyMgr->setPlayerAdress(_player);



	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 12);
	_stageMapLoader->MakeObjects(&_vvMap, &_vObjects, _enemyMgr);
	//	로더에서 몹 밀어넣어주고, 에니미 매니저가 몹들 이닛해줘야함 -> 순서주의
	_enemyMgr->setMapAdress(_vvMap);
	_enemyMgr->init();
	//_aStar->init();
	//_aStar->setMap(&_vvMap);
	//_stageMapLoader->release();
	delete _stageMapLoader;
	_stageMapLoader = nullptr;

	CAMERA2D->getMapSize(_tileNumX*TOP_TILESIZE, _tileNumY*TOP_TILESIZE);
	
	SOUNDMANAGER->stop(OPTIONMANAGER->getTempSoundName());
	SOUNDMANAGER->play("Ice", OPTIONMANAGER->getSoundBackVolume());
	OPTIONMANAGER->setTempSoundName("Ice");


	return S_OK;
}

void stage1_1::release()
{

}

void stage1_1::update()
{
	if (_allStop == false)
	{
		_player->update();
		_player->tileCheckFunc();

		_enemyMgr->update();

		CAMERA2D->setPos(_player->getPos());
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

void stage1_1::render()
{
	//기능1. 클리핑추가해야됨 ############################################
	TileMapRender();
	//기능2. 클리핑추가해야됨 ############################################
	VObjectRender();

	//_player->render(getMemDC());
	//_player->CamRender(getMemDC());
	//_enemyMgr->render();
	for (int i = 0; i < _enemyMgr->getVEnemy().size(); ++i)
	{

		if (_player->getPlayerTileCheckRc().bottom >= _enemyMgr->getVEnemy()[i]->getCollision().bottom)
		{
			_enemyMgr->getVEnemy()[i]->CamRender();
		}
	}
	_player->CamRender(getMemDC());
	for (int i = 0; i < _enemyMgr->getVEnemy().size(); ++i)
	{
		if (_player->getPlayerTileCheckRc().bottom < _enemyMgr->getVEnemy()[i]->getCollision().bottom)
		{
			_enemyMgr->getVEnemy()[i]->CamRender();
		}
	}
	_player->getSkillUI()->render();
}

void stage1_1::TileMapRender()
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

void stage1_1::VObjectRender()
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
