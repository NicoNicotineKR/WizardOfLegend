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

	enum E_EARTHOBJ_KINDS {	//	_curTileSampleIdx
		EARTHOBJ1 = 0,
		EARTHOBJ2,
		EARTHOBJ3,
		EARTHOBJ4,
		EARTHOBJ_KINDS_END,
	};

	//추가 - 유형우
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

	//	======= 샘플들 시작~! ==========

	tile* _totalSamples[3][5][14][56];	//[타일/오브젝트/유닛] [castle/earth...] [y][x];
	//		[_curSampleKind][_curTileKind/_curObjKind/_curUnitKind][][]
	POINT _totalFrameIdx[3][5][2][5];
	//[타일/오브젝트/유닛] [castle/earth...] [시작/끝][프레임 수];
	//		[_curSampleKind][_curTileKind/_curObjKind/_curUnitKind][0/1][_curTileSampleIdx]


	tile* _castleTileSample[12][22];
	POINT _castleTileFrameIdx[2][4];	// [시작/끝][종류]

	tile* _castleObjSample[12][23];
	POINT _castleObjFrameIdx[2][3];		// [시작/끝][종류]

	tile* _earthTileSample[14][14 * 4];
	POINT _earthTileFrameIdx[2][4];

	tile* _earthObjSample[14][14 * 4];
	POINT _eartObjFrameIdx[2][4];

	//추가 - 유형우
	tile* _IceTileSample[14][14 * 4];
	POINT _IceTileFrameIdx[2][4];	// [시작/끝][종류]

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


	int _mapResizeCount;


	const int ARROWBUTTON_GAP = 15;
	const POINT SAMPLEZONE_CENTER = { 1375,225 };
	const int SAMPLE_MASK_ALPHA = 120;
	const int CAM_MOVESPD = 4;
	const int RESIZE_COUNTFRAME = 5;		//	맵크기 리사이즈 할때 카운트할 프레임
	const int PREVIEW_ALPHA = 200;			//	미리보기 알파값

	const int INFO_SHOW_X = 1030;			//	타일정보 출력 X좌표

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

	//추가 - 유형우
	void InitSampleIceTile();	//	샘플 프레임, 이미지, 개별 속성입력 + 타일셋 종류별 프레임갯수
	void InitSampleIceObj();

	void OverlayClickFunc();
	void ArrowClickFunc();			//--- 타일/오브제 추가할때마다 수정필요 ---
	void EraseMapX();
	void EraseMapY();
	void AddMapX();
	void AddMapY();

	void CursorGetTileInfoFunc();

	//	렌더들 모음
	void SampleRender();			// (이제 수정 안해도됨) --- 타일/오브제 추가할때마다 수정필요 --- 
	void SampleSelectedRectRender();
	void TextNumberRender();
	void TileInfoRender();
	void AreaIdxRender();
	void PreviewSampleRender();		//--- 타일/오브제 추가할때마다 수정필요 --- 


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

	void MapResizeCountDelayFunc();
	bool IsRdyToResize();

	//길 보여짐
	void LoadView();
};

