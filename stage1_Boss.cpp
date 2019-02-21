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
	IMAGEMANAGER->addFrameImage("tileIce", "images/map/IceBaseTileSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objIce", "images/map/IceBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objEarth", "images/map/EarthBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objCommon", "images/map/CommonBaseObjSet.bmp", 3584, 448, 112, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("enemyCommon", "images/map/enemyUnitSet.bmp", 384, 160, 12, 5, true, 0xFF00FF);


	// 추가 - 다이얼로그
	IMAGEMANAGER->addImage("bossImg", "images/npc/bossImg.bmp", 188, 189, true, 0xff00ff);
	_npcFaceImg = IMAGEMANAGER->findImage("bossImg");
	_npcFaceText = "잡어 잡어잡어잡어";

	_stageMapLoader = new stageMapLoader;
	_enemyMgr = new enemyMgr;
	_miniMap = new minimapUI;
	_boss = new boss;
	_dialogueMaker = new dialogueMaker;
	_dialogueMaker->init();

	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;

	_player->enemyLink(_enemyMgr);
	_player->init(_vvMap);
	_player->arrSkillInit();
	_player->skillIconInit();

	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 20);
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
	_player->setPosX(600);
	_player->setPosY(2000);


	_stateBossStage = NON;


	return S_OK;
}

void stage1_Boss::release()
{
}

void stage1_Boss::update()
{
	if (_allStop == false)
	{
		if (_stateBossStage == NON || _stateBossStage == BATTLE)
		{
			_player->update();
		}
		else
		{
			_player->setState(STATE::IDLE);
			_player->currentPlayerState();
			_player->startAni();
			_player->setPosY(1000);
		}



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



	if (_player->getPos().y <= 1000 && _stateBossStage == NON)
	{
		_stateBossStage = CAMERAMOVE;
		CAMERA2D->setStateCamera(1);
	}

	if (CAMERA2D->getCamPosY() == 200 && _stateBossStage == CAMERAMOVE)
	{
		_stateBossStage = TALK;
	}

	if (_stateBossStage == TALK)
	{
		_dialogueMaker->update();

		if (_dialogueMaker->getPrintLen() == 0)
		{
			_dialogueMaker->setDialogue(_npcFaceImg, _npcFaceText, 0.1);
			_dialogueMaker->setIsStart(true);
		}
		else if (_dialogueMaker->getisStart() == false)
		{
			for (int i = 40; i < 44; ++i)
			{
				for (int j = 18; j < 25; ++j)
				{
					_vvMap[i][j]->setIsAvailMove(false);
					_vvMap[i][j]->setTopTileFrameX(16);

					for (int k = 0; k < 4; k++)
					{
						if (i == 40 + k)
						{
							_vvMap[i][j]->setTopTileFrameY(k);
						}
					}
				}
			}
			CAMERA2D->setStateCamera(0);
			_stateBossStage = BATTLE;
		}
	}



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

	if (_stateBossStage == TALK)
	{
		_dialogueMaker->render();
	}

	char str[128];
	sprintf_s(str, "%f ,%f   보스맵상태 : %d", _player->getPos().x, _player->getPos().y, _stateBossStage);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, strlen(str));
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
