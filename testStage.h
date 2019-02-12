#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "aStar.h"
#include "player.h"
#include "enemyMgr.h"

class testStage : public gameNode
{
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	vvMap _vvMap;
	int _tileNumX;
	int _tileNumY;

	aStar* _aStar;

	list<POINT> _myWay;
	list<POINT>::iterator _imyWay;

	RECT _test;
	player* _player;

	enemyMgr* _em;
	
public:
	testStage();
	~testStage();

	HRESULT init();
	void release();
	void update();
	void render();


	void RenderMap();


	void LoadMap();



};

