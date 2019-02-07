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
	enum E_ARROW_BUTTONS {
		ARROW_AREAMODE,
		ARROW_MAPIDX,
		ARROW_MAPSIZEX,
		ARROW_MAPSIZEY,
		ARROW_TILES,
		ARROW_OBJECTS,
		ARROW_UNITS,
		E_ARROW_END,
	};
	enum E_SELECT_KIND {
		SELECT_TILE = 0,

		SELECT_KIND_END,
	};
	enum E_CASTLETILE_KINDS {
		CASTLETILE1 = 0,
		CASTLETILE2,
		CASTLETILE3,
		CASTLETILE4,
		CASTLETILE_KINDS_END,
	};
	enum E_TILE_KINDS
	{
		CASTLE_TILE = 0,


		TILE_KINDS_END,
	};
	enum E_OBJ_KINDS
	{
		CASTLE_OBJ = 0,


		OBJ_KINDS_END,
	};
	enum E_UNIT_KINDS
	{
		CASTLE_UNIT = 0,


		UNIT_KINDS_END,
	};




	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	int _tileNumX;
	int _tileNumY;

	vvMap		_vvMap;
	RECT _mapZoneRc;

	//	======= ���õ� ����~! ==========
	tile* _castleTileSample[12][22];
	POINT _castleTileFrameIdx[2][4];	// [����/��][����]

	tile* _castleObjSample;

	image* _frame;
	tagImgSet _buttons[13];
	tagImgSet _arrowButtons[2][7];
	
	RECT _sampleRc[14][14];
	image* _sampleMask;

	int _curSampleKind;		//	Ÿ��/������Ʈ/����
	int _curTileKind;		//	ĳ��/��/..
	int _curObjKind;		//	ĳ��/��/..
	int _curUnitKind;		//	ĳ��/��/..
	int _curTileSampleIdx;	//	�¿�Ŭ������ ����� ��������?



	int _curAreaIdx;
	int _curMapIdx;


	
	
	


	bool _isAreaMode;
	bool _isAutoFill;
	bool _isErase;

	POINT _cursorSampleIdx[2];		//	������, ����
	POINT _cursorMapIdx;			//	������
	tile* _currentCursorTileInfo;

	bool _isClickDown;
	bool _isCursorSelected;

	POINT _camLeftTop;

	//=========== ���� data ================
	



	const int ARROWBUTTON_GAP = 15;
	const POINT SAMPLEZONE_CENTER = { 1375,225 };
	const int SAMPLE_MASK_ALPHA = 120;
	const int CAM_MOVESPD = 2;

public:
	mapEditor();
	~mapEditor();

	HRESULT init();
	void release();
	void update();
	void render();

	void SetNewMap(int tilenumX, int tileNumY);
	void SetNewTile(tile* tile, int idxX, int idxY);
	void SetNewSampleTile(tile* tile, int idxX, int idxY);

	void InitButtons();
	void InitArrows();
	void InitSampleRc();

	void InitSampleCastleTile();	//	���� ������, �̹���, ���� �Ӽ��Է� + Ÿ�ϼ� ������ �����Ӱ���


	void OverlayClickFunc();
	void ArrowClickFunc();
	void EraseMapX();
	void EraseMapY();
	void AddMapX();
	void AddMapY();

	void CursorGetTileInfoFunc();

	//	������ ����
	void SampleRender();
	void SampleSelectedRectRender();
	void TextNumberRender();
	void TileInfoRender();

	
	void CursorSampleSelectFunc();
	void CursorClickOnMap();
	void CursorAdjustOnMap();	//	���� ���øʿ� ����, sampleidx�����Ͽ� ����
	void CursorEraseMap(tile * mapTile);
	void TransTileSampleToMap(tile* sampleTile, tile* mapTile);
	
	void CamMove();

	void SaveFunc();
	void LoadFunc();


};

