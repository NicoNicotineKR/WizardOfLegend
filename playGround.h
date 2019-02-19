#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "testStage.h"
#include "mainmenu.h"
#include "stage1_1.h"
#include "home.h"
#include "player.h"


class playGround : public gameNode
{
private:
    introScene* _introScene;
	mainmenu* _mainmenu;
	testStage* _testStage;
	stage1_1* _stage1_1;
	home* _home;
	player* _player;


	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

