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
	//_boss = new boss;


	_vvMap.clear();
	_vObjects.clear();

	_tileNumX = 0;
	_tileNumY = 0;

	//	순서바꿈
	_player->arrStateInit();
	_player->enemyLink(_enemyMgr);
	//_player->bossLink(_boss);
	_player->init(_vvMap);
	//_player->enemyLink(_enemyMgr);

	_player->arrSkillInit();
	_player->skillIconInit();
	_enemyMgr->setPlayerAdress(_player);
	_enemyMgr->setMapAdress(_vvMap);
	//_boss->setPlayerAdress(_player);

	_stageMapLoader->LoadMap(&_vvMap, &_tileNumX, &_tileNumY, 13);
	_stageMapLoader->MakeObjects(&_vvMap, &_vObjects, _enemyMgr);
	_enemyMgr->init();
	//_boss->init();

	delete _stageMapLoader;
	_stageMapLoader = nullptr;

//	_boss->setPlayerAdress(_player);

	CAMERA2D->getMapSize(_tileNumX*TOP_TILESIZE, _tileNumY*TOP_TILESIZE);

	_dialogueMaker = new dialogueMaker;
	_dialogueMaker->init();

	_nm = new npcMgr;
	_nm->init();

	_skillbookUI = new skillbookUI;
	_skillbookUI->LinkToPlayer(_player);
	_skillbookUI->init();

	_playerInfoBoxUI = new playerInfoBoxUI;
	_playerInfoBoxUI->init();

	_playerInfoBox = new playerInfoBox;
	_playerInfoBox->setPlayerAddreesLink(_player);
	_playerInfoBox->init();


	//시작지점
	_player->setPosX(1000);
	_player->setPosY(1000);

	_isTalk = false;
	_isSkillbookMode = false;
	_skillbookUI->LinkSkillBookUIMode(&_isSkillbookMode);
	_allStop2 = false;

	SOUNDMANAGER->stop(OPTIONMANAGER->getTempSoundName());
	SOUNDMANAGER->play("PlayerRoom", OPTIONMANAGER->getSoundBackVolume());
	OPTIONMANAGER->setTempSoundName("PlayerRoom");

	return S_OK;
}

void home::release()
{
}

void home::update()
{
	if (_allStop == false)
	{
		if (_dialogueMaker->getisStart() == false && !_isSkillbookMode && _allStop2 == false)
		{
			_player->update();
		}

		_player->tileCheckFunc();

		_enemyMgr->update();
//		_boss->update();

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

					if (i == 0) {
						_isSkillbookMode = true;
						//추가
						_isOnceEndSkillUi = true;
					}

				}
			}
		}




		if (_isOnceEndSkillUi == true)
		{
			if (_isSkillbookMode == false)
			{
				_nm->getvNpce()[0]->setNpcState(stateNpc::UI1_ESC);
				_nm->getvNpce()[0]->isOnceAniPlay(stateNpc::UI1_ESC);
				_isOnceEndSkillUi = false;
			}
		}




		if (_nm->getvNpce()[4]->getState() == stateNpc::UI1_ING)
		{
			SOUNDMANAGER->stop("logoSound");
			SOUNDMANAGER->stop("titleMusic");
			SOUNDMANAGER->stop("PlayerRoom");
			SOUNDMANAGER->stop("Ice");

			//플레이어	   
			SOUNDMANAGER->stop("PlayerFootstep");
			SOUNDMANAGER->stop("chainLightning");
			SOUNDMANAGER->stop("chainLightning2");
			SOUNDMANAGER->stop("flameStrike");
			SOUNDMANAGER->stop("searingRush");
			SOUNDMANAGER->stop("stoneShot");

			//몬스터		
			SOUNDMANAGER->stop("goul");
			SOUNDMANAGER->stop("KnightAttack");

			//보스		
			SOUNDMANAGER->stop("Bossbackground");
			SOUNDMANAGER->stop("IceBossHurt");
			SOUNDMANAGER->stop("IceBossLaugh");
			SOUNDMANAGER->stop("IceShakeLong");

			//npc		  
			SOUNDMANAGER->stop("Broom");

			SCENEMANAGER->changeScene("stage1_1");
			CAMERA2D->setPos({ 0,0 });
			
		}
	}

	if (_allStop == false && !_isSkillbookMode)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && _allStop2 == false)
		{
			_allStop = true;
			OPTIONMANAGER->setIsStartOption(true);
		}
	}
	else if (_allStop == true)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && _allStop2 == false)
		{
			_allStop = false;
			OPTIONMANAGER->setIsStartOption(false);
		}
	}

	_allStop = OPTIONMANAGER->getIsStartOption();

	//==================================================================

	//if (_nm->getvNpce()[0]->getState() == stateNpc::UI1_ING)
	//{
	//
	//}

	_skillbookUI->update();

	if (_allStop == false)
	{
		_playerInfoBox->update();
		_allStop2 = _playerInfoBox->getIsStart();
	}
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
}

void home::render()
{
	TileMapRender();
	VObjectRender();

	//_player->CamRender(getMemDC());
	_enemyMgr->render();
//	_boss->render();
	//_nm->render();
	for (int i = 0; i < _nm->getvNpce().size(); ++i)
	{
		if (_nm->getvNpce()[i]->getNpcRc().bottom <= _player->getCollisionRc().bottom)
		{
			_nm->getvNpce()[i]->render();
		}
	}
	_player->CamRender(getMemDC());
	for (int i = 0; i < _nm->getvNpce().size(); ++i)
	{
		if (_nm->getvNpce()[i]->getNpcRc().bottom > _player->getCollisionRc().bottom)
		{
			_nm->getvNpce()[i]->render();
		}
	}

	_dialogueMaker->render();
	_skillbookUI->render();

	_playerInfoBoxUI->render();
	_playerInfoBox->render();
	_player->getSkillUI()->render();
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
