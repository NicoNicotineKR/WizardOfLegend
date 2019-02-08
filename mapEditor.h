#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

class mapEditor : public gameNode
{
private:
	enum E_BUTTONS {
		AREAMODE = 0,
		ERASE_TILE,
		ERASE_OBJ,
		//ERASE_UNIT,
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
	enum E_SELECT_KIND {	// _curSampleKind
		SELECT_TILE = 0,
		SELECT_OBJ,
		SELECT_UNIT,

		SELECT_KIND_END,
	};
	enum E_CASTLETILE_KINDS {
		CASTLETILE1 = 0,
		CASTLETILE2,
		CASTLETILE3,
		CASTLETILE4,
		CASTLETILE_KINDS_END,
	};
	enum E_CASTLEOBJ_KINDS {
		CASTLEOBJ1 = 0,
		CASTLEOBJ2,
		//CASTLEOBJ3,		//	��Ÿ�� �߰��� ����
		CASTLEOBJ_KINDS_END,

	};
	enum E_TILE_KINDS	//_curTileKind
	{
		CASTLE_TILE = 0,


		TILE_KINDS_END,
	};
	enum E_OBJ_KINDS	//_curObjKind
	{
		CASTLE_OBJ = 0,


		OBJ_KINDS_END,
	};
	enum E_UNIT_KINDS	//	_curUnitKind
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

	tile* _castleObjSample[12][23];
	POINT _castleObjFrameIdx[2][3];		// [����/��][����]

	//=========== ���� data �� =============

	

	image* _frame;
	tagImgSet _buttons[14];
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
	bool _isErase;			//	������/Ÿ��/���� �����Ұ�
	bool _isEraseTile;
	bool _isEraseObj;
	bool _isEraseUnit;


	POINT _cursorSampleIdx[2];		//	������, ����
	POINT _cursorMapIdx;			//	������
	tile* _currentCursorTileInfo;

	bool _isClickDown;
	bool _isCursorSelected;

	POINT _camLeftTop;

	

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
	void SetNewSampleObj(tile* tile, int idxX, int idxY);

	void InitButtons();
	void InitArrows();
	void InitSampleRc();

	void InitSampleCastleTile();	//	���� ������, �̹���, ���� �Ӽ��Է� + Ÿ�ϼ� ������ �����Ӱ���
	void InitSampleCastleObj();


	void OverlayClickFunc();
	void ArrowClickFunc();			//--- Ÿ��/������ �߰��Ҷ����� �����ʿ� ---
	void EraseMapX();
	void EraseMapY();
	void AddMapX();
	void AddMapY();

	void CursorGetTileInfoFunc();

	//	������ ����
	void SampleRender();			//--- Ÿ��/������ �߰��Ҷ����� �����ʿ� ---
	void SampleSelectedRectRender();
	void TextNumberRender();
	void TileInfoRender();		//	������ ���� �߰����

	
	void CursorSampleSelectFunc();
	void CursorClickOnMap();
	void CursorAdjustOnMap();	//	���� ���øʿ� ����, sampleidx�����Ͽ� ���� //--- Ÿ��/������ �߰��Ҷ����� �����ʿ� ---
	void CursorEraseMap(tile * mapTile);
	void CursorEraseTile(tile* mapTile);
	void CursorEraseObj(tile* mapTile);
	void TransTileSampleToMap(tile* sampleTile, tile* mapTile);
	void TransObjSampleToMap(tile* sampleTile, tile* mapTile);
	
	void CamMove();

	void SaveFunc();
	void LoadFunc();


};

