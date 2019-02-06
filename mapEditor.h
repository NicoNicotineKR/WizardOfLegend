#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

class mapEditor : public gameNode
{
private:
	enum E_BUTTONS {
		AREAMODE = 0,
		AUTOFILL,
		SELECT,
		INFO,
		SAVE,
		LOAD,
		MAPIDX,
		XY,
		MAPSIZE,
		TILES,
		OBJECTS,
		UNITS,
		ERASE,
		E_BUTTONS_END,

	};


	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	int _tileNumX;
	int _tileNumY;

	vvMap		_vvMap;
	tagImgSet	_castleTileSample;
	tagImgSet	_castleObjSample;

	image* _frame;
	tagImgSet _buttons[13];
	bool _isButtonsOverlay[13];




public:
	mapEditor();
	~mapEditor();

	HRESULT init();
	void release();
	void update();
	void render();

	void SetNewMap(int tilenumX, int tileNumY);
	void SetNewTile(tile* tile, int idxX, int idxY);

	void InitButtons();


};

