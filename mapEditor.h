#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

/* ======타일 셋 추가할때 해야할 거======
1.	변수선언
	tile* _earthTileSample[14][14 * 4];		샘플이미지[프레임Y][프레임X] -> 타일별로 프레임 끊음
	POINT _earthTileFrameIdx[2][4];			샘플페이지 넘길때 한 페이지의 시작-끝 프레임인덱스 숫자로 저장

2.	이닛에 이미지매니저 프레임이미지 추가.
3.	이닛에 초기화함수 맹글어. 

4.	이넘 추가
5.	밑에 함수들에 다 추가 -> 배열로 고쳐야하는데 ㅠㅠㅠ

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
		//CASTLEOBJ3,		//	울타리 추가시 해제
		CASTLEOBJ_KINDS_END,

	};

	enum E_EARTHTILE_KINDS {	//	_curTileSampleIdx
		EARTHTILE1 = 0,
		EARTHTILE2,
		EARTHTILE3,
		EARTHTILE4,
		EARTHTILE_KINDS_END,
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

	//	======= 샘플들 시작~! ==========
	tile* _castleTileSample[12][22];
	POINT _castleTileFrameIdx[2][4];	// [시작/끝][종류]

	tile* _castleObjSample[12][23];
	POINT _castleObjFrameIdx[2][3];		// [시작/끝][종류]

	tile* _earthTileSample[14][14 * 4];
	POINT _earthTileFrameIdx[2][4];

	tile* _earthObjSample[14][14 * 4];
	POINT _eartObjFrameIdx[2][4];

	//=========== 샘플 data 끗 =============

	

	image* _frame;
	tagImgSet _buttons[14];
	tagImgSet _arrowButtons[2][7];
	tagButtons _kindButtons[3][5];	//[타일/오브제/유닛] [캐슬/아이스/파이어/어스/커먼]
	
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
	void InitSampleEarthTile();	//	샘플 프레임, 이미지, 개별 속성입력 + 타일셋 종류별 프레임갯수
	void InitSampleEarthObj();


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
	void TileInfoRender();		
	void AreaIdxRender();		

	
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

