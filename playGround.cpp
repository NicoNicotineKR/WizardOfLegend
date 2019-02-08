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

	//	======	�縸 �׽�Ʈ�� ======
	//_mapEditor = new mapEditor;
	_testStage = new testStage;

	//	======	���� �׽�Ʈ�� ======
	SCENEMANAGER->addScene("introScene",_introScene);
	SCENEMANAGER->addScene("mainmenu", _mainmenu);
	//SCENEMANAGER->addScene("mapEditor", _mapEditor);		//	�׽�Ʈ�غ� �� �߰��ϰ�
	SCENEMANAGER->addScene("testStage", _testStage);
	SCENEMANAGER->changeScene("introScene");					//	ü���� ���ش�.

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
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	SCENEMANAGER->render();
	OPTIONMANAGER->render();
	
	//===========================================================
	IMAGEMANAGER->findImage("backBuffer")->render(getHDC(), 0, 0);
}

