#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "mapEditor.h"
#include "testStage.h"


class playGround : public gameNode
{
private:
     //introScene* _introScene;
	mapEditor* _mapEditor;

	testStage* _testStage;

	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

