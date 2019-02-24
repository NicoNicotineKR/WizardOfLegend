#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	//SetCursor(NULL);
	ShowCursor(false);

	// ====== 형우 테스트용 =====
	_introScene = new introScene;
	_mainmenu = new mainmenu;
	_home = new home;
	_player = new player;
	_home->setPlayerLink(_player);
	//	======	재만 테스트용 ======
	_mapEditor = new mapEditor;
	_testStage = new testStage;

	_stage1_1 = new stage1_1;
	_stage1_1->setPlayerLink(_player);

	_stage1_Boss = new stage1_Boss;
	_stage1_Boss->setPlayerLink(_player);

	_endingScene = new endingScene;



	//	======	씬 추가 ======
	SCENEMANAGER->addScene("introScene",_introScene);
	SCENEMANAGER->addScene("mainmenu", _mainmenu);
	SCENEMANAGER->addScene("mapEditor", _mapEditor);
	SCENEMANAGER->addScene("testStage", _testStage);
	SCENEMANAGER->addScene("stage1_1", _stage1_1);
	SCENEMANAGER->addScene("stage1_Boss", _stage1_Boss);
	SCENEMANAGER->addScene("endingScene", _endingScene);

	SCENEMANAGER->addScene("home", _home);

	SCENEMANAGER->changeScene("introScene");	
	//SCENEMANAGER->changeScene("endingScene");		//	체인지 해준다.
	

	return S_OK;
}


void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	OPTIONMANAGER->update();
	KEYANIMANAGER->update();

	//if (_stage1_1->getIsOneSavePlayerHp() == false)
	//{
	//	_savePlayerHp = _stage1_1->getPlayerHp();
	//	_stage1_Boss->setPlayerStartHp(_savePlayerHp);
	//}
}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);


	SCENEMANAGER->render();
	OPTIONMANAGER->render();



	//TIMEMANAGER->render(getMemDC());
	//===========================================================
	IMAGEMANAGER->findImage("backBuffer")->render(getHDC(), 0, 0);
}

