#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

/* ======Ÿ�� �� �߰��Ҷ� �ؾ��� ��======
1.	��������
	tile* _earthTileSample[14][14 * 4];		�����̹���[������Y][������X] -> Ÿ�Ϻ��� ������ ����
	POINT _earthTileFrameIdx[2][4];			���������� �ѱ涧 �� �������� ����-�� �������ε��� ���ڷ� ����

2.	�̴ֿ� �̹����Ŵ��� �������̹��� �߰�.
3.	�̴ֿ� �ʱ�ȭ�Լ� �ͱ۾�.

4.	�̳� �߰�
5.	�ؿ� �Լ��鿡 �� �߰� -> �迭�� ���ľ��ϴµ� �ФФ�

*/

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
	enum E_CASTLETILE_KINDS {	//	_curTileSampleIdx
		CASTLETILE1 = 0,
		CASTLETILE2,
		CASTLETILE3,
		CASTLETILE4,
		CASTLETILE_KINDS_END,
	};
	enum E_CASTLEOBJ_KINDS {	//	_curTileSampleIdx
		CASTLEOBJ1 = 0,
		CASTLEOBJ2,
		//CASTLEOBJ3,		//	��Ÿ�� �߰��� ����
		CASTLEOBJ_KINDS_END,

	};

	enum E_EARTHTILE_KINDS {	//	_curTileSampleIdx
		EARTHTILE1 = 0,
		EARTHTILE2,
		EARTHTILE3,
		EARTHTILE4,
		EARTHTILE_KINDS_END,
	};

	enum E_EARTHOBJ_KINDS {	//	_curTileSampleIdx
		EARTHOBJ1 = 0,
		EARTHOBJ2,
		EARTHOBJ3,
		EARTHOBJ4,
		EARTHOBJ_KINDS_END,
	};

	//�߰� - ������
	enum E_ICETILE_KINDS {	//	_curTileSampleIdx
		ICETILE1 = 0,
		ICETILE2,
		ICETILE3,
		ICETILE4,
		ICETILE_KINDS_END,
	};

	enum E_ICEOBJ_KINDS {	//	_curTileSampleIdx
		ICEOBJ1 = 0,
		ICEOBJ2,
		ICEOBJ3,
		ICEOBJ4,
		ICEOBJ_KINDS_END,
	};

	enum E_TILE_KINDS	//_curTileKind
	{
		CASTLE_TILE = 0,
		ICE_TILE,
		FIRE_TILE,
		EARTH_TILE,
		COMMON_TILE,


		TILE_KINDS_END,
	};
	enum E_OBJ_KINDS	//_curObjKind
	{
		CASTLE_OBJ = 0,
		ICE_OBJ,
		FIRE_OBJ,
		EARTH_OBJ,
		COMMON_OBJ,


		OBJ_KINDS_END,
	};
	enum E_UNIT_KINDS	//	_curUnitKind
	{
		CASTLE_UNIT = 0,
		ICE_UNIT,
		FIRE_UNIT,
		EARTH_UNIT,
		COMMON_UNIT,


		UNIT_KINDS_END,
	};
	struct tagButtons {
		image* img;
		POINT pos;
		RECT rc;
		bool isOn;
	};
	enum E_KINDSBUTTONS {	//	_kindButtons[][E_KINDSBUTTONS]
		BTN_CASTLE = 0,
		BTN_ICE,
		BTN_FIRE,
		BTN_EARTH,
		BTN_COMMON,
		BTN_KINDS_END,
	};




	int _tileNumX;
	int _tileNumY;

	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	vvMap		_vvMap;
	RECT _mapZoneRc;

	//	======= ���õ� ����~! ==========

	tile* _totalSamples[3][5][14][56];	//[Ÿ��/������Ʈ/����] [castle/earth...] [y][x];
	//		[_curSampleKind][_curTileKind/_curObjKind/_curUnitKind][][]
	POINT _totalFrameIdx[3][5][2][5];
	//[Ÿ��/������Ʈ/����] [castle/earth...] [����/��][������ ��];
	//		[_curSampleKind][_curTileKind/_curObjKind/_curUnitKind][0/1][_curTileSampleIdx]


	tile* _castleTileSample[12][22];
	POINT _castleTileFrameIdx[2][4];	// [����/��][����]

	tile* _castleObjSample[12][23];
	POINT _castleObjFrameIdx[2][3];		// [����/��][����]

	tile* _earthTileSample[14][14 * 4];
	POINT _earthTileFrameIdx[2][4];

	tile* _earthObjSample[14][14 * 4];
	POINT _eartObjFrameIdx[2][4];

	//�߰� - ������
	tile* _IceTileSample[14][14 * 4];
	POINT _IceTileFrameIdx[2][4];	// [����/��][����]

	//=========== ���� data �� =============



	image* _frame;
	tagImgSet _buttons[14];
	tagImgSet _arrowButtons[2][7];
	tagButtons _kindButtons[3][5];	//[Ÿ��/������/����] [ĳ��/���̽�/���̾�/�/Ŀ��]

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


	int _mapResizeCount;


	const int ARROWBUTTON_GAP = 15;
	const POINT SAMPLEZONE_CENTER = { 1375,225 };
	const int SAMPLE_MASK_ALPHA = 120;
	const int CAM_MOVESPD = 4;
	const int RESIZE_COUNTFRAME = 5;		//	��ũ�� �������� �Ҷ� ī��Ʈ�� ������
	const int PREVIEW_ALPHA = 200;			//	�̸����� ���İ�

	const int INFO_SHOW_X = 1030;			//	Ÿ������ ��� X��ǥ

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
	void InitSampleEarthTile();	//	���� ������, �̹���, ���� �Ӽ��Է� + Ÿ�ϼ� ������ �����Ӱ���
	void InitSampleEarthObj();

	//�߰� - ������
	void InitSampleIceTile();	//	���� ������, �̹���, ���� �Ӽ��Է� + Ÿ�ϼ� ������ �����Ӱ���
	void InitSampleIceObj();

	void OverlayClickFunc();
	void ArrowClickFunc();			//--- Ÿ��/������ �߰��Ҷ����� �����ʿ� ---
	void EraseMapX();
	void EraseMapY();
	void AddMapX();
	void AddMapY();

	void CursorGetTileInfoFunc();

	//	������ ����
	void SampleRender();			// (���� ���� ���ص���) --- Ÿ��/������ �߰��Ҷ����� �����ʿ� --- 
	void SampleSelectedRectRender();
	void TextNumberRender();
	void TileInfoRender();
	void AreaIdxRender();
	void PreviewSampleRender();		//--- Ÿ��/������ �߰��Ҷ����� �����ʿ� --- 


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

	void MapResizeCountDelayFunc();
	bool IsRdyToResize();

	//�� ������
	void LoadView();
};

