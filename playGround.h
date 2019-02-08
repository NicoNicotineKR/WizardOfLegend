#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "testStage.h"
#include "mainmenu.h"



class playGround : public gameNode
{
private:
    introScene* _introScene;
	mainmenu* _mainmenu;
	testStage* _testStage;



	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

