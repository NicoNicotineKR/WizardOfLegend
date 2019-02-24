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
	IMAGEMANAGER->addImage("warpNpcFace", "images/npc/warpNpcFace.bmp", 187, 189, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("objCastle", "images/map/CastleBaseObjSet.bmp", 736, 384, 23, 12, true, 0xFF00FF);

	_npcFaceImg = IMAGEMANAGER->findImage("warpNpcFace");
	_npcFaceText1 = "몬스터가 남아있구마";
	_npcFaceText2 = "마지막 개발자가 있는 곳으로 안내하지";

	_stageMapLoader = new stageMapLoader;
	_enemyMgr = new enemyMgr;
	_miniMap = new minimapUI;
	_boss = new boss;

	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;

	//	재만 순서바꿈 - cuz 스킬과 연결
	_player->enemyLink(_enemyMgr);
//	_player->enemyLink(nullptr);
	_player->init(_vvMap);
	_player->arrSkillInit();
	_player->skillIconInit();

	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 31);
	_stageMapLoader->MakeObjects(&_vvMap, &_vObjects, _enemyMgr);
	//	로더에서 몹 밀어넣어주고, 에니미 매니저가 몹들 이닛해줘야함 -> 순서주의

	_enemyMgr->setPlayerAdress(_player);
	_enemyMgr->setMapAdress(_vvMap);
	_enemyMgr->init();

	_boss->setPlayerAdress(_player);
	_boss->init();
	float bossPosX = _vvMap[13][16]->getTopTilePos().x;
	float bossPosY = _vvMap[13][16]->getTopTilePos().y;
	POINTFLOAT bossPos = { bossPosX,bossPosY };
	_boss->setPos(bossPos);
	_player->bossLink(_boss);
//	_player->bossLink(nullptr);
	
	_miniMap->init(&_vvMap, _player->getPosAddress(), _enemyMgr->getVEnemyAdress());
	
	delete _stageMapLoader;
	_stageMapLoader = nullptr;

	CAMERA2D->getMapSize(_tileNumX*TOP_TILESIZE, _tileNumY*TOP_TILESIZE);
	
	SOUNDMANAGER->stop(OPTIONMANAGER->getTempSoundName());
	SOUNDMANAGER->play("Ice", OPTIONMANAGER->getSoundBackVolume());
	OPTIONMANAGER->setTempSoundName("Ice");

	_npc_warp = new npc_warp;
	_npc_warp->init();

	_dialogueMaker = new dialogueMaker;
	_dialogueMaker->init();

	_npc_warp->setPos({1800,2900});
	//_isOneSavePlayerHp = false;


	return S_OK;
}

void stage1_1::release()
{
	SAFE_RELEASE(_enemyMgr);
	SAFE_DELETE(_enemyMgr);

	SAFE_RELEASE(_miniMap);
	SAFE_DELETE(_miniMap);

	SAFE_RELEASE(_boss);
	SAFE_DELETE(_boss);

	SAFE_RELEASE(_npc_warp);
	SAFE_DELETE(_npc_warp);

	SAFE_RELEASE(_dialogueMaker);
	SAFE_DELETE(_dialogueMaker);
	
}

void stage1_1::update()
{
	if (_npc_warp->getNpcClosePlayer() == true && _dialogueMaker->getisStart() == false)
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_IsTalk = true;
		}
	}

	_dialogueMaker->update();

	if (_allStop == false && _IsTalk == false)
	{
		_player->update();
		_player->tileCheckFunc();

		_enemyMgr->update();
		_miniMap->update();

		_boss->update();

		_npc_warp->update();
		_npc_warp->setPlayerPos(_player->getPos());

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

	RECT temp;
	for (int i = 0; i < _vObjects.size(); ++i)
	{
		if (_vObjects[i]->getAttr() == OBJ_UNBREAKABLE) continue;
		if (IntersectRect(&temp, &_player->getPlayerTileCheckRc(), &_vObjects[i]->getRc()))
		{
			_vObjects.erase(_vObjects.begin() + i);
			break;
		}
	}

	if (_IsTalk == true)
	{
		if (_enemyMgr->getVEnemy().size() == 0)
		{
			if (_dialogueMaker->getPrintLen() == 0)
			{
				_dialogueMaker->setDialogue(_npcFaceImg, _npcFaceText2, 0.1);
				_dialogueMaker->setIsStart(true);
			}
			else if (_dialogueMaker->getisStart() == false)
			{
				_dialogueMaker->setPrintLen(0);
				SCENEMANAGER->changeScene("stage1_Boss");
				_IsTalk = false;
			}
		}
		else if (_enemyMgr->getVEnemy().size() != 0)
		{
			if (_dialogueMaker->getPrintLen() == 0)
			{
				_dialogueMaker->setDialogue(_npcFaceImg, _npcFaceText1, 0.1);
				_dialogueMaker->setIsStart(true);
			}
			else if (_dialogueMaker->getisStart() == false)
			{
				_dialogueMaker->setPrintLen(0);
				_IsTalk = false;
			}
		}
	}


	//SCENEMANAGER->changeScene("stage1_Boss");
}

void stage1_1::render()
{
	//기능1. 클리핑추가해야됨 ############################################
	TileMapRender();
	//기능2. 클리핑추가해야됨 ############################################
	VObjectRender();

	_boss->render();
	//_player->render(getMemDC());
	//_player->CamRender(getMemDC());
	//_enemyMgr->render();
	for (int i = 0; i < _enemyMgr->getVEnemy().size(); ++i)
	{

		if (_player->getPlayerTileCheckRc().bottom >= _enemyMgr->getVEnemy()[i]->getCollision().bottom)
		{
			_enemyMgr->getVEnemy()[i]->CamRender();
		}

		//	aStar용 렉트 렌더

		if (KEYMANAGER->isToggleKey(VK_F9))
		{
			list<POINT>::iterator showPathI = _enemyMgr->getVEnemy()[i]->getPath()->begin();
			for (; showPathI != _enemyMgr->getVEnemy()[i]->getPath()->end(); showPathI++)
			{
				int idX = (*showPathI).x;
				int idY = (*showPathI).y;

				RECT temp = _vvMap[idY][idX]->getTopTileRc();

				Rectangle(getMemDC(), temp.left - CAMERA2D->getCamPosX(), temp.top - CAMERA2D->getCamPosY(), temp.right - CAMERA2D->getCamPosX(), temp.bottom - CAMERA2D->getCamPosY());

			}
		}

	}
	_player->CamRender(getMemDC());

	for (int i = 0; i < _enemyMgr->getVEnemy().size(); ++i)
	{
		if (_player->getPlayerTileCheckRc().bottom < _enemyMgr->getVEnemy()[i]->getCollision().bottom)
		{
			_enemyMgr->getVEnemy()[i]->CamRender();

			if (KEYMANAGER->isToggleKey(VK_F9))
			{
				list<POINT>::iterator showPathI = _enemyMgr->getVEnemy()[i]->getPath()->begin();
				for (; showPathI != _enemyMgr->getVEnemy()[i]->getPath()->end(); showPathI++)
				{
					int idX = (*showPathI).x;
					int idY = (*showPathI).y;

					RECT temp = _vvMap[idY][idX]->getTopTileRc();

					Rectangle(getMemDC(), temp.left - CAMERA2D->getCamPosX(), temp.top - CAMERA2D->getCamPosY(), temp.right - CAMERA2D->getCamPosX(), temp.bottom - CAMERA2D->getCamPosY());

				}
			}

		}
	}
	_player->getSkillUI()->render();
	_miniMap->render();




	_npc_warp->render();
	_dialogueMaker->render();
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
