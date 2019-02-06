#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "mapEditor.h"


class playGround : public gameNode
{
private:
     //introScene* _introScene;
	mapEditor* _mapEditor;
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

