#include "stdafx.h"
#include "stage1_Boss.h"


stage1_Boss::stage1_Boss()
{
}


stage1_Boss::~stage1_Boss()
{
}

HRESULT stage1_Boss::init()
{
	_stageMapLoader = new stageMapLoader;
	_enemyMgr = new enemyMgr;
	_miniMap = new minimapUI;
	_boss = new boss;

	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;

	_player->enemyLink(_enemyMgr);
	_player->init(_vvMap);
	_player->arrSkillInit();
	_player->skillIconInit();

	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 14);
	_stageMapLoader->MakeObjects(&_vvMap, &_vObjects, _enemyMgr);

	_enemyMgr->setPlayerAdress(_player);
	_enemyMgr->setMapAdress(_vvMap);
	_enemyMgr->init();

	_boss->setPlayerAdress(_player);
	_boss->init();
	float bossPosX = _vvMap[13][16]->getTopTilePos().x;
	float bossPosY = _vvMap[13][16]->getTopTilePos().y;
	POINTFLOAT bossPos = { bossPosX,bossPosY };
	_boss->setPos(bossPos);

	_miniMap->init(&_vvMap, _player->getPosAddress(), _enemyMgr->getVEnemyAdress());

	delete _stageMapLoader;
	_stageMapLoader = nullptr;

	CAMERA2D->getMapSize(_tileNumX*TOP_TILESIZE, _tileNumY*TOP_TILESIZE);

	SOUNDMANAGER->stop(OPTIONMANAGER->getTempSoundName());
	SOUNDMANAGER->play("Bossbackground", OPTIONMANAGER->getSoundBackVolume());
	OPTIONMANAGER->setTempSoundName("Bossbackground");

	_player->setCurHp(_savePlayerHp);

	return S_OK;
}

void stage1_Boss::release()
{
}

void stage1_Boss::update()
{
	if (_allStop == false)
	{
		_player->update();
		_player->tileCheckFunc();

		_enemyMgr->update();
		_miniMap->update();

		_boss->update();

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

void stage1_Boss::render()
{
	TileMapRender();
	VObjectRender();

	_boss->render();
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
	_miniMap->render();
}

void stage1_Boss::TileMapRender()
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

void stage1_Boss::VObjectRender()
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
