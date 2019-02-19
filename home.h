#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"

#include "dialogueMaker.h"
#include "npcMgr.h"


class home : public gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	typedef vector<objectInfo*> vObjects;

	stageMapLoader* _stageMapLoader;
	vvMap		_vvMap;
	vObjects	_vObjects;

	player*	_player;
	enemyMgr* _enemyMgr;
	dialogueMaker* _dialogueMaker;
	npcMgr* _nm;


	int _tileNumX;
	int _tileNumY;

	bool _allStop;

public:
	home();
	~home();

	HRESULT init();
	void release();
	void update();
	void render();

	//ÇÔ¼öµé
	void TileMapRender();
	void VObjectRender();
};

