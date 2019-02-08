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
		//CASTLEOBJ3,		//	울타리 추가시 해제
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

	//	======= 샘플들 시작~! ==========
	tile* _castleTileSample[12][22];
	POINT _castleTileFrameIdx[2][4];	// [시작/끝][종류]

	tile* _castleObjSample[12][23];
	POINT _castleObjFrameIdx[2][3];		// [시작/끝][종류]

	//=========== 샘플 data 끗 =============

	

	image* _frame;
	tagImgSet _buttons[14];
	tagImgSet _arrowButtons[2][7];
	
	RECT _sampleRc[14][14];
	image* _sampleMask;

	int _curSampleKind;		//	타일/오브젝트/유닛
	int _curTileKind;		//	캐슬/불/..
	int _curObjKind;		//	캐슬/불/..
	int _curUnitKind;		//	캐슬/불/..
	int _curTileSampleIdx;	//	좌우클릭으로 몇번쨰 샘플인지?



	int _curAreaIdx;
	int _curMapIdx;

	
	bool _isAreaMode;
	bool _isAutoFill;
	bool _isErase;			//	오브제/타일/유닛 구분할것
	bool _isEraseTile;
	bool _isEraseObj;
	bool _isEraseUnit;


	POINT _cursorSampleIdx[2];		//	시작점, 끝점
	POINT _cursorMapIdx;			//	시작점
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

	void InitSampleCastleTile();	//	샘플 프레임, 이미지, 개별 속성입력 + 타일셋 종류별 프레임갯수
	void InitSampleCastleObj();


	void OverlayClickFunc();
	void ArrowClickFunc();			//--- 타일/오브제 추가할때마다 수정필요 ---
	void EraseMapX();
	void EraseMapY();
	void AddMapX();
	void AddMapY();

	void CursorGetTileInfoFunc();

	//	렌더들 모음
	void SampleRender();			//--- 타일/오브제 추가할때마다 수정필요 ---
	void SampleSelectedRectRender();
	void TextNumberRender();
	void TileInfoRender();		//	오브제 내용 추가요망

	
	void CursorSampleSelectFunc();
	void CursorClickOnMap();
	void CursorAdjustOnMap();	//	현재 샘플맵에 따라, sampleidx적용하여 설정 //--- 타일/오브제 추가할때마다 수정필요 ---
	void CursorEraseMap(tile * mapTile);
	void CursorEraseTile(tile* mapTile);
	void CursorEraseObj(tile* mapTile);
	void TransTileSampleToMap(tile* sampleTile, tile* mapTile);
	void TransObjSampleToMap(tile* sampleTile, tile* mapTile);
	
	void CamMove();

	void SaveFunc();
	void LoadFunc();


};

