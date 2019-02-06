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
	

	//	======	�縸 �׽�Ʈ�� ======
	_mapEditor = new mapEditor;




	//	======	���� �׽�Ʈ�� ======
	SCENEMANAGER->addScene("mapEditor", _mapEditor);		//	�׽�Ʈ�غ� �� �߰��ϰ�
	SCENEMANAGER->changeScene("mapEditor");					//	ü���� ���ش�.

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

