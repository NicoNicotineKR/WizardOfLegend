#pragma once
#include "gameNode.h"
#include "skillIconList.h"
class skillCooldownUI : public gameNode
{
private:
	skillIconList* _iconList;


	

public:
	skillCooldownUI();
	~skillCooldownUI();

	HRESULT init();
	void release();
	void update();
	void render();


	

};

