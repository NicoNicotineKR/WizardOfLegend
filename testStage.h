#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
class testStage : public gameNode
{
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	vvMap _vvMap;
	int _tileNumX;
	int _tileNumY;




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

