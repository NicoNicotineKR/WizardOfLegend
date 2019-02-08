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

	//	======	재만 테스트용 ======
	//_mapEditor = new mapEditor;
	_testStage = new testStage;

	//	======	공유 테스트용 ======
	SCENEMANAGER->addScene("introScene",_introScene);
	SCENEMANAGER->addScene("mainmenu", _mainmenu);
	//SCENEMANAGER->addScene("mapEditor", _mapEditor);		//	테스트해볼 씬 추가하고
	SCENEMANAGER->addScene("testStage", _testStage);
	SCENEMANAGER->changeScene("introScene");					//	체인지 해준다.

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

