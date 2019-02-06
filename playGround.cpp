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

	//_introScene = new introScene;
	

	//	======	재만 테스트용 ======
	_mapEditor = new mapEditor;




	//	======	공유 테스트용 ======
	SCENEMANAGER->addScene("mapEditor", _mapEditor);		//	테스트해볼 씬 추가하고
	SCENEMANAGER->changeScene("mapEditor");					//	체인지 해준다.

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

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	SCENEMANAGER->render();
	
	//===========================================================
	IMAGEMANAGER->findImage("backBuffer")->render(getHDC(), 0, 0);
}

