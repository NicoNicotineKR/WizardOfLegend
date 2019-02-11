#pragma once
#include "gameNode.h"
class hpUI : public gameNode
{

public:
	hpUI();
	~hpUI();

	HRESULT init();
	void release();
	void update();
	void render();

};

