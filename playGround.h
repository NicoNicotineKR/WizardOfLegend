#pragma once
#include "gameNode.h"
#include "introScene.h"


class playGround : public gameNode
{
private:
     //introScene* _introScene;
	
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

