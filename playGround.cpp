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

	// ====== ���� �׽�Ʈ�� =====
	_introScene = new introScene;
	_mainmenu = new mainmenu;
	_home = new home;
	_player = new player;
	_home->setPlayerLink(_player);
	//	======	�縸 �׽�Ʈ�� ======
	//_mapEditor = new mapEditor;
	_testStage = new testStage;
	_stage1_1 = new stage1_1;
	_stage1_1->setPlayerLink(_player);
	//	======	���� �׽�Ʈ�� ======
	SCENEMANAGER->addScene("introScene",_introScene);
	SCENEMANAGER->addScene("mainmenu", _mainmenu);
	//SCENEMANAGER->addScene("mapEditor", _mapEditor);		//	�׽�Ʈ�غ� �� �߰��ϰ�
	SCENEMANAGER->addScene("testStage", _testStage);
	SCENEMANAGER->addScene("stage1_1", _stage1_1);
	SCENEMANAGER->addScene("home", _home);

	SCENEMANAGER->changeScene("introScene");	
	//	ü���� ���ش�.

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

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	
	SCENEMANAGER->render();
	OPTIONMANAGER->render();


	TIMEMANAGER->render(getMemDC());
	//===========================================================
	IMAGEMANAGER->findImage("backBuffer")->render(getHDC(), 0, 0);
}

