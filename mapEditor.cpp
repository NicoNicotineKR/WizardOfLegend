#include "stdafx.h"
#include "mapEditor.h"
#pragma warning(disable: 4996)

mapEditor::mapEditor()
{
}


mapEditor::~mapEditor()
{
}

HRESULT mapEditor::init()
{
	//	이미지매니저
	IMAGEMANAGER->addFrameImage("tileCastle", "images/map/CastleBaseTileSet.bmp", 704, 384, 22, 12, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objCastle", "images/map/CastleBaseObjSet.bmp", 736, 384, 23, 12, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("tileEarth", "images/map/EarthBaseTileSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objEarth", "images/map/EarthBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	//추가 - 유형우
	IMAGEMANAGER->addFrameImage("tileIce", "images/map/IceBaseTileSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objIce", "images/map/IceBaseObjSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("tileFire", "images/map/FireBaseTileSet.bmp", 1792, 448, 56, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objFire", "images/map/FireBaseObjSet.bmp", 896, 448, 28, 14, true, 0xFF00FF);

	//추가 - 유형우
	IMAGEMANAGER->addFrameImage("tileCommon", "images/map/CommonBaseTileSet.bmp", 3584, 448, 112, 14, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objCommon", "images/map/CommonBaseObjSet.bmp", 3584, 448, 112, 14, true, 0xFF00FF);

	//추가 - 에너미
	IMAGEMANAGER->addFrameImage("enemyCommon", "images/map/enemyUnitSet.bmp", 384, 160, 12, 5, true, 0xFF00FF);

	IMAGEMANAGER->addImage("mapEditorFrame", "images/mapEditor/mapEditorFrame.bmp", 1600, 900, true, 0xFF00FF);
	IMAGEMANAGER->addImage("sampleMask", "images/mapEditor/sampleMask.bmp", 32, 32, false, 0x000000);

	//	버튼 이미지 imagemanager 넣고
	{
		IMAGEMANAGER->addFrameImage("btn_areamode", "images/mapEditor/btn_areamode.bmp", 141, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_autofill", "images/mapEditor/btn_autofill.bmp", 105, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_eraseTile", "images/mapEditor/btn_eraseTile.bmp", 125, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_eraseObj", "images/mapEditor/btn_eraseObj.bmp", 120, 56, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_eraseUnit", "images/mapEditor/btn_eraseUnit.bmp", 134, 44, 1, 2, false, 0x000000);

		IMAGEMANAGER->addFrameImage("btn_select", "images/mapEditor/btn_select.bmp", 77, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_info", "images/mapEditor/btn_info.bmp", 55, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_save", "images/mapEditor/btn_save.bmp", 61, 42, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_load", "images/mapEditor/btn_load.bmp", 69, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_mapidx", "images/mapEditor/btn_mapidx.bmp", 105, 56, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_xy", "images/mapEditor/btn_xy.bmp", 139, 21, 1, 1, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_mapsize", "images/mapEditor/btn_mapsize.bmp", 115, 56, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_tiles", "images/mapEditor/btn_tiles.bmp", 64, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_objects", "images/mapEditor/btn_objects.bmp", 97, 56, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_units", "images/mapEditor/btn_units.bmp", 72, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_erase", "images/mapEditor/btn_erase.bmp", 72, 42, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_arrow", "images/mapEditor/btn_arrow.bmp", 56, 56, 2, 2, true, 0xFF00FF);

		IMAGEMANAGER->addFrameImage("btn_castle", "images/mapEditor/btn_castle.bmp", 73, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_ice", "images/mapEditor/btn_ice.bmp", 37, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_fire", "images/mapEditor/btn_fire.bmp", 45, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_earth", "images/mapEditor/btn_earth.bmp", 67, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_common", "images/mapEditor/btn_common.bmp", 113, 30, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_roadView", "images/mapEditor/btn_roadView.bmp", 121, 42, 1, 2, true, 0xFF00FF);
	}

	//	기본 크기
	_tileNumX = 30;
	_tileNumY = 30;
	_mapZoneRc = { 0,0,1024,768 };


	//	기본 맵타일 셋팅
	_vvMap.clear();
	for (int i = 0; i < _tileNumY; i++) {
		vLine tmpLine;
		tmpLine.clear();
		for (int j = 0; j < _tileNumX; j++) {
			tile* tmpTile = new tile;
			SetNewTile(tmpTile, j, i);
			tmpLine.push_back(tmpTile);
		}
		_vvMap.push_back(tmpLine);
	}

	_frame = IMAGEMANAGER->findImage("mapEditorFrame");
	InitButtons();
	InitArrows();		//	애로우는 버튼따라 설정되니까, 버튼먼저 이닛하고 할것
	InitSampleRc();
	_sampleMask = IMAGEMANAGER->findImage("sampleMask");

	//	샘플종류
	_curSampleKind = SELECT_TILE;
	_buttons[TILES].frameY = 1;
	_curTileKind = CASTLE_TILE;
	_curObjKind = CASTLE_OBJ;
	_curUnitKind = COMMON_UNIT;
	_curTileSampleIdx = 0;

	//	=== tileCastle 샘플 생성 ===
	InitSampleCastleTile();
	InitSampleCastleObj();
	InitSampleEarthTile();
	InitSampleEarthObj();

	//추가 - 유형우
	InitSampleIceTile();
	InitSampleIceObj();

	InitSampleFireTile();
	InitSampleFireObj();

	InitSampleCommonTile();
	InitSampleCommonObj();

	InitSampleCommonEnemy();



	_isAreaMode = false;
	_isAutoFill = false;
	_isErase = false;
	_isEraseTile = false;
	_isEraseObj = false;
	_isEraseUnit = false;

	_cursorSampleIdx[0] = { 0,0 };
	_cursorSampleIdx[1] = { 0,0 };
	_currentCursorTileInfo = new tile;

	_isClickDown = false;
	_isCursorSelected = false;

	_camLeftTop = { 0,0 };

	_mapResizeCount = 0;
	_roadViewImg = IMAGEMANAGER->findImage("btn_roadView");
	_roadViewFrameY = 1;
	_roadViewOn = false;

	//로드뷰 - [길]
	_roadViewRc = RectMakeCenter(WINSIZEX / 2 + 288, WINSIZEY - 65, 120, 60);

	return S_OK;
}

void mapEditor::release()
{

	_currentCursorTileInfo = nullptr;

	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {
			SAFE_DELETE(_vvMap[i][j]);
			_vvMap[i][j] = nullptr;
		}
		_vvMap[i].clear();
	}
	_vvMap.clear();

	

	//IMAGEMANAGER->deleteImage("");		//	이거 다해줘야함

	
}

void mapEditor::update()
{
	OverlayClickFunc();
	CursorSampleSelectFunc();
	ArrowClickFunc();
	CursorClickOnMap();

	CursorGetTileInfoFunc();

	CamMove();

	MapResizeCountDelayFunc();

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeScene("mainmenu");
	}

	// 로드뷰 - [길]
	{
		_cameraIdxX = _camLeftTop.x / 32;
		_cameraIdxY = _camLeftTop.y / 32;
		LoadView();
	}

}

void mapEditor::render()
{

	//타일 출력 - (시퀀스 렌더링)
	for (int i = _cameraIdxY - 2; i < _cameraIdxY + 25; i++)
	{
		for (int j = _cameraIdxX - 2; j < _cameraIdxX + 34; j++)
		{
			if (j < 0)continue;
			if (i < 0)continue;
			if (j >= _tileNumX)continue;
			if (i >= _tileNumY)continue;

			_vvMap[i][j]->CamRender(_camLeftTop.x, _camLeftTop.y);
		}
	}

	//타일 출력 - (시퀀스 렌더링)
	//	areaIdx
	if (_isAreaMode) {

		AreaIdxRender();
	}



	//프레임이미지 출력
	_frame->render(getMemDC(), 0, 0);

	//버튼들 출력
	for (int i = 0; i < E_BUTTONS_END; i++)
	{
		_buttons[i].img->frameRender(getMemDC(), _buttons[i].rc.left, _buttons[i].rc.top, _buttons[i].frameX, _buttons[i].frameY);
	}

	//종류선택버튼 출력
	for (int i = 0; i < 3; i++) {	//	tile/obj/unit
		for (int j = 0; j < BTN_KINDS_END; j++) {
			_kindButtons[i][j].img->frameRender(getMemDC(), _kindButtons[i][j].rc.left, _kindButtons[i][j].rc.top,
				0, _kindButtons[i][j].isOn);
		}
	}

	//화살표출력
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < E_ARROW_END; j++)
		{
			_arrowButtons[i][j].img->frameRender(getMemDC(), _arrowButtons[i][j].rc.left, _arrowButtons[i][j].rc.top,
				_arrowButtons[i][j].frameX, _arrowButtons[i][j].frameY);
		}
	}


	//	샘플존 rc출력
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			//Rectangle(getMemDC(), _sampleRc[i][j]);
			HBRUSH brush;
			brush = CreateSolidBrush(RGB(150, 100, 100));
			FrameRect(getMemDC(), &_sampleRc[i][j], brush);
			DeleteObject(brush);
		}
	}

	//샘플이미지 렌더
	SampleRender();
	SampleSelectedRectRender();


	//	텍스트 숫자들 출력
	TextNumberRender();

	//	타일 Info 출력
	TileInfoRender();

	//	미리보기 출력
	if (PtInRect(&_mapZoneRc, _ptMouse)) {
		PreviewSampleRender();
	}


	//	테스트용
	char str[128];
	sprintf_s(str, "_curTileSampleIdx : %d", _curTileSampleIdx);
	TextOut(getMemDC(), 30, 30, str, strlen(str));


	//로드뷰 - [길]
	if (_roadViewOn == true)
	{
		for (int i = _cameraIdxY - 2; i < _cameraIdxY + 25; i++)
		{
			for (int j = _cameraIdxX - 2; j < _cameraIdxX + 34; j++)
			{
				if (j < 0)continue;
				if (i < 0)continue;
				if (j >= _tileNumX)continue;
				if (i >= _tileNumY)continue;

				if (_vvMap[i][j]->getIsAvailMove() == true)
				{
					char str[128];
					sprintf_s(str, "[길]");
					TextOut(getMemDC(),
						_vvMap[i][j]->getTopTileRc().left - _camLeftTop.x,
						_vvMap[i][j]->getTopTileRc().bottom - _camLeftTop.y - 20,
						str, strlen(str));
				}
			}
		}
	}
	_roadViewImg->frameRender(getMemDC(), _roadViewRc.left, _roadViewRc.top, 0, _roadViewFrameY);
}

void mapEditor::SetNewMap(int tilenumX, int tileNumY)
{
}

void mapEditor::SetNewTile(tile* tile, int idxX, int idxY)
{

	POINT tmpIdx = { idxX, idxY };
	tile->setTopIdx(tmpIdx);


	tagImgSet tmpTileSet;
	tmpTileSet.attribute = TILE_NONE;
	tmpTileSet.frameX = 0;
	tmpTileSet.frameY = 0;
	tmpTileSet.img = nullptr;
	tmpTileSet.pos.x = TOP_TILESIZE / 2 + TOP_TILESIZE * idxX;
	tmpTileSet.pos.y = TOP_TILESIZE / 2 + TOP_TILESIZE * idxY;
	tmpTileSet.rc = RectMakeCenter(tmpTileSet.pos.x, tmpTileSet.pos.y, TOP_TILESIZE, TOP_TILESIZE);
	tmpTileSet.imgKeyValue = "none";
	tile->setTopTileImageSet(tmpTileSet);



	tagImgSet tmpObjSet;
	tmpObjSet.attribute = OBJ_NONE;
	tmpObjSet.frameX = 0;
	tmpObjSet.frameY = 0;
	tmpObjSet.img = nullptr;
	tmpObjSet.pos.x = TOP_TILESIZE / 2 + TOP_TILESIZE * idxX;
	tmpObjSet.pos.y = TOP_TILESIZE / 2 + TOP_TILESIZE * idxY;
	tmpObjSet.rc = RectMakeCenter(tmpObjSet.pos.x, tmpObjSet.pos.y, TOP_TILESIZE, TOP_TILESIZE);
	tmpObjSet.imgKeyValue = "none";
	tile->setTopObjImageSet(tmpObjSet);

	tile->setIsAvailMove(false);
	tile->setParent(nullptr);

}

//	x위치만 new tile과 다름
void mapEditor::SetNewSampleTile(tile * tile, int idxX, int idxY)
{

	POINT tmpIdx = { idxX, idxY };
	tile->setTopIdx(tmpIdx);


	tagImgSet tmpTileSet;
	tmpTileSet.attribute = TILE_NONE;
	tmpTileSet.frameX = idxX;		//	타일 셋트할땐 여기에 인덱스
	tmpTileSet.frameY = idxY;
	tmpTileSet.img = nullptr;
	tmpTileSet.pos.x = 1150 + TOP_TILESIZE / 2 + TOP_TILESIZE * idxX;
	tmpTileSet.pos.y = TOP_TILESIZE / 2 + TOP_TILESIZE * idxY;
	tmpTileSet.rc = RectMakeCenter(tmpTileSet.pos.x, tmpTileSet.pos.y, TOP_TILESIZE, TOP_TILESIZE);
	tmpTileSet.imgKeyValue = "none";
	tile->setTopTileImageSet(tmpTileSet);


	tagImgSet tmpObjSet;
	tmpObjSet.attribute = OBJ_NONE;
	tmpObjSet.frameX = 0;			//	오브젝트 셋트할땐 여기에 인덱스
	tmpObjSet.frameY = 0;
	tmpObjSet.img = nullptr;
	tmpObjSet.pos.x = 1150 + TOP_TILESIZE / 2 + TOP_TILESIZE * idxX;
	tmpObjSet.pos.y = TOP_TILESIZE / 2 + TOP_TILESIZE * idxY;
	tmpObjSet.rc = RectMakeCenter(tmpObjSet.pos.x, tmpObjSet.pos.y, TOP_TILESIZE, TOP_TILESIZE);
	tmpObjSet.imgKeyValue = "none";
	tile->setTopObjImageSet(tmpObjSet);

	tile->setIsAvailMove(false);
	tile->setParent(nullptr);


}

void mapEditor::SetNewSampleObj(tile * tile, int idxX, int idxY)
{
	POINT tmpIdx = { idxX, idxY };
	//tile->setTopIdx(tmpIdx);

	tagImgSet tmpTileSet;
	tmpTileSet.attribute = TILE_NONE;
	tmpTileSet.frameX = 0;		//	타일 셋트할땐 여기에 인덱스
	tmpTileSet.frameY = 0;
	tmpTileSet.img = nullptr;
	tmpTileSet.pos.x = 1150 + TOP_TILESIZE / 2 + TOP_TILESIZE * idxX;
	tmpTileSet.pos.y = TOP_TILESIZE / 2 + TOP_TILESIZE * idxY;
	tmpTileSet.rc = RectMakeCenter(tmpTileSet.pos.x, tmpTileSet.pos.y, TOP_TILESIZE, TOP_TILESIZE);
	tmpTileSet.imgKeyValue = "none";
	tile->setTopTileImageSet(tmpTileSet);


	tagImgSet tmpObjSet;
	tmpObjSet.attribute = OBJ_NONE;
	tmpObjSet.frameX = idxX;			//	오브젝트 셋트할땐 여기에 인덱스
	tmpObjSet.frameY = idxY;
	tmpObjSet.img = nullptr;
	tmpObjSet.pos.x = 1150 + TOP_TILESIZE / 2 + TOP_TILESIZE * idxX;
	tmpObjSet.pos.y = TOP_TILESIZE / 2 + TOP_TILESIZE * idxY;
	tmpObjSet.rc = RectMakeCenter(tmpObjSet.pos.x, tmpObjSet.pos.y, TOP_TILESIZE, TOP_TILESIZE);
	tmpObjSet.imgKeyValue = "none";
	tile->setTopObjImageSet(tmpObjSet);

	tile->setIsAvailMove(false);
	tile->setParent(nullptr);
}

void mapEditor::InitButtons()
{
	for (int i = 0; i < E_BUTTONS_END; i++) {
		switch (i) {
		case AREAMODE:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_areamode");
			_buttons[i].pos = { 174,814 };
			break;
		case ERASE_TILE:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_eraseTile");
			_buttons[i].pos = { 1087,36 };
			break;
		case ERASE_OBJ:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_eraseObj");
			_buttons[i].pos = { 1087,92 };
			break;
			//	case ERASE_UNIT:
			//		_buttons[i].img = IMAGEMANAGER->findImage("btn_eraseUnit");
			//		_buttons[i].pos = { 1087,148 };
			//		break;
		case INFO:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_info");
			_buttons[i].pos = { 1087,257 };
			break;
		case SAVE:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_save");
			_buttons[i].pos = { 884,814 };
			break;
		case LOAD:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_load");
			_buttons[i].pos = { 884,864 };
			break;
		case MAPIDX:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_mapidx");
			_buttons[i].pos = { 708,814 };
			break;
		case XY:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_xy");
			_buttons[i].pos = { 465,864 };
			break;
		case MAPSIZE:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_mapsize");
			_buttons[i].pos = { 465,814 };
			break;
		case TILES:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_tiles");
			_buttons[i].pos = { 1225,490 };
			break;
		case OBJECTS:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_objects");
			_buttons[i].pos = { 1375,490 };
			break;
		case UNITS:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_units");
			_buttons[i].pos = { 1525,490 };
			break;
		case ERASE:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_erase");
			_buttons[i].pos = { 1087,207 };


		}

		_buttons[i].frameX = 0;
		_buttons[i].frameY = 0;
		_buttons[i].rc = RectMakeCenter(_buttons[i].pos.x, _buttons[i].pos.y, _buttons[i].img->getFrameWidth(), _buttons[i].img->getFrameHeight());


	}
	//	_kindButtons 이닛
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < BTN_KINDS_END; j++) {
			switch (j) {
			case BTN_CASTLE:
				_kindButtons[i][j].img = IMAGEMANAGER->findImage("btn_castle");
				_kindButtons[i][j].pos.y = 550;
				break;

			case BTN_ICE:
				_kindButtons[i][j].img = IMAGEMANAGER->findImage("btn_ice");
				_kindButtons[i][j].pos.y = 600;
				break;

			case BTN_FIRE:
				_kindButtons[i][j].img = IMAGEMANAGER->findImage("btn_fire");
				_kindButtons[i][j].pos.y = 650;
				break;

			case BTN_EARTH:
				_kindButtons[i][j].img = IMAGEMANAGER->findImage("btn_earth");
				_kindButtons[i][j].pos.y = 700;
				break;

			case BTN_COMMON:
				_kindButtons[i][j].img = IMAGEMANAGER->findImage("btn_common");
				_kindButtons[i][j].pos.y = 750;
				break;

			}
			switch (i) {
			case 0:	//	타일
				_kindButtons[i][j].pos.x = 1225;
				break;
			case 1:	//	obj
				_kindButtons[i][j].pos.x = 1375;
				break;
			case 2:	//	unit
				_kindButtons[i][j].pos.x = 1525;
				break;


			}
			_kindButtons[i][j].rc = RectMakeCenter(_kindButtons[i][j].pos.x, _kindButtons[i][j].pos.y,
				_kindButtons[i][j].img->getFrameWidth(), _kindButtons[i][j].img->getFrameHeight());
			_kindButtons[i][j].isOn = false;

		}
	}
	_kindButtons[0][0].isOn = true;		//	첫번째. 타일->캐슬


}

void mapEditor::InitArrows()
{

	for (int i = 0; i < E_ARROW_END; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_arrowButtons[j][i].frameX = j;
			_arrowButtons[j][i].frameY = 0;
			_arrowButtons[j][i].img = IMAGEMANAGER->findImage("btn_arrow");
		}

		switch (i)
		{
		case ARROW_AREAMODE:

			_arrowButtons[0][ARROW_AREAMODE].pos.x = _buttons[AREAMODE].rc.left - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_AREAMODE].pos.x = _buttons[AREAMODE].rc.right + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_AREAMODE].pos.y = _buttons[AREAMODE].pos.y;
			_arrowButtons[1][ARROW_AREAMODE].pos.y = _buttons[AREAMODE].pos.y;
			break;

		case ARROW_MAPIDX:

			_arrowButtons[0][ARROW_MAPIDX].pos.x = _buttons[MAPIDX].rc.left - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_MAPIDX].pos.x = _buttons[MAPIDX].rc.right + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_MAPIDX].pos.y = _buttons[MAPIDX].pos.y;
			_arrowButtons[1][ARROW_MAPIDX].pos.y = _buttons[MAPIDX].pos.y;
			break;

		case ARROW_MAPSIZEX:

			_arrowButtons[0][ARROW_MAPSIZEX].pos.x = _buttons[XY].rc.left - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_MAPSIZEX].pos.x = _buttons[XY].rc.left + 20 + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_MAPSIZEX].pos.y = _buttons[XY].pos.y;
			_arrowButtons[1][ARROW_MAPSIZEX].pos.y = _buttons[XY].pos.y;
			break;
		case ARROW_MAPSIZEY:

			_arrowButtons[0][ARROW_MAPSIZEY].pos.x = _buttons[XY].rc.right - 20 - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_MAPSIZEY].pos.x = _buttons[XY].rc.right + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_MAPSIZEY].pos.y = _buttons[XY].pos.y;
			_arrowButtons[1][ARROW_MAPSIZEY].pos.y = _buttons[XY].pos.y;
			break;
		case ARROW_TILES:

			_arrowButtons[0][ARROW_TILES].pos.x = _buttons[TILES].rc.left - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_TILES].pos.x = _buttons[TILES].rc.right + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_TILES].pos.y = _buttons[TILES].pos.y;
			_arrowButtons[1][ARROW_TILES].pos.y = _buttons[TILES].pos.y;
			break;
		case ARROW_OBJECTS:

			_arrowButtons[0][ARROW_OBJECTS].pos.x = _buttons[OBJECTS].rc.left - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_OBJECTS].pos.x = _buttons[OBJECTS].rc.right + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_OBJECTS].pos.y = _buttons[OBJECTS].pos.y;
			_arrowButtons[1][ARROW_OBJECTS].pos.y = _buttons[OBJECTS].pos.y;
			break;

		case ARROW_UNITS:

			_arrowButtons[0][ARROW_UNITS].pos.x = _buttons[UNITS].rc.left - ARROWBUTTON_GAP;
			_arrowButtons[1][ARROW_UNITS].pos.x = _buttons[UNITS].rc.right + ARROWBUTTON_GAP;
			_arrowButtons[0][ARROW_UNITS].pos.y = _buttons[UNITS].pos.y;
			_arrowButtons[1][ARROW_UNITS].pos.y = _buttons[UNITS].pos.y;
			break;

		}	//	스위치종료

		for (int j = 0; j < 2; j++) {
			_arrowButtons[j][i].rc = RectMakeCenter(_arrowButtons[j][i].pos.x, _arrowButtons[j][i].pos.y,
				_arrowButtons[j][i].img->getFrameWidth(), _arrowButtons[j][i].img->getFrameHeight());
		}


	}	//	j for문 종료


}

void mapEditor::InitSampleRc()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			_sampleRc[i][j] = RectMakeCenter(1150 + 1 + 16 + j * 32, 16 + 1 + i * 32, 32, 32);
		}
	}
}

void mapEditor::InitSampleCastleTile()
{
	{
		//for (int i = 0; i <= IMAGEMANAGER->findImage("tileCastle")->getMaxFrameY(); i++)	//	12
		//{
		//	for (int j = 0; j <= IMAGEMANAGER->findImage("tileCastle")->getMaxFrameX(); j++)	//	22
		//	{
		for (int i = 0; i <= 12; i++)	//	12
		{
			for (int j = 0; j <= 22; j++)	//	22
			{
				_totalSamples[SELECT_TILE][CASTLE_TILE][i][j] = new tile;
				SetNewSampleTile(_totalSamples[SELECT_TILE][CASTLE_TILE][i][j], j, i);
				_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileImage(IMAGEMANAGER->findImage("tileCastle"));
				_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileImgKey("tileCastle");

				//	개별적 셋팅
				//	1번
				if (i <= 11 && j <= 11)
				{
					//	1번 윗벽
					if (0 <= i && i <= 3) {
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}

					//	1번 왼쪽벽
					if (j == 0) {
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
					//	1번 아래벽
					if (i == 11) {
						if (0 <= j && j <= 11) {
							_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(false);
							_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_WALL);
						}
					}
					//	1번 우측벽
					if (j == 11) {
						if (0 <= i && i <= 11) {
							_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(false);
							_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_WALL);
						}
					}
					//	1번 바닥
					if (4 <= i && i <= 10) {
						if (1 <= j && j <= 10) {
							_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(true);
							_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
						}
					}
				}	//	1번 타일 끝

				//	2번 
				if (i <= 6 && 12 <= j && j <= 17) {
					if (i <= 3) {
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
					if (4 <= i && i <= 6) {
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}

				//	3번
				if (18 <= j && j <= 21 && i <= 6) {
					_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
				}

				//	4번
				if (12 <= j && j <= 15 && 7 <= i && i <= 11) {
					_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_TILE][CASTLE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
				}




			}
		}	//for i 종료

		//캐슬 타일 프레임 갯수 이닛
		{
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][0][CASTLETILE1] = { 0,0 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][1][CASTLETILE1] = { 11,11 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][0][CASTLETILE2] = { 12,0 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][1][CASTLETILE2] = { 17,6 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][0][CASTLETILE3] = { 18,0 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][1][CASTLETILE3] = { 22,6 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][0][CASTLETILE4] = { 12,7 };
			_totalFrameIdx[SELECT_TILE][CASTLE_TILE][1][CASTLETILE4] = { 15,11 };
		}

	}
}

void mapEditor::InitSampleCastleObj()
{

	for (int i = 0; i <= IMAGEMANAGER->findImage("objCastle")->getMaxFrameY(); i++)	//	11
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("objCastle")->getMaxFrameX(); j++)	//	22
		{
			_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j] = new tile;

			SetNewSampleObj(_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j], j, i);
			_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjImage(IMAGEMANAGER->findImage("objCastle"));
			_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjImgKey("objCastle");

			//	개별적 셋팅
			//	벽,동상,기둥, 창문들
			if (i <= 4) {
				if (j <= 2) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
				if (i <= 2) {
					if (2 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (3 <= i && i <= 4) {
					if (2 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i <= 2) {
					if (6 <= j && j <= 11) {
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (3 <= i && i <= 4) {
					if (6 <= j && j <= 8) {
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE1);
					}
					if (9 <= j && j <= 11) {
						if (6 <= j && j <= 8) {
							_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
							_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE2);
						}
					}
				}
			}
			//	깃발
			if (j <= 2) {
				if (5 <= i && i <= 7) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//	책장
			if (5 <= i && i <= 7) {
				if (3 <= j && j <= 5) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE3);
				}
				if (6 <= j && j <= 8) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE4);
				}
			}
			//	잡동사니
			if (5 <= i && i <= 6) {
				if (j == 9) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE5);
				}
			}
			if (i == 5) {
				if (j == 11) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE6);
				}
			}
			if (i == 6) {
				if (j == 10) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE7);
				}
			}
			if (i == 6) {
				if (j == 11) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE8);
				}
			}
			if (i == 7) {
				if (j == 9) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE9);
				}
				if (j == 10) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE10);
				}
			}
			//	나무의자, 나무들
			if (8 <= i && i <= 9) {
				if (0 <= j && j <= 3) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE11);
				}
				if (4 <= j && j <= 5) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE12);
				}
				if (6 <= j && j <= 9) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE13);
				}
			}


			//	돌아치
			if (i <= 5) {
				//왼쪽다리
				if (12 <= j && j <= 13) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
				//아치
				if (i <= 2) {
					if (12 <= j && j <= 18) {
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//오른쪽다리
				if (17 <= j && j <= 18) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//	돌아치 기둥 밑부분
			if (i == 6) {
				if (j == 12 || j == 18) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//	나무문 - > 사용안함
			if (2 <= i && i <= 6) {
				if (19 <= j && j <= 22) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_BREAKABLE);
				}

			}
			//	촛대
			if (12 <= j && j <= 13) {
				if (7 <= i && i <= 9) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE14);
				}
			}
			//	촛불
			if (j == 14 && i == 7) {
				_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
				_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_CANDLE);
			}


			//해골묶여잇는거
			if (3 <= i && i <= 4) {
				if (9 <= j && j <= 11) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE89);
				}
			}
			//깃발
			if (5 <= i && i <= 7) {
				if (0 <= j && j <= 2) {
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][CASTLE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}


		}
	}	//	for i 종료
	//캐슬 Obj 프레임 갯수 이닛
	{
		_totalFrameIdx[SELECT_OBJ][CASTLE_OBJ][0][CASTLEOBJ1] = { 0,0 };
		_totalFrameIdx[SELECT_OBJ][CASTLE_OBJ][1][CASTLEOBJ1] = { 11,9 };

		_totalFrameIdx[SELECT_OBJ][CASTLE_OBJ][0][CASTLEOBJ2] = { 12,0 };
		_totalFrameIdx[SELECT_OBJ][CASTLE_OBJ][1][CASTLEOBJ2] = { 22,9 };

	}
}

void mapEditor::InitSampleEarthTile()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("tileEarth")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("tileEarth")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_TILE][EARTH_TILE][i][j] = new tile;
			SetNewSampleTile(_totalSamples[SELECT_TILE][EARTH_TILE][i][j], j, i);
			_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileImage(IMAGEMANAGER->findImage("tileEarth"));
			_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileImgKey("tileEarth");

			//	개별적 셋팅
			//	1번 페이지
			{
				//위벽
				if (0 <= i && i <= 3) {
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//좌우벽
				if (0 <= i && i <= 11) {
					//왼쪽벽
					if (j == 0) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
					//오른쪽벽
					else if (j == 11) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//아래벽
				if (i == 11) {
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//	벽내부바닥
				if (4 <= i && i <= 10) {
					if (1 <= j && j <= 10) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}


				//오른쪽 타일들
				if (0 <= i && i <= 8) {
					if (12 <= j && j <= 13) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
			}
			//	1번페이지 끗

			//	2번페이지
			{
				if (0 <= i && i <= 13) {
					if (14 <= j && j <= 24) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
			}
			//	2번페이지 끗

			//	3번페이지
			{
				if (0 <= i && i <= 4) {
					if (28 <= j && j <= 32) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (0 <= i && i <= 3) {
					if (33 <= j && j <= 38) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (28 <= j && j <= 37) {
					if (5 <= i && i <= 8) {

						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
					if (9 <= i && i <= 11) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}
				if (12 <= i && i <= 13) {
					if (28 <= j && j <= 32) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_HOLE);

					}
				}
			}
			//	3번 페이지 끗

			//	4번 페이지 시작
			{
				if (0 <= i && i <= 9) {
					if (42 <= j && j <= 48) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

				if (12 <= i && i <= 14) {
					if (49 <= j && j <= 51) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

				if (10 <= i && i <= 12) {
					if (42 <= j && j <= 43) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}

					if (44 <= j && j <= 54) {
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][EARTH_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}

				}

			}
			//	4번 페이지 끗

		}	//	for j 종료
	}	//for i 종료


	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][0][EARTHTILE1] = { 0,0 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][1][EARTHTILE1] = { 13,13 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][0][EARTHTILE2] = { 14,0 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][1][EARTHTILE2] = { 27,13 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][0][EARTHTILE3] = { 28,0 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][1][EARTHTILE3] = { 41,13 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][0][EARTHTILE4] = { 42,0 };
		_totalFrameIdx[SELECT_TILE][EARTH_TILE][1][EARTHTILE4] = { 55,13 };


	}


}

void mapEditor::InitSampleEarthObj()
{

	for (int i = 0; i <= IMAGEMANAGER->findImage("objEarth")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("objEarth")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j] = new tile;
			SetNewSampleObj(_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j], j, i);
			_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjImage(IMAGEMANAGER->findImage("objEarth"));
			_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjImgKey("objEarth");

			//	1페이지
			{
				//	위쪽 벽장식
				if (0 <= i && i <= 2) {
					if (0 <= j && j <= 9) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	작은 풀
				if (0 <= i && i <= 1) {
					if (10 <= j && j <= 11) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	풀떼기들...?
				if (3 <= i && i <= 5) {
					if (0 <= j && j <= 10) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	땅잡초-풀
				if (6 <= i && i <= 7) {
					if (0 <= j && j <= 3) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//	기둥 테두리 풀
				if (8 <= i && i <= 10) {
					if (0 <= j && j <= 3) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//	밟는 풀 + 돌
				if (8 <= i && i <= 9) {
					if (4 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE1);
					}
					if (6 <= j && j <= 7) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE2);
					}
					if (8 <= j && j <= 9) {
						if (i == 8) {
							_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
							_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE3);
						}
						else if (i == 9) {
							_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
							_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE4);
						}

					}
					if (10 <= j && j <= 11) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE5);
					}
					if (12 <= j && j <= 13) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE6);
					}

				}
				//	밑에 나무
				if (11 <= i && i <= 13) {
					if (0 <= j && j <= 2) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE7);
					}
					if (3 <= j && j <= 4) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE8);
					}
					if (5 <= j && j <= 7) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE9);
					}

				}

			}
			//	1페이지 끗

			//	2페이지 시작
			{
				if (0 <= i && i <= 5) {
					if (14 <= j && j <= 19) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 4) {
					if (j == 14 || j == 19) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 5) {
					if (j == 14 || j == 19) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (0 <= i && i <= 4) {
					if (20 <= j && j <= 26) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	묘지 윗부분
				if (6 <= i && i <= 7) {
					if (14 <= j && j <= 21) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	묘지 아래
				if (i == 8) {
					if (14 <= j && j <= 21) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//	창문들
				if (6 <= i && i <= 8) {
					if (22 <= j && j <= 27) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	밑에 액자
				if (9 <= i && i <= 11) {
					if (14 <= j && j <= 16) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE10);
					}
					if (17 <= j && j <= 18) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE11);
					}

				}



			}
			//	2페이지 끗

			//	3페이지 시작
			{
				//작은나무
				if (0 <= i && i <= 4) {
					if (28 <= j && j <= 37) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_TREE1);
					}
				}
				//작은나무 밑기둥
				if (i == 4) {
					if (j == 30) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_TREEROOT1);
					}
				}
				//	모닥불
				if (6 <= i && i <= 8) {
					if (28 <= j && j <= 30) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE13);
					}
				}
				//	큰나무
				if (0 <= i && i <= 5) {
					if (33 <= j && j <= 37) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_TREE2);
					}
				}

				//큰나무 밑기둥
				if (i == 5) {
					if (j == 35) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_TREEROOT2);
					}
				}




				//	항아리 + 돌
				if (9 <= i && i <= 10) {
					if (28 <= j && j <= 29) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE14);
					}
					if (30 <= j && j <= 31) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE15);
					}

				}
				//	통나무
				if (6 <= i && i <= 9) {
					if (33 <= j && j <= 37) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE16);
					}
				}

				//	화단??
				if (11 <= i && i <= 13) {
					if (28 <= j && j <= 29) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (12 <= i && i <= 13) {
					if (30 <= j && j <= 31) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	굴뚝?위
				if (i == 12) {
					if (32 <= j && j <= 34) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	굴뚝?아래
				if (i == 13) {
					if (32 <= j && j <= 34) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	돌벽
				if (0 <= i && i <= 4) {
					if (38 <= j && j <= 39) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	돌기둥 위쪽
				if (0 <= i && i <= 2) {
					if (40 <= j && j <= 41) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	돌기둥 아래쪽
				if (3 <= i && i <= 4) {
					if (40 <= j && j <= 41) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//	깃발
				if (5 <= i && i <= 7) {
					if (38 <= j && j <= 39) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

			}
			//	3페이지 끗

			//	4페이지 시작
			{
				//	도형액자
				if (0 <= i && i <= 2) {
					if (42 <= j && j <= 44) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE17);
					}
					if (45 <= j && j <= 46) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE18);
					}
				}
				//	찬희액자
				if (3 <= i && i <= 5) {
					if (42 <= j && j <= 44) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE19);
					}
					if (45 <= j && j <= 46) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE20);
					}
				}
				if (6 <= i && i <= 8) {
					if (42 <= j && j <= 44) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE21);
					}
					if (45 <= j && j <= 46) {
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][EARTH_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE22);
					}
				}
			}




		}	//	for j end
	}	//	for i end

	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][0][EARTHTILE1] = { 0,0 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][1][EARTHTILE1] = { 13,13 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][0][EARTHTILE2] = { 14,0 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][1][EARTHTILE2] = { 27,13 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][0][EARTHTILE3] = { 28,0 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][1][EARTHTILE3] = { 41,13 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][0][EARTHTILE4] = { 42,0 };
		_totalFrameIdx[SELECT_OBJ][EARTH_OBJ][1][EARTHTILE4] = { 55,13 };


	}

}

void mapEditor::InitSampleIceTile()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("tileIce")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("tileIce")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_TILE][ICE_TILE][i][j] = new tile;
			SetNewSampleTile(_totalSamples[SELECT_TILE][ICE_TILE][i][j], j, i);
			_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileImage(IMAGEMANAGER->findImage("tileIce"));
			_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileImgKey("tileIce");

			//	개별적 셋팅
			//	1번 페이지
			{
				//위벽
				if (0 <= i && i <= 3) {
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//좌우벽
				if (0 <= i && i <= 11) {
					//왼쪽벽
					if (j == 0) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
					//오른쪽벽
					else if (j == 11) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//아래벽
				if (i == 11) {
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//	벽내부바닥
				if (4 <= i && i <= 10) {
					if (1 <= j && j <= 10) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}


				//오른쪽 타일들
				if (0 <= i && i <= 8)
				{
					if (12 <= j && j <= 13) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
			}
			//	1번페이지 끗

			//	2번페이지
			{
				//위벽
				if (0 <= i && i <= 3) {
					if (14 <= j && j <= 25) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//좌우벽
				if (0 <= i && i <= 11) {
					//왼쪽벽
					if (j == 14) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
					//오른쪽벽
					else if (j == 25) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//아래벽
				if (i == 11) {
					if (14 <= j && j <= 25) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//	벽내부바닥
				if (4 <= i && i <= 10) {
					if (15 <= j && j <= 24) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}


				//오른쪽 타일들
				if (0 <= i && i <= 8)
				{
					if (26 <= j && j <= 28) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

				//아래에있는 타일들
				if (12 <= i && i <= 14)
				{
					if (14 <= j && j <= 22) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

			}
			//	2번페이지 끗

			//	3번페이지
			{
				//타일
				if (0 <= i && i <= 11) {
					if (28 <= j && j <= 35) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				//사다리
				if (i == 0) {
					if (j == 36) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 1) {
					if (j == 36) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (i == 2) {
					if (j == 36) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (i == 3) {
					if (j == 36) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//구멍
				if (0 <= i && i <= 3) {
					if (37 <= j && j <= 41) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (4 <= i && i <= 6) {
					if (37 <= j && j <= 41) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}
				if (7 <= i && i <= 10) {
					if (37 <= j && j <= 41) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (11 <= i && i <= 13) {
					if (37 <= j && j <= 41) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}
			}
			//	3번 페이지 끗

			//4페이지 시작
			{
				if (0 <= i && i <= 9) {
					if (42 <= j && j <= 53) {
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][ICE_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}
			}
			//4페이지 끗

		}	//	for j 종료
	}	//for i 종료


	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_TILE][ICE_TILE][0][ICETILE1] = { 0,0 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][1][ICETILE1] = { 13,13 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][0][ICETILE2] = { 14,0 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][1][ICETILE2] = { 27,13 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][0][ICETILE3] = { 28,0 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][1][ICETILE3] = { 41,13 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][0][ICETILE4] = { 42,0 };
		_totalFrameIdx[SELECT_TILE][ICE_TILE][1][ICETILE4] = { 55,13 };
	}

}

void mapEditor::InitSampleIceObj()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("objIce")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("objIce")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_OBJ][ICE_OBJ][i][j] = new tile;
			SetNewSampleObj(_totalSamples[SELECT_OBJ][ICE_OBJ][i][j], j, i);
			_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjImage(IMAGEMANAGER->findImage("objIce"));
			_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjImgKey("objIce");

			//1페이지
			{
				//	얼음들
				if (0 <= i && i <= 1) {
					if (0 <= j && j <= 1) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE1);
					}
				}
				if (0 <= i && i <= 1) {
					if (2 <= j && j <= 3) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE2);
					}
				}
				if (0 <= i && i <= 1) {
					if (4 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE3);
					}
				}

				if (2 <= i && i <= 4) {
					if (0 <= j && j <= 2) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE4);
					}
				}
				if (2 <= i && i <= 4) {
					if (3 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE5);
					}
				}
				if (5 <= i && i <= 8) {
					if (0 <= j && j <= 2) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE6);
					}
				}
				if (5 <= i && i <= 7) {
					if (3 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE7);
					}
				}
				if (8 <= i && i <= 10) {
					if (3 <= j && j <= 5) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE8);
					}
				}
				if (0 <= i && i <= 4) {
					if (6 <= j && j <= 7) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE9);
					}
				}
				if (0 <= i && i <= 2) {
					if (8 <= j && j <= 9) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE10);
					}
				}
				if (0 <= i && i <= 1) {
					if (10 <= j && j <= 11) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE11);
					}
				}
				if (10 <= i && i <= 13) {
					if (5 <= j && j <= 9) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE12);
					}
				}

				if (5 <= i && i <= 7) {
					if (6 <= j && j <= 8) {
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE20);
					}
				}

				//2페이지 - 창문과 문?
				if (0 <= i && i <= 13)
				{
					if (14 <= j && j <= 27)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//다리사이
				if (i == 6)
				{
					if (20 <= j && j <= 21)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 6)
				{
					if (25 <= j && j <= 26)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//28번~37번
				//3페이지
				if (0 <= i && i <= 1)
				{
					if (28 <= j && j <= 30)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE13);
					}
				}
				if (0 <= i && i <= 1)
				{
					if (31 <= j && j <= 33)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE14);
					}
				}
				if (2 <= i && i <= 3)
				{
					if (28 <= j && j <= 30)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE15);
					}
				}
				if (i == 2)
				{
					if (j == 31)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE16);
					}
				}
				if (i == 2)
				{
					if (j == 32)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE17);
					}
				}

				//가시
				if (4 <= i && i <= 5)
				{
					if (28 <= j && j <= 34)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_NEEDLE);
					}
				}

				//해골 및 구조물
				if (7 <= i && i <= 8)
				{
					if (28 <= j && j <= 29)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 7)
				{
					if (30 <= j && j <= 31)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 8)
				{
					if (30 <= j && j <= 31)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (7 <= i && i <= 8)
				{
					if (32 <= j && j <= 33)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//해골들과 철장
				if (9 <= i && i <= 11)
				{
					if (28 <= j && j <= 31)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 12)
				{
					if (28 <= j && j <= 31)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (9 <= i && i <= 11)
				{
					if (32 <= j && j <= 36)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 12)
				{
					if (32 <= j && j <= 36)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//깃발
				if (6 <= i && i <= 8)
				{
					if (35 <= j && j <= 36)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE19);
					}
				}

				//기둥
				if (0 <= i && i <= 2)
				{
					if (38 <= j && j <= 41)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//기둥
				if (3 <= i && i <= 4)
				{
					if (38 <= j && j <= 41)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (5 <= i && i <= 9)
				{
					if (38 <= j && j <= 41)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//4페이지
				if (0 <= i && i <= 6)
				{
					if (42 <= j && j <= 48)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 7)
				{
					if (42 <= j && j <= 43)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 7)
				{
					if (47 <= j && j <= 48)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//다리사이
				if (i == 7)
				{
					if (44 <= j && j <= 46)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//석상
				if (8 <= i && i <= 9)
				{
					if (42 <= j && j <= 44)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (10 <= i && i <= 11)
				{
					if (42 <= j && j <= 44)
					{
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][ICE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

			}
		}	//	for j end
	}	//	for i end

	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][0][ICETILE1] = { 0,0 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][1][ICETILE1] = { 13,13 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][0][ICETILE2] = { 14,0 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][1][ICETILE2] = { 27,13 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][0][ICETILE3] = { 28,0 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][1][ICETILE3] = { 41,13 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][0][ICETILE4] = { 42,0 };
		_totalFrameIdx[SELECT_OBJ][ICE_OBJ][1][ICETILE4] = { 55,13 };
	}
}

void mapEditor::InitSampleFireTile()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("tileFire")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("tileFire")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_TILE][FIRE_TILE][i][j] = new tile;
			SetNewSampleTile(_totalSamples[SELECT_TILE][FIRE_TILE][i][j], j, i);
			_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileImage(IMAGEMANAGER->findImage("tileFire"));
			_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileImgKey("tileFire");

			//	개별적 셋팅
			//	1번 페이지
			{
				if (0 <= i && i <= 11)
				{
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (0 <= i && i <= 3)
				{
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 11)
				{
					if (j == 0) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 11)
				{
					if (j == 11) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 11)
				{
					if (0 <= j && j <= 11) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				if (0 <= i && i <= 12)
				{
					if (12 <= j && j <= 13) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
			}
			//페이지2
			{
				if (0 <= i && i <= 13)
				{
					if (14 <= j && j <= 25) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (i == 1)
				{
					if (23 <= j && j <= 24) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 4)
				{
					if (23 <= j && j <= 24) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//하수구
				if (8 <= i && i <= 10)
				{
					if (14 <= j && j <= 17) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (12 <= i && i <= 13)
				{
					if (j == 14) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (9 <= i && i <= 10)
				{
					if (j == 18) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 10)
				{
					if (15 <= j && j <= 16) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
			}

			//페이지3 // 4페이지포함
			{
				if (0 <= i && i <= 13)
				{
					if (28 <= j && j <= 45) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (4 <= i && i <= 6)
				{
					if (37 <= j && j <= 41) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}
				if (9 <= i && i <= 13)
				{
					if (34 <= j && j <= 41) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_HOLE);
					}
				}

				//화로
				if (0 <= i && i <= 4) {
					if (46 <= j && j <= 55) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 2) {
					if (46 <= j && j <= 48) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (i == 4) {
					if (49 <= j && j <= 52) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

				//길수정
				if (12 <= i && i <= 13) {
					if (j == 14) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopObjAttr(TILE_FLOOR);
					}
				}
				if (9 <= i && i <= 10) {
					if (j == 18) {
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][FIRE_TILE][i][j]->setTopObjAttr(TILE_FLOOR);
					}
				}

			}
		}	//	for j 종료
	}	//for i 종료


	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][0][FIRETILE1] = { 0,0 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][1][FIRETILE1] = { 13,13 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][0][FIRETILE2] = { 14,0 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][1][FIRETILE2] = { 27,13 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][0][FIRETILE3] = { 28,0 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][1][FIRETILE3] = { 41,13 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][0][FIRETILE4] = { 42,0 };
		_totalFrameIdx[SELECT_TILE][FIRE_TILE][1][FIRETILE4] = { 55,13 };
	}
}

void mapEditor::InitSampleFireObj()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("objFire")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("objFire")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j] = new tile;
			SetNewSampleObj(_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j], j, i);
			_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjImage(IMAGEMANAGER->findImage("objFire"));
			_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjImgKey("objFire");

			//1페이지
			{
				//돌 부터시작
				if (0 <= i && i <= 1) {
					if (0 <= j && j <= 2) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE1);
					}
				}
				if (0 <= i && i <= 1) {
					if (3 <= j && j <= 4) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE2);
					}
				}
				if (0 <= i && i <= 1) {
					if (j == 5) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE3);
					}
				}
				if (0 <= i && i <= 1) {
					if (6 <= j && j <= 8) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE4);
					}
				}
				if (0 <= i && i <= 1) {
					if (9 <= j && j <= 10) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE5);
					}
				}
				if (0 <= i && i <= 1) {
					if (11 <= j && j <= 12) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE6);
					}
				}

				//박스부터시작
				if (2 <= i && i <= 3) {
					if (0 <= j && j <= 2) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE7);
					}
				}
				if (i == 3) {
					if (j == 3) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE8);
					}
				}
				if (i == 3) {
					if (j == 4) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE9);
					}
				}
				//가시
				if (i == 3) {
					if (j == 5) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_TRAP1);
					}
				}
				if (i == 3) {
					if (j == 6) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_TRAP2);
					}
				}

				if (2 <= i && i <= 3) {
					if (j == 7) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_TRAP3);
					}
				}
				if (2 <= i && i <= 3) {
					if (j == 8) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_TRAP4);
					}
				}
				if (2 <= i && i <= 3) {
					if (9 <= j && j <= 10) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_TRAP5);
					}
				}

				//뻰치
				if (2 <= i && i <= 4) {
					if (11 <= j && j <= 12) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE14);
					}
				}

				//화로 처음부터
				if (5 <= i && i <= 13) {
					if (0 <= j && j <= 20) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				//기둥2개
				if (5 <= i && i <= 7) {
					if (10 <= j && j <= 11) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}

				//동상
				if (9 <= i && i <= 10) {
					if (0 <= j && j <= 2) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
			}
			// 2페이지
			{
				//망치부터
				if (0 <= i && i <= 2) {
					if (15 <= j && j <= 16) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE15);
					}
				}
				if (0 <= i && i <= 2) {
					if (17 <= j && j <= 18) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE16);
					}
				}
				if (0 <= i && i <= 2) {
					if (19 <= j && j <= 20) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE17);
					}
				}
				if (i == 0) {
					if (21 <= j && j <= 22) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE18);
					}
				}
				if (i == 1) {
					if (21 <= j && j <= 22) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE19);
					}
				}
				//갑옷부터
				if (0 <= i && i <= 2) {
					if (23 <= j && j <= 24) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE20);
					}
				}
				if (0 <= i && i <= 2) {
					if (25 <= j && j <= 26) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE21);
					}
				}
				//문양?
				if (3 <= i && i <= 4) {
					if (21 <= j && j <= 22) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE22);
					}
				}
				if (3 <= i && i <= 5) {
					if (23 <= j && j <= 24) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE23);
					}
				}

				//기둥
				if (5 <= i && i <= 9) {
					if (14 <= j && j <= 20) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
				if (i == 10) {
					if (16 <= j && j <= 18) {
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_OBJ][FIRE_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
					}
				}
			}
		}	//	for j end
	}	//	for i end

	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_OBJ][FIRE_OBJ][0][FIRETILE1] = { 0,0 };
		_totalFrameIdx[SELECT_OBJ][FIRE_OBJ][1][FIRETILE1] = { 13,13 };
		_totalFrameIdx[SELECT_OBJ][FIRE_OBJ][0][FIRETILE2] = { 14,0 };
		_totalFrameIdx[SELECT_OBJ][FIRE_OBJ][1][FIRETILE2] = { 27,13 };
	}
}

void mapEditor::InitSampleCommonTile()
{
	int maxFrameX = IMAGEMANAGER->findImage("tileCommon")->getMaxFrameX();
	int maxFrameY = IMAGEMANAGER->findImage("tileCommon")->getMaxFrameY();

	for (int i = 0; i <= IMAGEMANAGER->findImage("tileCommon")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("tileCommon")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_TILE][COMMON_TILE][i][j] = new tile;
			SetNewSampleTile(_totalSamples[SELECT_TILE][COMMON_TILE][i][j], j, i);
			_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileImage(IMAGEMANAGER->findImage("tileCommon"));
			_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileImgKey("tileCommon");

			//1페이지
			{
				//전부길로 처리
				if (0 <= i && i <= 13)
				{
					if (0 <= j && j <= 112) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

				//1페이지 방
				if (0 <= i && i <= 4)
				{
					if (0 <= j && j <= 3) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 3)
				{
					if (4 <= j && j <= 14) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 4)
				{
					if (15 <= j && j <= 18) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (1 <= i && i <= 8)
				{
					if (j == 18) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 9)
				{
					if (15 <= j && j <= 18) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 9)
				{
					if (3 <= j && j <= 15) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 9)
				{
					if (0 <= j && j <= 3) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 8)
				{
					if (j == 0) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//2페이지 벽
				if (0 <= i && i <= 3)
				{
					if (19 <= j && j <= 27) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}


				//3페이지 방
				if (0 <= i && i <= 4)
				{
					if (28 <= j && j <= 31) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 3)
				{
					if (32 <= j && j <= 42) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 4)
				{
					if (43 <= j && j <= 46) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (1 <= i && i <= 8)
				{
					if (j == 46) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 9)
				{
					if (43 <= j && j <= 46) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 9)
				{
					if (31 <= j && j <= 43) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 9)
				{
					if (28 <= j && j <= 31) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 8)
				{
					if (j == 28) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//4페이지 타일샘플방
				if (0 <= i && i <= 3)
				{
					if (47 <= j && j <= 64) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				//기둥
				if (0 <= i && i <= 7)
				{
					if (52 <= j && j <= 53) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 7)
				{
					if (58 <= j && j <= 59) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 10)
				{
					if (47 <= j && j <= 60) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//5페이지부터 시작되는 방
				if (0 <= i && i <= 4)
				{
					if (65 <= j && j <= 68) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 3)
				{
					if (69 <= j && j <= 79) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 4)
				{
					if (80 <= j && j <= 83) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (1 <= i && i <= 8)
				{
					if (j == 83) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 9)
				{
					if (80 <= j && j <= 83) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (i == 9)
				{
					if (68 <= j && j <= 80) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (8 <= i && i <= 9)
				{
					if (65 <= j && j <= 68) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 8)
				{
					if (j == 65) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//6페이지방아래 벽
				if (i == 10)
				{
					if (70 <= j && j <= 81) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//7페이지벽
				if (0 <= i && i <= 2)
				{
					if (84 <= j && j <= 90) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//망루대같은? 
				if (0 <= i && i <= 2)
				{
					if (91 <= j && j <= 96) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (0 <= i && i <= 4)
				{
					if (j == 96) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (5 <= i && i <= 8)
				{
					if (91 <= j && j <= 96) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				if (12 <= i && i <= 13)
				{
					if (87 <= j && j <= 97) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//8페이지 (보스서잇는곳?)
				if (1 <= i && i <= 8)
				{
					if (98 <= j && j <= 99) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (6 <= i && i <= 8)
				{
					if (98 <= j && j <= 105) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}
				if (1 <= i && i <= 8)
				{
					if (104 <= j && j <= 105) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(false);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_WALL);
					}
				}

				//길추가1 - 보스서잇는곳
				if (3 <= i && i <= 5)
				{
					if (j == 99) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}
				if (3 <= i && i <= 5)
				{
					if (j == 104) {
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(true);
						_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
					}
				}

			}
		}	//	for j 종료
	}	//for i 종료


	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE1] = { 0,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE1] = { 13,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE2] = { 14,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE2] = { 27,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE3] = { 28,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE3] = { 41,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE4] = { 42,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE4] = { 55,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE5] = { 56,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE5] = { 69,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE6] = { 70,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE6] = { 83,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE7] = { 84,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE7] = { 97,13 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][0][COMMONTILE8] = { 98,0 };
		_totalFrameIdx[SELECT_TILE][COMMON_TILE][1][COMMONTILE8] = { 111,13 };
	}
}

void mapEditor::InitSampleCommonObj()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("objCommon")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("objCommon")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j] = new tile;
			SetNewSampleObj(_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j], j, i);
			_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjImage(IMAGEMANAGER->findImage("objCommon"));
			_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjImgKey("objCommon");

			//_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
			//_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE1);
			//_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
			//_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);

			//1페이지
			//나무 사람통과하는기둥
			if (0 <= i && i <= 4)
			{
				if (0 <= j && j <= 5)
				{
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 4)
			{
				if (0 <= j && j <= 1)
				{
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 4)
			{
				if (4 <= j && j <= 5)
				{
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 5)
			{
				if (1 <= j && j <= 4)
				{
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//침대
			if (0 <= i && i <= 4) {
				if (6 <= j && j <= 9) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//카드
			if (0 <= i && i <= 3) {
				if (10 <= j && j <= 13) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE1);
				}
			}

			//카드아래 가림막
			if (4 <= i && i <= 7) {
				if (11 <= j && j <= 13) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE2);
				}
			}

			//주의나무판자1
			if (6 <= i && i <= 7) {
				if (5 <= j && j <= 6) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE3);
				}
			}
			//주의나무판자2
			if (6 <= i && i <= 7) {
				if (7 <= j && j <= 8) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE4);
				}
			}
			//주의나무판자3
			if (6 <= i && i <= 7) {
				if (9 <= j && j <= 10) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE5);
				}
			}

			//오지못하게하는 철대
			if (6 <= i && i <= 7) {
				if (1 <= j && j <= 4) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (1 <= j && j <= 4) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//오지못하게하는 철대2
			if (6 <= i && i <= 10) {
				if (j == 0) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//가림막덩이1
			if (8 <= i && i <= 10) {
				if (1 <= j && j <= 3) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE6);
				}
			}
			//가림막덩이2
			if (8 <= i && i <= 11) {
				if (4 <= j && j <= 6) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE7);
				}
			}
			//가림막덩이3
			if (8 <= i && i <= 10) {
				if (7 <= j && j <= 8) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE8);
				}
			}
			//가림막덩이4
			if (8 <= i && i <= 10) {
				if (9 <= j && j <= 10) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE9);
				}
			}
			//가림막덩이5
			if (11 <= i && i <= 13) {
				if (0 <= j && j <= 3) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE10);
				}
			}

			//유리?
			if (i == 13) {
				if (4 <= j && j <= 12) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 12) {
				if (4 <= j && j <= 12) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//유리판자?
			if (10 <= i && i <= 11) {
				if (11 <= j && j <= 13) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//2페이지
			//가림막
			if (0 <= i && i <= 3) {
				if (14 <= j && j <= 17) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE11);
				}
			}
			if (0 <= i && i <= 3) {
				if (18 <= j && j <= 21) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE12);
				}
			}
			if (0 <= i && i <= 3) {
				if (22 <= j && j <= 24) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE13);
				}
			}

			if (11 <= i && i <= 12) {
				if (14 <= j && j <= 16) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE89);
				}
			}


			//큰다리
			if (4 <= i && i <= 10) {
				if (14 <= j && j <= 21) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 10) {
				if (14 <= j && j <= 15) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 10) {
				if (20 <= j && j <= 21) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//돌상자?
			if (4 <= i && i <= 5) {
				if (22 <= j && j <= 25) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (6 <= i && i <= 7) {
				if (22 <= j && j <= 25) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//보스동상
			if (8 <= i && i <= 10) {
				if (22 <= j && j <= 23) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE14);
				}
			}
			//보스동상
			if (8 <= i && i <= 10) {
				if (24 <= j && j <= 25) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE15);
				}
			}
			//보스동상
			if (8 <= i && i <= 10) {
				if (26 <= j && j <= 27) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE16);
				}
			}
			//보스동상
			if (11 <= i && i <= 12) {
				if (22 <= j && j <= 23) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE17);
				}
			}

			//3페이지 - 마법진
			if (0 <= i && i <= 13) {
				if (28 <= j && j <= 41) {
					_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_TILE][COMMON_TILE][i][j]->setTopTileAttr(TILE_FLOOR);
				}
			}

			//4페이지
			//위저드 동상
			if (0 <= i && i <= 4) {
				if (42 <= j && j <= 51) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 4) {
				if (42 <= j && j <= 51) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//마법진돌?
			if (0 <= i && i <= 3) {
				if (52 <= j && j <= 55) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//기둥?
			if (4 <= i && i <= 7) {
				if (53 <= j && j <= 55) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (53 <= j && j <= 55) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//2줄짜리 길?뭐야이거
			if (5 <= i && i <= 6) {
				if (49 <= j && j <= 52) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//철담벼락길?
			if (5 <= i && i <= 6) {
				if (42 <= j && j <= 48) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 6) {
				if (42 <= j && j <= 48) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}


			//기둥
			if (7 <= i && i <= 11) {
				if (42 <= j && j <= 43) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 11) {
				if (42 <= j && j <= 43) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//공원의자
			if (7 <= i && i <= 8) {
				if (44 <= j && j <= 46) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//1장짜리 마법진?
			if (i == 7) {
				if (j == 47) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//거울
			if (9 <= i && i <= 11) {
				if (44 <= j && j <= 46) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE18);
				}
			}

			//동상세우는데?
			if (9 <= i && i <= 11) {
				if (47 <= j && j <= 50) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//동상세우는데?2
			if (8 <= i && i <= 11) {
				if (51 <= j && j <= 54) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//5페이지
			//긴의자
			if (0 <= i && i <= 3) {
				if (56 <= j && j <= 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//길막기둥?
			if (4 <= i && i <= 6) {
				if (56 <= j && j <= 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 6) {
				if (56 <= j && j <= 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 5) {
				if (60 <= j && j <= 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 4) {
				if (j == 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//철문
			if (0 <= i && i <= 2) {
				if (62 <= j && j <= 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//길막
			if (0 <= i && i <= 6) {
				if (j == 66) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//의자
			if (0 <= i && i <= 3) {
				if (67 <= j && j <= 68) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//의자2
			if (4 <= i && i <= 7) {
				if (67 <= j && j <= 68) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//책
			if (i == 3) {
				if (63 <= j && j <= 64) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE19);
				}
			}
			//문서?
			if (i == 4) {
				if (j == 62) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE20);
				}
			}
			//빨간책
			if (4 <= i && i <= 5) {
				if (64 <= j && j <= 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE21);
				}
			}
			//빨간책
			if (5 <= i && i <= 6) {
				if (62 <= j && j <= 63) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE22);
				}
			}

			//작은식물?
			if (i == 7) {
				if (j == 56) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE23);
				}
			}
			if (i == 7) {
				if (j == 57) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE24);
				}
			}
			if (i == 7) {
				if (j == 58) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE25);
				}
			}
			//식물 중간짜리?
			if (7 <= i && i <= 8) {
				if (59 <= j && j <= 60) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE26);
				}
			}
			if (7 <= i && i <= 8) {
				if (61 <= j && j <= 62) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE27);
				}
			}

			//작은장미
			if (i == 7) {
				if (j == 63) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE28);
				}
			}
			if (i == 7) {
				if (j == 64) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE29);
				}
			}
			if (i == 7) {
				if (j == 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE30);
				}
			}
			if (i == 8) {
				if (j == 64) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE31);
				}
			}
			if (i == 8) {
				if (j == 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE32);
				}
			}
			if (i == 9) {
				if (j == 64) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE33);
				}
			}
			if (i == 9) {
				if (j == 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE34);
				}
			}

			//나침반?
			if (i == 8) {
				if (j == 56) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE35);
				}
			}
			if (i == 8) {
				if (j == 58) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE36);
				}
			}
			if (i == 9) {
				if (j == 56) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE37);
				}
			}

			//나침반?
			if (8 <= i && i <= 9) {
				if (j == 57) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE38);
				}
			}
			if (i == 9) {
				if (j == 58) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE39);
				}
			}
			if (i == 9) {
				if (j == 59) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE40);
				}
			}
			//뭐지 초코칩 쏟은건가
			if (i == 10) {
				if (56 <= j && j <= 57) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE41);
				}
			}
			if (i == 10) {
				if (j == 58) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE42);
				}
			}
			if (i == 10) {
				if (j == 59) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE43);
				}
			}
			//중간접시?
			if (9 <= i && i <= 10) {
				if (60 <= j && j <= 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE44);
				}
			}
			//작은해골바가지
			if (i == 9) {
				if (j == 62) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE45);
				}
			}
			//접시
			if (10 <= i && i <= 11) {
				if (62 <= j && j <= 63) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE46);
				}
			}
			//마법진이 왜여깃을까
			if (11 <= i && i <= 12) {
				if (56 <= j && j <= 58) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE47);
				}
			}
			if (11 <= i && i <= 12) {
				if (j == 59) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE48);
				}
			}
			//방패검?
			if (11 <= i && i <= 12) {
				if (60 <= j && j <= 61) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE49);
				}
			}
			//책쌓아놓은거
			if (12 <= i && i <= 13) {
				if (62 <= j && j <= 63) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE50);
				}
			}
			if (12 <= i && i <= 13) {
				if (64 <= j && j <= 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE51);
				}
			}
			//간판?
			if (10 <= i && i <= 11) {
				if (64 <= j && j <= 65) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE52);
				}
			}

			//책쌓아놓은거
			if (8 <= i && i <= 10) {
				if (66 <= j && j <= 67) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE53);
				}
			}
			//책쌓아놓은거2
			if (8 <= i && i <= 10) {
				if (68 <= j && j <= 69) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE54);
				}
			}
			//책쌓아놓은거2
			if (i == 11) {
				if (j == 67) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE55);
				}
			}
			if (i == 11) {
				if (j == 68) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE56);
				}
			}
			if (i == 11) {
				if (j == 69) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE57);
				}
			}

			if (11 <= i && i <= 12) {
				if (j == 66) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE58);
				}
			}
			if (12 <= i && i <= 13) {
				if (67 <= j && j <= 68) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE59);
				}
			}

			//6페이지
			//담벼락세트?
			if (0 <= i && i <= 6) {
				if (70 <= j && j <= 76) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (0 <= i && i <= 2) {
				if (72 <= j && j <= 74) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (3 <= i && i <= 4) {
				if (71 <= j && j <= 75) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//책들
			if (0 <= i && i <= 2) {
				if (77 <= j && j <= 79) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE60);
				}
			}
			if (0 <= i && i <= 1) {
				if (80 <= j && j <= 81) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE61);
				}
			}
			//쓰레기들?
			if (i == 0) {
				if (82 <= j && j <= 83) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE62);
				}
			}
			if (i == 1) {
				if (82 <= j && j <= 83) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE63);
				}
			}
			//나무더미
			if (2 <= i && i <= 3) {
				if (80 <= j && j <= 82) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE64);
				}
			}
			//나무
			if (3 <= i && i <= 5) {
				if (77 <= j && j <= 79) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE65);
				}
			}
			if (6 <= i && i <= 7) {
				if (77 <= j && j <= 79) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE66);
				}
			}
			//빈상자
			if (4 <= i && i <= 6) {
				if (80 <= j && j <= 81) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE67);
				}
			}
			//물건4개잇는곳
			if (i == 4) {
				if (j == 82) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE68);
				}
			}
			if (i == 5) {
				if (j == 82) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE69);
				}
			}
			if (i == 6) {
				if (j == 82) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE70);
				}
			}
			if (i == 6) {
				if (j == 83) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE71);
				}
			}
			//항아리
			if (7 <= i && i <= 8) {
				if (70 <= j && j <= 71) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE72);
				}
			}

			//담는통?
			if (7 <= i && i <= 9) {
				if (72 <= j && j <= 74) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (72 <= j && j <= 74) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//항아리2
			if (7 <= i && i <= 9) {
				if (75 <= j && j <= 77) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (75 <= j && j <= 76) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//풍선
			if (10 <= i && i <= 13) {
				if (70 <= j && j <= 71) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//돌문양
			if (10 <= i && i <= 11) {
				if (72 <= j && j <= 74) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//쓰레기통?
			if (10 <= i && i <= 11) {
				if (75 <= j && j <= 76) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//돌문양
			if (12 <= i && i <= 13) {
				if (72 <= j && j <= 75) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//빨간깃발?
			if (10 <= i && i <= 11) {
				if (j == 77) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//풍선
			if (8 <= i && i <= 12) {
				if (78 <= j && j <= 83) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//7페이지
			//빅건물
			if (0 <= i && i <= 13) {
				if (84 <= j && j <= 97) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (0 <= i && i <= 7) {
				if (84 <= j && j <= 92) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (84 <= j && j <= 85) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (91 <= j && j <= 92) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//포장마차?
			if (8 <= i && i <= 12) {
				if (84 <= j && j <= 89) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//깃발들
			if (8 <= i && i <= 13) {
				if (90 <= j && j <= 95) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//동상
			if (7 <= i && i <= 8) {
				if (96 <= j && j <= 97) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (4 <= i && i <= 6) {
				if (96 <= j && j <= 97) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//도르레
			if (5 <= i && i <= 6) {
				if (93 <= j && j <= 95) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE73);
				}
			}

			//우편봉투?
			if (9 <= i && i <= 10) {
				if (96 <= j && j <= 97) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE74);
				}
			}

			//검
			if (0 <= i && i <= 2) {
				if (j == 93) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE75);
				}
			}
			if (0 <= i && i <= 2) {
				if (j == 94) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_FURNITURE76);
				}
			}

			//8페이지

			if (0 <= i && i <= 13) {
				if (98 <= j && j <= 111) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			if (0 <= i && i <= 3) {
				if (98 <= j && j <= 103) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//천덮힌탁자?
			if (5 <= i && i <= 6) {
				if (98 <= j && j <= 99) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 4) {
				if (98 <= j && j <= 99) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			//천덮힌탁자2
			if (4 <= i && i <= 6) {
				if (100 <= j && j <= 103) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//빨간탁자
			if (8 <= i && i <= 10) {
				if (98 <= j && j <= 106) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(false);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (i == 7) {
				if (98 <= j && j <= 106) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}
			if (4 <= i && i <= 7) {
				if (107 <= j && j <= 111) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}

			//시작지점
			if (4 <= i && i <= 7) {
				if (107 <= j && j <= 111) {
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setIsAvailMove(true);
					_totalSamples[SELECT_OBJ][COMMON_OBJ][i][j]->setTopObjAttr(OBJ_UNBREAKABLE);
				}
			}






		}	//	for j end
	}	//	for i end

	//earth 타일 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ1] = { 0,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ1] = { 13,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ2] = { 14,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ2] = { 27,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ3] = { 28,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ3] = { 41,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ4] = { 42,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ4] = { 55,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ5] = { 56,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ5] = { 69,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ6] = { 70,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ6] = { 83,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ7] = { 84,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ7] = { 97,13 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][0][COMMONOBJ8] = { 98,0 };
		_totalFrameIdx[SELECT_OBJ][COMMON_OBJ][1][COMMONOBJ8] = { 111,13 };
	}
}

void mapEditor::InitSampleCommonEnemy()
{
	for (int i = 0; i <= IMAGEMANAGER->findImage("enemyCommon")->getMaxFrameY(); i++)
	{
		for (int j = 0; j <= IMAGEMANAGER->findImage("enemyCommon")->getMaxFrameX(); j++)
		{
			_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j] = new tile;
			SetNewSampleObj(_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j], j, i);
			_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setTopObjImage(IMAGEMANAGER->findImage("enemyCommon"));
			_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setTopObjImgKey("enemyCommon");

			if (0 <= j && j <= 3) {
				_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setIsAvailMove(true);
				_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setTopObjAttr(UNIT_GHOUL);
			}
			else if (4 <= j && j <= 7) {
				_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setIsAvailMove(true);
				_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setTopObjAttr(UNIT_KNIGHT);

			}
			else if (8 <= j && j <= 11) {
				_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setIsAvailMove(true);
				_totalSamples[SELECT_UNIT][COMMON_UNIT][i][j]->setTopObjAttr(UNIT_LANCER);
			}
		}
	}

	//common Enemy 시작/끗 프레임인덱스 이닛
	{
		_totalFrameIdx[SELECT_UNIT][COMMON_UNIT][0][COMMON_ENEMY1] = { 0,0 };
		_totalFrameIdx[SELECT_UNIT][COMMON_UNIT][1][COMMON_ENEMY1] = { 11,4 };
	}
}

void mapEditor::OverlayClickFunc()
{
	//버튼들 오버레이
	for (int i = 0; i < E_BUTTONS_END; i++) {
		if (i == SAVE || i == LOAD)
		{
			_buttons[i].frameY = 0;
			if (PtInRect(&_buttons[i].rc, _ptMouse)) {
				_buttons[i].frameY = 1;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == SAVE) SaveFunc();
					if (i == LOAD) LoadFunc();
				}
			}
		}
		else if (i == AREAMODE || i == ERASE_TILE || i == ERASE || i == ERASE_OBJ)
		{
			if (PtInRect(&_buttons[i].rc, _ptMouse))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					switch (i)
					{
					case AREAMODE:
						_isAreaMode = !_isAreaMode;
						if (_isAreaMode) _buttons[i].frameY = 1;
						else             _buttons[i].frameY = 0;

						break;
					case ERASE_TILE:
						_isEraseTile = !_isEraseTile;
						if (_isEraseTile) _buttons[i].frameY = 1;
						else             _buttons[i].frameY = 0;

						break;
					case ERASE:
						_isErase = !_isErase;
						if (_isErase) _buttons[i].frameY = 1;
						else          _buttons[i].frameY = 0;
						break;

					case ERASE_OBJ:
						_isEraseObj = !_isEraseObj;
						if (_isEraseObj) _buttons[i].frameY = 1;
						else             _buttons[i].frameY = 0;

						break;
						//	안씀. UNIT하고 오브젝하고 혼종이되었음
						//case ERASE_UNIT:
						//	_isEraseUnit = !_isEraseUnit;
						//	if (_isEraseUnit) _buttons[i].frameY = 1;
						//	else             _buttons[i].frameY = 0;
						//
						//	break;
					}
				}
			}
		}
		else if (i == TILES) {
			if (PtInRect(&_buttons[i].rc, _ptMouse))
			{

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_buttons[i].frameY = 1;
					_buttons[OBJECTS].frameY = 0;
					_buttons[UNITS].frameY = 0;
					_curSampleKind = SELECT_TILE;
					_curTileSampleIdx = 0;
				}
			}
		}
		else if (i == OBJECTS) {
			if (PtInRect(&_buttons[i].rc, _ptMouse))
			{

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_buttons[i].frameY = 1;
					_buttons[TILES].frameY = 0;
					_buttons[UNITS].frameY = 0;
					_curSampleKind = SELECT_OBJ;
					_curTileSampleIdx = 0;
				}
			}
		}
		else if (i == UNITS) {
			if (PtInRect(&_buttons[i].rc, _ptMouse))
			{

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_buttons[i].frameY = 1;
					_buttons[TILES].frameY = 0;
					_buttons[OBJECTS].frameY = 0;
					_curSampleKind = SELECT_UNIT;
					_curTileSampleIdx = 0;
				}
			}
		}


	}

	//tile/obj/unit의 종류(castle, ice..)버튼들 클릭
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < BTN_KINDS_END; j++) {
			if (PtInRect(&_kindButtons[i][j].rc, _ptMouse)) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					_kindButtons[i][j].isOn = true;
					//	프레임Y는 bool 값으로 대체하고있어서 안건들어도 적용됨.

					//	나머진 다 false;
					for (int ii = 0; ii < 3; ii++) {
						for (int jj = 0; jj < BTN_KINDS_END; jj++) {
							if (ii == i && jj == j) {
								continue;
							}
							else {
								_kindButtons[ii][jj].isOn = false;
							}
						}
					}


					//	tile / Obj / Unit도 자동으로 따라감
					switch (i) {
						//tile
					case 0:
						_curSampleKind = SELECT_TILE;
						_curTileSampleIdx = 0;

						//	tile/obj/unit 버튼들 따로 놀고있어서...어쩔수없이 직접 다 해줘야함
						_buttons[TILES].frameY = 1;
						_buttons[OBJECTS].frameY = 0;
						_buttons[UNITS].frameY = 0;


						if (j == BTN_CASTLE) { _curTileKind = CASTLE_TILE; }
						else if (j == BTN_ICE) { _curTileKind = ICE_TILE; }
						else if (j == BTN_FIRE) { _curTileKind = FIRE_TILE; }
						else if (j == BTN_EARTH) { _curTileKind = EARTH_TILE; }
						else if (j == BTN_COMMON) { _curTileKind = COMMON_TILE; }
						break;

						//obj
					case 1:
						_curSampleKind = SELECT_OBJ;
						_curTileSampleIdx = 0;

						//	tile/obj/unit 버튼들 따로 놀고있어서...어쩔수없이 직접 다 해줘야함
						_buttons[TILES].frameY = 0;
						_buttons[OBJECTS].frameY = 1;
						_buttons[UNITS].frameY = 0;

						if (j == BTN_CASTLE) { _curObjKind = CASTLE_OBJ; }
						else if (j == BTN_ICE) { _curObjKind = ICE_OBJ; }
						else if (j == BTN_FIRE) { _curObjKind = FIRE_OBJ; }
						else if (j == BTN_EARTH) { _curObjKind = EARTH_OBJ; }
						else if (j == BTN_COMMON) { _curObjKind = COMMON_OBJ; }
						break;

						//unit
					case 2:
						_curSampleKind = SELECT_UNIT;
						_curTileSampleIdx = 0;

						//	tile/obj/unit 버튼들 따로 놀고있어서...어쩔수없이 직접 다 해줘야함
						_buttons[TILES].frameY = 0;
						_buttons[OBJECTS].frameY = 0;
						_buttons[UNITS].frameY = 1;

						if (j == BTN_CASTLE) { _curUnitKind = CASTLE_UNIT; }
						else if (j == BTN_ICE) { _curUnitKind = ICE_UNIT; }
						else if (j == BTN_FIRE) { _curUnitKind = FIRE_UNIT; }
						else if (j == BTN_EARTH) { _curUnitKind = EARTH_UNIT; }
						else if (j == BTN_COMMON) { _curUnitKind = COMMON_UNIT; }
						break;

					}




				}

			}
		}
	}
}

void mapEditor::ArrowClickFunc()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (PtInRect(&_arrowButtons[i][j].rc, _ptMouse))
			{
				//	staykeydown떄문에 예외로 따로 처리
				if (j == ARROW_MAPSIZEX || j == ARROW_MAPSIZEY)
				{
					//	staykeydown 적용하는 애들부분
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						switch (j) {
						case ARROW_MAPSIZEX:
							if (i == 0) {
								if (IsRdyToResize()) {
									_tileNumX--;
									if (_tileNumX < 1) {
										_tileNumX = 1;

									}
									else {
										EraseMapX();
										_mapResizeCount = 0;

									}
								}



							}
							else if (i == 1) {
								if (IsRdyToResize())
								{
									_tileNumX++;
									AddMapX();
									_mapResizeCount = 0;
								}

							}
							break;


						case ARROW_MAPSIZEY:
							if (i == 0) {
								if (IsRdyToResize())
								{
									_tileNumY--;
									if (_tileNumY < 1) {
										_tileNumY = 1;

									}
									else {
										EraseMapY();
										_mapResizeCount = 0;
									}
								}


							}
							else if (i == 1) {
								if (IsRdyToResize())
								{
									_tileNumY++;
									AddMapY();
									_mapResizeCount = 0;
								}


							}

							break;
						}
					}
				} //	staykeydown 적용하는 애들부분 끗


				//	oncekeydown 적용하는 애들부분
				else {
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						//	왼쪽화살표
						if (i == 0) {
							switch (j)
							{
							case ARROW_AREAMODE:
								_curAreaIdx--;
								if (_curAreaIdx < 0)
									_curAreaIdx = 0;
								break;
							case ARROW_MAPIDX:
								_curMapIdx--;
								if (_curMapIdx < 0)
									_curMapIdx = 0;
								break;

								//case ARROW_MAPSIZEX:
								//	_tileNumX--;
								//	if (_tileNumX < 1) {
								//		_tileNumX = 1;
								//		break;
								//	}
								//		
								//	EraseMapX();
								//	break;
								//
								//case ARROW_MAPSIZEY:
								//	_tileNumY--;
								//	if (_tileNumY < 1) {
								//		_tileNumY = 1;
								//		break;
								//	}
								//	EraseMapY();
								//	break;

							case ARROW_TILES:
								//	현재 선택된거랑 일치할경우만 적용!
								if (_curSampleKind == SELECT_TILE) {
									_curTileSampleIdx--;
									//최대수제한(루프)
									if (_curTileSampleIdx < 0) {
										//캐슬타일중일경우,
										if (_curTileKind == CASTLE_TILE) {
											_curTileSampleIdx = CASTLETILE_KINDS_END - 1;
										}
										else if (_curTileKind == EARTH_TILE) {
											_curTileSampleIdx = EARTHTILE_KINDS_END - 1;
										}
										else if (_curTileKind == ICE_TILE) {
											_curTileSampleIdx = ICETILE_KINDS_END - 1;
										}
										else if (_curTileKind == FIRE_TILE) {
											_curTileSampleIdx = FIRETILE_KINDS_END - 1;
										}
										else if (_curTileKind == COMMON_TILE) {
											_curTileSampleIdx = COMMONTILE_KINDS_END - 1;
										}
									}

									//	==== if잘못걸려있어서 위와같이 수정함 ====
									//if (_curTileKind == CASTLE_TILE) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = CASTLETILE_KINDS_END - 1;
									//	}
									//}
									////어스타일일 경우
									//else if (_curTileKind == EARTH_TILE) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = EARTHTILE_KINDS_END - 1;
									//	}
									//}
									////추가 - 유형우
									//else if (_curTileKind == ICE_TILE) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = ICETILE_KINDS_END - 1;
									//	}
									//}
									//else if (_curTileKind == FIRE_TILE) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = FIRETILE_KINDS_END - 1;
									//	}
									//}
									//else if (_curTileKind == COMMON_TILE) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = COMMONTILE_KINDS_END - 1;
									//	}
									//}
									////	다른 종류 타일 추가시 여기에 추가
										//else if () {
										//
										//}
								}


								break;

							case ARROW_OBJECTS:
								//	현재 선택된거랑 일치할경우만 적용!
								if (_curSampleKind == SELECT_OBJ) {
									_curTileSampleIdx--;
									//최대수제한(루프)
									if (_curTileSampleIdx < 0) {
										if (_curObjKind == CASTLE_OBJ) {
											_curTileSampleIdx = CASTLEOBJ_KINDS_END - 1;
										}
										else if (_curObjKind == EARTH_OBJ) {
											_curTileSampleIdx = EARTHOBJ_KINDS_END - 1;
										}
										else if (_curObjKind == ICE_OBJ) {
											_curTileSampleIdx = ICEOBJ_KINDS_END - 1;
										}
										else if (_curObjKind == FIRE_OBJ) {
											_curTileSampleIdx = FIREOBJ_KINDS_END - 1;
										}
										else if (_curObjKind == COMMON_OBJ) {
											_curTileSampleIdx = COMMONOBJ_KINDS_END - 1;
										}

									}

									//캐슬오브제일경우
									//if (_curObjKind == CASTLE_OBJ) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = CASTLEOBJ_KINDS_END - 1;
									//	}
									//}
									//else if (_curObjKind == EARTH_OBJ) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = EARTHOBJ_KINDS_END - 1;
									//	}
									//}
									////추가 - 유형우
									//else if (_curObjKind == ICE_OBJ) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = ICEOBJ_KINDS_END - 1;
									//	}
									//}
									//else if (_curObjKind == FIRE_OBJ) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = FIREOBJ_KINDS_END - 1;
									//	}
									//}
									//else if (_curObjKind == COMMON_OBJ) {
									//	if (_curTileSampleIdx < 0) {
									//		_curTileSampleIdx = COMMONOBJ_KINDS_END - 1;
									//	}
									//}
									////어스오브제일경우

									//	다른 종류 타일 추가시 여기에 추가
								}
								break;

							case ARROW_UNITS:
								//	현재 선택된거랑 일치할경우만 적용!
								if (_curSampleKind == SELECT_UNIT) {
									_curTileSampleIdx--;
									if (_curTileSampleIdx < 0) {
										if (_curObjKind == COMMON_UNIT) {
											_curTileSampleIdx = COMMON_ENEMY_KINDS_END - 1;
										}
										//else if (_curObjKind == COMMON_UNIT) {
										//	_curTileSampleIdx = COMMON_ENEMY_KINDS_END - 1;
										//}
									}

								}
								break;
							}
						}
						//	오른쪽 화살표
						else if (i == 1)
						{
							switch (j)
							{
							case ARROW_AREAMODE:
								_curAreaIdx++;
								break;
							case ARROW_MAPIDX:
								_curMapIdx++;
								break;

								//case ARROW_MAPSIZEX:
								//	_tileNumX++;
								//	AddMapX();
								//	break;
								//
								//case ARROW_MAPSIZEY:
								//	_tileNumY++;
								//	AddMapY();
								//	break;

							case ARROW_TILES:
								//	현재 선택된거랑 일치할경우만 적용!
								if (_curSampleKind == SELECT_TILE) {
									_curTileSampleIdx++;
									//최대수제한(루프)
									//	캐슬타일중일경우,
									if (_curTileKind == CASTLE_TILE) {
										if (_curTileSampleIdx >= CASTLETILE_KINDS_END) {

											_curTileSampleIdx = 0;
										}
									}
									else if (_curTileKind == EARTH_TILE) {
										if (_curTileSampleIdx >= EARTHTILE_KINDS_END) {

											_curTileSampleIdx = 0;
										}
									}
									//추가 - 유형우
									else if (_curTileKind == ICE_TILE) {
										if (_curTileSampleIdx >= ICETILE_KINDS_END) {

											_curTileSampleIdx = 0;
										}
									}
									else if (_curTileKind == FIRE_TILE) {
										if (_curTileSampleIdx >= FIRETILE_KINDS_END) {

											_curTileSampleIdx = 0;
										}
									}
									else if (_curTileKind == COMMON_TILE) {
										if (_curTileSampleIdx >= COMMONTILE_KINDS_END) {

											_curTileSampleIdx = 0;
										}
									}
									//	다른 종류 타일 추가시 여기에 추가
										//else if () {
										//
										//}
								}
								break;

							case ARROW_OBJECTS:
								//	현재 선택된거랑 일치할경우만 적용!
								if (_curSampleKind == SELECT_OBJ) {
									_curTileSampleIdx++;
									//	캐슬오브제인경우,
									if (_curObjKind == CASTLE_OBJ) {

										if (_curTileSampleIdx >= CASTLEOBJ_KINDS_END) {
											_curTileSampleIdx = 0;
										}
									}
									else if (_curObjKind == EARTH_OBJ) {

										if (_curTileSampleIdx >= EARTHOBJ_KINDS_END) {
											_curTileSampleIdx = 0;
										}
									}
									else if (_curObjKind == ICE_OBJ) {

										if (_curTileSampleIdx >= ICEOBJ_KINDS_END) {
											_curTileSampleIdx = 0;
										}
									}
									else if (_curObjKind == FIRE_OBJ) {

										if (_curTileSampleIdx >= FIREOBJ_KINDS_END) {
											_curTileSampleIdx = 0;
										}
									}
									else if (_curObjKind == COMMON_OBJ) {

										if (_curTileSampleIdx >= COMMONOBJ_KINDS_END) {
											_curTileSampleIdx = 0;
										}
									}



									//	다른 종류 타일 추가시 여기에 추가
										//else if () {
										//
										//}
								}
								break;

							case ARROW_UNITS:
								//	현재 선택된거랑 일치할경우만 적용!
								if (_curSampleKind == SELECT_UNIT) {
									_curTileSampleIdx++;
									if (_curUnitKind == COMMON_UNIT) {
										if (_curTileSampleIdx >= COMMON_ENEMY_KINDS_END) {
											_curTileSampleIdx = 0;
										}
									}
								}
								break;
							}
						}
					}
				}	//	oncekeydown 적용하는 애들부분 end

			}
		}
	}
}

void mapEditor::EraseMapX()
{
	for (int i = 0; i < _tileNumY; i++) {
		_vvMap[i].pop_back();
	}

}

void mapEditor::EraseMapY()
{
	_vvMap.pop_back();

}

void mapEditor::AddMapX()
{

	for (int i = 0; i < _tileNumY; i++) {
		tile* tmpTile = new tile;
		SetNewTile(tmpTile, _tileNumX - 1, i);
		_vvMap[i].push_back(tmpTile);
	}

}

void mapEditor::AddMapY()
{
	vLine tmpLine;
	tmpLine.clear();
	for (int i = 0; i < _tileNumX; i++)
	{
		tile* tmpTile = new tile;
		SetNewTile(tmpTile, i, _tileNumY - 1);
		tmpLine.push_back(tmpTile);
	}
	_vvMap.push_back(tmpLine);

}

void mapEditor::CursorGetTileInfoFunc()
{
	//	맵쪽
	//if (PtInRect(&_mapZoneRc, _ptMouse)) {
	//	for (int i = 0; i < _tileNumY; i++) {
	//		for (int j = 0; j < _tileNumX; j++) {
	//			RECT camAdjustRc = _vvMap[i][j]->getTopTileRc();
	//			camAdjustRc.left -= _camLeftTop.x;
	//			camAdjustRc.right -= _camLeftTop.x;
	//			camAdjustRc.top -= _camLeftTop.y;
	//			camAdjustRc.bottom -= _camLeftTop.y;
	//			if (PtInRect(&camAdjustRc, _ptMouse)) {
	//				_currentCursorTileInfo = _vvMap[i][j];
	//			}
	//		}
	//	}
	//}

	if (PtInRect(&_mapZoneRc, _ptMouse)) {
		for (int i = _cameraIdxY - 2; i < _cameraIdxY + 25; i++)
		{
			for (int j = _cameraIdxX - 2; j < _cameraIdxX + 34; j++)
			{
				if (j < 0)continue;
				if (i < 0)continue;
				if (j >= _tileNumX)continue;
				if (i >= _tileNumY)continue;

				RECT camAdjustRc = _vvMap[i][j]->getTopTileRc();
				camAdjustRc.left -= _camLeftTop.x;
				camAdjustRc.right -= _camLeftTop.x;
				camAdjustRc.top -= _camLeftTop.y;
				camAdjustRc.bottom -= _camLeftTop.y;
				if (PtInRect(&camAdjustRc, _ptMouse)) {
					_currentCursorTileInfo = _vvMap[i][j];
				}
			}
		}
	}
}

void mapEditor::SampleRender()
{
	switch (_curSampleKind)
	{
		int xStartIdx;
		int yStartIdx;
		int xEndIdx;
		int yEndIdx;

		//타일인 경우,
	case SELECT_TILE:

		xStartIdx = _totalFrameIdx[_curSampleKind][_curTileKind][0][_curTileSampleIdx].x;
		yStartIdx = _totalFrameIdx[_curSampleKind][_curTileKind][0][_curTileSampleIdx].y;
		xEndIdx = _totalFrameIdx[_curSampleKind][_curTileKind][1][_curTileSampleIdx].x;
		yEndIdx = _totalFrameIdx[_curSampleKind][_curTileKind][1][_curTileSampleIdx].y;


		for (int i = yStartIdx; i <= yEndIdx; i++) {
			for (int j = xStartIdx; j <= xEndIdx; j++) {
				//_castleTileSampleImg->frameRender(getMemDC(), _sampleRc[0][0].left + (j-xStartIdx) * TOP_TILESIZE, _sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE, j, i);	//일단 죽여봄
				_totalSamples[_curSampleKind][_curTileKind][i][j]->getTopTileImg()->frameRender(getMemDC(),
					_sampleRc[0][0].left + (j - xStartIdx) * TOP_TILESIZE,
					_sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE,
					j, i);
			}
		}


		break;

		//오브제인경우,
	case SELECT_OBJ:

		xStartIdx = _totalFrameIdx[_curSampleKind][_curObjKind][0][_curTileSampleIdx].x;
		yStartIdx = _totalFrameIdx[_curSampleKind][_curObjKind][0][_curTileSampleIdx].y;
		xEndIdx = _totalFrameIdx[_curSampleKind][_curObjKind][1][_curTileSampleIdx].x;
		yEndIdx = _totalFrameIdx[_curSampleKind][_curObjKind][1][_curTileSampleIdx].y;

		for (int i = yStartIdx; i <= yEndIdx; i++) {
			for (int j = xStartIdx; j <= xEndIdx; j++) {
				//_castleTileSampleImg->frameRender(getMemDC(), _sampleRc[0][0].left + (j-xStartIdx) * TOP_TILESIZE, _sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE, j, i);	//일단 죽여봄
				_totalSamples[_curSampleKind][_curObjKind][i][j]->getTopObjImg()->frameRender(getMemDC(),
					_sampleRc[0][0].left + (j - xStartIdx) * TOP_TILESIZE,
					_sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE,
					j, i);
			}
		}

		break;

	case SELECT_UNIT:

		xStartIdx = _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].x;
		yStartIdx = _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].y;
		xEndIdx = _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].x;
		yEndIdx = _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].y;

		for (int i = yStartIdx; i <= yEndIdx; i++) {
			for (int j = xStartIdx; j <= xEndIdx; j++) {
				//_castleTileSampleImg->frameRender(getMemDC(), _sampleRc[0][0].left + (j-xStartIdx) * TOP_TILESIZE, _sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE, j, i);	//일단 죽여봄
				_totalSamples[_curSampleKind][_curUnitKind][i][j]->getTopObjImg()->frameRender(getMemDC(),
					_sampleRc[0][0].left + (j - xStartIdx) * TOP_TILESIZE,
					_sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE,
					j, i);
			}
		}

		break;

	}



}

//	더이상 건들필요없음
void mapEditor::SampleSelectedRectRender()
{
	int iStart = _cursorSampleIdx[0].y;
	int iEnd = _cursorSampleIdx[1].y;
	int jStart = _cursorSampleIdx[0].x;
	int jEnd = _cursorSampleIdx[1].x;
	int tempNum;

	if (iStart > iEnd) {
		tempNum = iStart;
		iStart = iEnd;
		iEnd = tempNum;
	}
	if (jStart > jEnd) {
		tempNum = jStart;
		jStart = jEnd;
		jEnd = tempNum;
	}



	for (int i = iStart; i <= iEnd; i++)
	{
		for (int j = jStart; j <= jEnd; j++)
		{
			_sampleMask->alphaRender(getMemDC(), _sampleRc[i][j].left, _sampleRc[i][j].top, SAMPLE_MASK_ALPHA);
		}
	}

}

void mapEditor::TextNumberRender()
{
	HFONT font, oldFont;
	char str[64];
	//font = CreateFont(
	//	40, //문자폭
	//	0, //문자 넓이
	//	40, //문자 기울기(실제로 기울어짐)
	//	0, //문자 방향
	//	600, //문자 굵기
	//	false, //bool형 문자 기울기(이탤릭체) true, false
	//	false, //bool형 문자 밑줄 true, false
	//	false, //bool형 문자 취소선 true, false
	//	DEFAULT_CHARSET, //문자포맷 셋팅
	//	0, //출력 정확도
	//	0, //클리핑 정확도
	//	0, //출력 퀄리티
	//	0, //자간
	//	TEXT("Calisto MT"));	//폰트
	SetBkMode(getMemDC(), TRANSPARENT);
	font = CreateFont(30, 0, 0, 0, 300, 0, 0, 0,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Calisto MT"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	RECT AreaIdxRc = RectMakeCenter(_buttons[AREAMODE].pos.x, _buttons[AREAMODE].pos.y + 40, 80, 30);
	sprintf_s(str, "%d", _curAreaIdx);
	DrawText(getMemDC(), str, strlen(str), &AreaIdxRc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT MapIdxRc = RectMakeCenter(_buttons[MAPIDX].pos.x, _buttons[MAPIDX].pos.y + 40, 80, 30);
	sprintf_s(str, "%d", _curMapIdx);
	DrawText(getMemDC(), str, strlen(str), &MapIdxRc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

}

void mapEditor::TileInfoRender()
{
	SetBkMode(getMemDC(), TRANSPARENT);
	char tmpStr[128];

	//	맵 인덱스
	sprintf_s(tmpStr, "MapIdx : [%d][%d]", _currentCursorTileInfo->getTopIdx().x, _currentCursorTileInfo->getTopIdx().y);
	TextOut(getMemDC(), INFO_SHOW_X, 300, tmpStr, strlen(tmpStr));
	//sprintf_s(tmpStr, "MapIdxY : [%d]", _currentCursorTileInfo->getTopIdx().y);
	//TextOut(getMemDC(), 1024, 320, tmpStr, strlen(tmpStr));
	sprintf_s(tmpStr, "AvailMove? : [%d]", _currentCursorTileInfo->getIsAvailMove());
	TextOut(getMemDC(), INFO_SHOW_X, 320, tmpStr, strlen(tmpStr));
	sprintf_s(tmpStr, "AreaIdx : [%d]", _currentCursorTileInfo->getAreaIdx());
	TextOut(getMemDC(), INFO_SHOW_X, 340, tmpStr, strlen(tmpStr));



	if (_currentCursorTileInfo->getTopTileImg() != nullptr) {

		string toptileImgName = _currentCursorTileInfo->getTopTileImgKey();
		//	이미지 이름
		TextOut(getMemDC(), INFO_SHOW_X, 380, toptileImgName.c_str(), strlen(toptileImgName.c_str()));



		//	타일 속성
		sprintf_s(tmpStr, "Tile Atr : ");
		TextOut(getMemDC(), INFO_SHOW_X, 400, tmpStr, strlen(tmpStr));
		switch (_currentCursorTileInfo->getTopTileAttr()) {
		case TILE_NONE:
			sprintf_s(tmpStr, "TILE_NONE");
			break;
		case TILE_FLOOR:
			sprintf_s(tmpStr, "TILE_FLOOR");
			break;
		case TILE_WALL:
			sprintf_s(tmpStr, "TILE_WALL");
			break;
		case TILE_HOLE:
			sprintf_s(tmpStr, "TILE_HOLE");
			break;

		}
		TextOut(getMemDC(), INFO_SHOW_X, 420, tmpStr, strlen(tmpStr));

		//	타일프레임
		sprintf_s(tmpStr, "Tile frameX : %d", _currentCursorTileInfo->getTopTileFrameX());
		TextOut(getMemDC(), INFO_SHOW_X, 440, tmpStr, strlen(tmpStr));
		sprintf_s(tmpStr, "Tile frameY : %d", _currentCursorTileInfo->getTopTileFrameY());
		TextOut(getMemDC(), INFO_SHOW_X, 460, tmpStr, strlen(tmpStr));
	}



	if (_currentCursorTileInfo->getTopObjImg() != nullptr) {
		sprintf_s(tmpStr, "============");
		TextOut(getMemDC(), INFO_SHOW_X, 480, tmpStr, strlen(tmpStr));

		string topObjImgName = _currentCursorTileInfo->getTopObjImgKey();
		TextOut(getMemDC(), INFO_SHOW_X, 500, topObjImgName.c_str(), strlen(topObjImgName.c_str()));

		//	d오브제 속성
		sprintf_s(tmpStr, "Obj Atr : ");
		TextOut(getMemDC(), INFO_SHOW_X, 520, tmpStr, strlen(tmpStr));
		switch (_currentCursorTileInfo->getTopObjAttr()) {
		case OBJ_NONE:
			sprintf_s(tmpStr, "OBJ_NONE");
			break;
		case OBJ_BREAKABLE:
			sprintf_s(tmpStr, "OBJ_BREAKABLE");
			break;
		case OBJ_UNBREAKABLE:
			sprintf_s(tmpStr, "OBJ_UNBREAKABLE");
			break;
		case OBJ_CANDLE:
			sprintf_s(tmpStr, "OBJ_CANDLE");
			break;
		default:
			sprintf_s(tmpStr, "ATRNUM [%d]", _currentCursorTileInfo->getTopObjAttr());
			break;

		}
		TextOut(getMemDC(), INFO_SHOW_X, 540, tmpStr, strlen(tmpStr));

		//	타일프레임
		sprintf_s(tmpStr, "Obj frameX : %d", _currentCursorTileInfo->getTopObjFrameX());
		TextOut(getMemDC(), INFO_SHOW_X, 560, tmpStr, strlen(tmpStr));
		sprintf_s(tmpStr, "Obj frameY : %d", _currentCursorTileInfo->getTopObjFrameY());
		TextOut(getMemDC(), INFO_SHOW_X, 580, tmpStr, strlen(tmpStr));


	}




}

void mapEditor::AreaIdxRender()
{



	for (int i = _cameraIdxY - 2; i < _cameraIdxY + 25; i++)
	{
		for (int j = _cameraIdxX - 2; j < _cameraIdxX + 34; j++)
		{
			if (j < 0)continue;
			if (i < 0)continue;
			if (j >= _tileNumX)continue;
			if (i >= _tileNumY)continue;

			char str[128];
			sprintf_s(str, "[%d]", _vvMap[i][j]->getAreaIdx());
			TextOut(getMemDC(),
				_vvMap[i][j]->getTopTileRc().left - _camLeftTop.x,
				_vvMap[i][j]->getTopTileRc().top - _camLeftTop.y,
				str, strlen(str));

		}
	}
}

void mapEditor::PreviewSampleRender()
{
	//_cursorMapIdx.x = j;
	//_cursorMapIdx.y = i;
	int iStart = _cursorSampleIdx[0].y;
	int iEnd = _cursorSampleIdx[1].y;
	int jStart = _cursorSampleIdx[0].x;
	int jEnd = _cursorSampleIdx[1].x;
	int tempNum;

	if (iStart > iEnd) {
		tempNum = iStart;
		iStart = iEnd;
		iEnd = tempNum;
	}
	if (jStart > jEnd) {
		tempNum = jStart;
		jStart = jEnd;
		jEnd = tempNum;
	}


	for (int i = iStart; i <= iEnd; i++)
	{
		for (int j = jStart; j <= jEnd; j++)
		{
			if (_curSampleKind == SELECT_TILE) {

				//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				int adjustIdxY = i + _totalFrameIdx[_curSampleKind][_curTileKind][0][_curTileSampleIdx].y;
				int adjustIdxX = j + _totalFrameIdx[_curSampleKind][_curTileKind][0][_curTileSampleIdx].x;

				//조절된 실제 이미지의 프레임계산값이, 해당페이지의 시작/끝 프레임수에서 벗어난다면, 예외처리.
				if (adjustIdxY < _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].y
					|| adjustIdxY > _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].y)	continue;
				if (adjustIdxX < _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].x
					|| adjustIdxX > _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].x)	continue;

				//	뿌려줄 좌표 위치계산
				POINT pos = { (_cursorMapIdx.x + (j - jStart)) * TOP_TILESIZE - _camLeftTop.x,
							(_cursorMapIdx.y + (i - iStart)) * TOP_TILESIZE - _camLeftTop.y };
				//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];

				//	터지는거 방지용
				if (_totalSamples[_curSampleKind][_curTileKind][adjustIdxY][adjustIdxX]->getTopTileImg() == nullptr) continue;

				_totalSamples[_curSampleKind][_curTileKind][adjustIdxY][adjustIdxX]->AlphaFrameRender(pos.x, pos.y, PREVIEW_ALPHA);


			}
			else if (_curSampleKind == SELECT_OBJ) {

				//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				int adjustIdxY = i + _totalFrameIdx[_curSampleKind][_curObjKind][0][_curTileSampleIdx].y;
				int adjustIdxX = j + _totalFrameIdx[_curSampleKind][_curObjKind][0][_curTileSampleIdx].x;

				//조절된 실제 이미지의 프레임계산값이, 해당페이지의 시작/끝 프레임수에서 벗어난다면, 예외처리.
				if (adjustIdxY < _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].y
					|| adjustIdxY > _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].y)	continue;
				if (adjustIdxX < _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].x
					|| adjustIdxX > _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].x)	continue;


				//	뿌려줄 좌표 위치계산
				POINT pos = { (_cursorMapIdx.x + (j - jStart)) * TOP_TILESIZE - _camLeftTop.x,
							(_cursorMapIdx.y + (i - iStart)) * TOP_TILESIZE - _camLeftTop.y };
				//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];

				//	터지는거 방지용
				if (_totalSamples[_curSampleKind][_curObjKind][adjustIdxY][adjustIdxX]->getTopObjImg() == nullptr) continue;

				_totalSamples[_curSampleKind][_curObjKind][adjustIdxY][adjustIdxX]->AlphaFrameRender(pos.x, pos.y, PREVIEW_ALPHA);


			}
			else if (_curSampleKind == SELECT_UNIT) {

				//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				int adjustIdxY = i + _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].y;
				int adjustIdxX = j + _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].x;

				//조절된 실제 이미지의 프레임계산값이, 해당페이지의 시작/끝 프레임수에서 벗어난다면, 예외처리.
				if (adjustIdxY < _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].y
					|| adjustIdxY > _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].y)	continue;
				if (adjustIdxX < _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].x
					|| adjustIdxX > _totalFrameIdx[_curSampleKind][_curUnitKind][1][_curTileSampleIdx].x)	continue;

				//	뿌려줄 좌표 위치계산
				POINT pos = { (_cursorMapIdx.x + (j - jStart)) * TOP_TILESIZE - _camLeftTop.x,
							(_cursorMapIdx.y + (i - iStart)) * TOP_TILESIZE - _camLeftTop.y };
				//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];

				//	터지는거 방지용
				if (_totalSamples[_curSampleKind][_curUnitKind][adjustIdxY][adjustIdxX]->getTopObjImg() == nullptr) continue;

				_totalSamples[_curSampleKind][_curUnitKind][adjustIdxY][adjustIdxX]->AlphaFrameRender(pos.x, pos.y, PREVIEW_ALPHA);


			}


		}
	}


}

void mapEditor::CursorSampleSelectFunc()
{
	if (_isCursorSelected == false) {
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 14; j++) {
				if (PtInRect(&_sampleRc[i][j], _ptMouse))
				{
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_cursorSampleIdx[0] = { j,i };
						_cursorSampleIdx[1] = { j,i };
						_isClickDown = true;
					}
					if (_isClickDown)
					{
						_cursorSampleIdx[1] = { j,i };
					}
					if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
					{
						_isClickDown = false;
					}
				}
			}
		}
	}


}

void mapEditor::CursorClickOnMap()
{
	if (PtInRect(&_mapZoneRc, _ptMouse))
	{
		for (int i = 0; i < _tileNumY; i++)
		{
			for (int j = 0; j < _tileNumX; j++)
			{
				RECT camAdjustRc = _vvMap[i][j]->getTopTileRc();
				camAdjustRc.left -= _camLeftTop.x;
				camAdjustRc.right -= _camLeftTop.x;
				camAdjustRc.top -= _camLeftTop.y;
				camAdjustRc.bottom -= _camLeftTop.y;
				//if (PtInRect(&_vvMap[i][j]->getTopTileRc(), _ptMouse))
				if (PtInRect(&camAdjustRc, _ptMouse))
				{
					_cursorMapIdx.x = j;
					_cursorMapIdx.y = i;



					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					{

						if (!_isErase && !_isEraseTile && !_isEraseObj)
						{
							CursorAdjustOnMap();
						}
						else if (_isErase)
						{
							CursorEraseMap(_vvMap[i][j]);
						}
						if (_isEraseTile)
						{
							CursorEraseTile(_vvMap[i][j]);
						}
						if (_isEraseObj)
						{
							CursorEraseObj(_vvMap[i][j]);
						}

					}
				}
			}
		}
	}

}


void mapEditor::CursorAdjustOnMap()
{
	//i,j는 드래그해서 얻은 샘플들의 인덱스
	int iStart = _cursorSampleIdx[0].y;
	int iEnd = _cursorSampleIdx[1].y;
	int jStart = _cursorSampleIdx[0].x;
	int jEnd = _cursorSampleIdx[1].x;
	int tempNum;
	//	맵인덱스는 내가 클릭했을때 얻은 맵벡터의 인덱스
	int mapIdxX = _cursorMapIdx.x;
	int mapIdxY = _cursorMapIdx.y;

	if (iStart > iEnd) {
		tempNum = iStart;
		iStart = iEnd;
		iEnd = tempNum;
	}
	if (jStart > jEnd) {
		tempNum = jStart;
		jStart = jEnd;
		jEnd = tempNum;
	}

	for (int i = iStart; i <= iEnd; i++)
	{
		for (int j = jStart; j <= jEnd; j++)
		{
			//	맵 벡터 밖으로 나가는것 방지
			if (mapIdxY + (i - iStart) > _tileNumY - 1 || mapIdxX + (j - jStart) > _tileNumX - 1)
				continue;


			if (_curSampleKind == SELECT_TILE) {

				//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				int adjustIdxY = i + _totalFrameIdx[_curSampleKind][_curTileKind][0][_curTileSampleIdx].y;
				int adjustIdxX = j + _totalFrameIdx[_curSampleKind][_curTileKind][0][_curTileSampleIdx].x;
				//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];
				TransTileSampleToMap(_totalSamples[_curSampleKind][_curTileKind][adjustIdxY][adjustIdxX], _vvMap[mapIdxY + (i - iStart)][mapIdxX + (j - jStart)]);	//	오브제를 전송하는건지, 타일전송하는건지 구분!


			}
			else if (_curSampleKind == SELECT_OBJ) {

				//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				int adjustIdxY = i + _totalFrameIdx[_curSampleKind][_curObjKind][0][_curTileSampleIdx].y;
				int adjustIdxX = j + _totalFrameIdx[_curSampleKind][_curObjKind][0][_curTileSampleIdx].x;
				//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];
				TransObjSampleToMap(_totalSamples[_curSampleKind][_curObjKind][adjustIdxY][adjustIdxX], _vvMap[mapIdxY + (i - iStart)][mapIdxX + (j - jStart)]);	//	오브제를 전송하는건지, 타일전송하는건지 구분!


				//if (_curObjKind == CASTLE_OBJ) {
				//	//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				//	int adjustIdxY = i + _castleObjFrameIdx[0][_curTileSampleIdx].y;	
				//	int adjustIdxX = j + _castleObjFrameIdx[0][_curTileSampleIdx].x;
				//	//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//	//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];
				//	TransObjSampleToMap(_castleObjSample[adjustIdxY][adjustIdxX], _vvMap[mapIdxY + (i - iStart)][mapIdxX + (j - jStart)]);		//	오브제를 전송하는건지, 타일전송하는건지 구분!
				//	
				//}
				//elseif(다른타일)		//다른 타일이면, === 타일 추가시 여기에 추가 ===
			}
			else if (_curSampleKind == SELECT_UNIT) {

				//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
				int adjustIdxY = i + _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].y;
				int adjustIdxX = j + _totalFrameIdx[_curSampleKind][_curUnitKind][0][_curTileSampleIdx].x;
				//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
				//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];
				TransObjSampleToMap(_totalSamples[_curSampleKind][_curUnitKind][adjustIdxY][adjustIdxX], _vvMap[mapIdxY + (i - iStart)][mapIdxX + (j - jStart)]);	//	오브제를 전송하는건지, 타일전송하는건지 구분!

			}

		}
	}



}

void mapEditor::CursorEraseMap(tile * mapTile)
{

	mapTile->setTopTileImage(nullptr);
	mapTile->setTopTileFrameX(0);
	mapTile->setTopTileFrameY(0);
	mapTile->setTopTileAttr(TILE_NONE);
	mapTile->setTopTileImgKey("none");

	mapTile->setTopObjImage(nullptr);
	mapTile->setTopObjFrameX(0);
	mapTile->setTopObjFrameY(0);
	mapTile->setTopObjAttr(OBJ_NONE);
	mapTile->setTopObjImgKey("none");



	mapTile->setIsAvailMove(false);

	mapTile->setAreaIdx(0);
}

void mapEditor::CursorEraseTile(tile * mapTile)
{
	mapTile->setTopTileImage(nullptr);
	mapTile->setTopTileFrameX(0);
	mapTile->setTopTileFrameY(0);
	mapTile->setTopTileAttr(TILE_NONE);
	mapTile->setTopTileImgKey("none");

	//mapTile->setTopObjImage(nullptr);
	//mapTile->setTopObjFrameX(0);
	//mapTile->setTopObjFrameY(0);
	//mapTile->setTopObjAttr(OBJ_NONE);
	//mapTile->setTopObjImgKey("none");



	mapTile->setIsAvailMove(false);

	mapTile->setAreaIdx(0);
}

void mapEditor::CursorEraseObj(tile * mapTile)
{
	//mapTile->setTopTileImage(nullptr);
	//mapTile->setTopTileFrameX(0);
	//mapTile->setTopTileFrameY(0);
	//mapTile->setTopTileAttr(TILE_NONE);
	//mapTile->setTopTileImgKey("none");

	mapTile->setTopObjImage(nullptr);
	mapTile->setTopObjFrameX(0);
	mapTile->setTopObjFrameY(0);
	mapTile->setTopObjAttr(OBJ_NONE);
	mapTile->setTopObjImgKey("none");



	//mapTile->setIsAvailMove(false);
	//
	//mapTile->setAreaIdx(0);
}

void mapEditor::TransTileSampleToMap(tile * sampleTile, tile * mapTile)
{
	if (sampleTile->getTopTileImg() == nullptr)	return;

	mapTile->setTopTileImage(sampleTile->getTopTileImg());
	mapTile->setTopTileFrameX(sampleTile->getTopTileFrameX());
	mapTile->setTopTileFrameY(sampleTile->getTopTileFrameY());
	mapTile->setTopTileAttr(sampleTile->getTopTileAttr());
	mapTile->setTopTileImgKey(sampleTile->getTopTileImgKey());

	mapTile->setIsAvailMove(sampleTile->getIsAvailMove());

	mapTile->setAreaIdx(_curAreaIdx);

}

void mapEditor::TransObjSampleToMap(tile * sampleTile, tile * mapTile)
{
	if (sampleTile->getTopObjImg() == nullptr)	return;

	mapTile->setTopObjImage(sampleTile->getTopObjImg());
	mapTile->setTopObjFrameX(sampleTile->getTopObjFrameX());
	mapTile->setTopObjFrameY(sampleTile->getTopObjFrameY());
	mapTile->setTopObjAttr(sampleTile->getTopObjAttr());
	mapTile->setTopObjImgKey(sampleTile->getTopObjImgKey());


	if (!mapTile->getIsAvailMove()) {
		if (sampleTile->getIsAvailMove()) {
			//	적용안함
		}
		else {
			//	적용함
			mapTile->setIsAvailMove(sampleTile->getIsAvailMove());
		}
	}
	else if (mapTile->getIsAvailMove()) {
		if (sampleTile->getIsAvailMove()) {
			//	적용함
			mapTile->setIsAvailMove(sampleTile->getIsAvailMove());
		}
		else {
			//	적용함
			mapTile->setIsAvailMove(sampleTile->getIsAvailMove());
		}

	}
	//mapTile->setIsAvailMove(sampleTile->getIsAvailMove());

	//mapTile->setAreaIdx(_curAreaIdx);
}

void mapEditor::CamMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		_camLeftTop.x -= CAM_MOVESPD;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		_camLeftTop.x += CAM_MOVESPD;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		_camLeftTop.y -= CAM_MOVESPD;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_camLeftTop.y += CAM_MOVESPD;
	}

}

void mapEditor::SaveFunc()
{
	HANDLE file;
	DWORD write;

	//itoa(무엇을, 어디에저장,몇진수?)
	//strcat_s(des, sizof(des), sour) '\0'에 붙여넣기

	char fileName[20] = "saveMap";
	char idxBuffer[5] = {};
	itoa(_curMapIdx, idxBuffer, 10);
	strcat_s(fileName, sizeof(fileName), idxBuffer);
	strcat_s(fileName, sizeof(fileName), ".map");



	// tilenumX] tilenumY]
	//	인덱스
	// tile - pos, rc, framex/y, attr, imgKey
	char save[5000000] = {};
	char token[100000] = {};
	char tmp[1000] = {};




	itoa(_tileNumX, tmp, 10);
	strcat_s(save, sizeof(save), tmp);
	strcat_s(save, sizeof(save), "]");

	itoa(_tileNumY, tmp, 10);
	strcat_s(save, sizeof(save), tmp);
	strcat_s(save, sizeof(save), "]");

	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {
			//	인덱스
			itoa((_vvMap[i][j]->getTopIdx().x), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	//	구분자추가
			itoa((_vvMap[i][j]->getTopIdx().y), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");	//	구분자추가

			//타일정보저장
			{
				//	Pos
				itoa((_vvMap[i][j]->getTopTilePos().x), tmp, 10);		//	tmp 에 char로 변경
				strcat_s(token, sizeof(token), tmp);	//	토큰에 넣고	
				strcat_s(token, sizeof(token), "/");	//	구분자추가

				itoa((_vvMap[i][j]->getTopTilePos().y), tmp, 10);		//	tmp 에 char로 변경
				strcat_s(token, sizeof(token), tmp);	//	토큰에 넣고	
				strcat_s(token, sizeof(token), "/");	//	구분자추가


				//	렉트
				itoa(_vvMap[i][j]->getTopTileRc().left, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가
				itoa(_vvMap[i][j]->getTopTileRc().top, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가
				itoa(_vvMap[i][j]->getTopTileRc().right, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가
				itoa(_vvMap[i][j]->getTopTileRc().bottom, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가


				//	tileframeX
				itoa(_vvMap[i][j]->getTopTileFrameX(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");
				//	tileframeY
				itoa(_vvMap[i][j]->getTopTileFrameY(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");

				//	타일속성
				itoa(_vvMap[i][j]->getTopTileAttr(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");

				//	이미지 키값
				strcat_s(token, sizeof(token), _vvMap[i][j]->getTopTileImgKey().c_str());
				strcat_s(token, sizeof(token), "/");
			}
			//	타일정보 저장 끝

			//	오브젝 정보 저장 - pos, rc, framex/y, attr, imgKey
			{
				//	Pos
				itoa((_vvMap[i][j]->getTopObjPos().x), tmp, 10);		//	tmp 에 char로 변경
				strcat_s(token, sizeof(token), tmp);	//	토큰에 넣고	
				strcat_s(token, sizeof(token), "/");	//	구분자추가

				itoa((_vvMap[i][j]->getTopObjPos().y), tmp, 10);		//	tmp 에 char로 변경
				strcat_s(token, sizeof(token), tmp);	//	토큰에 넣고	
				strcat_s(token, sizeof(token), "/");	//	구분자추가


				//	렉트
				itoa(_vvMap[i][j]->getTopObjRc().left, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가
				itoa(_vvMap[i][j]->getTopObjRc().top, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가
				itoa(_vvMap[i][j]->getTopObjRc().right, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가
				itoa(_vvMap[i][j]->getTopObjRc().bottom, tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");	//	구분자추가


				//	tileframeX
				itoa(_vvMap[i][j]->getTopObjFrameX(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");
				//	tileframeY
				itoa(_vvMap[i][j]->getTopObjFrameY(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");

				//	타일속성
				itoa(_vvMap[i][j]->getTopObjAttr(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");

				//	이미지 키값
				strcat_s(token, sizeof(token), _vvMap[i][j]->getTopObjImgKey().c_str());
				strcat_s(token, sizeof(token), "/");
			}

			//	isAvailMove
			itoa(_vvMap[i][j]->getIsAvailMove(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");

			//	AreaIdx
			itoa(_vvMap[i][j]->getAreaIdx(), tmp, 10);
			strcat_s(token, sizeof(token), tmp);
			strcat_s(token, sizeof(token), "/");



			strcat_s(save, sizeof(save), token);
			for (int i = 0; i < 10000; i++)
				token[i] = '\0';
		}

	}



	file = CreateFile(fileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, save, sizeof(save), &write, NULL);
	CloseHandle(file);
}

void mapEditor::LoadFunc()
{

	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {
			delete _vvMap[i][j];
			_vvMap[i][j] = nullptr;
		}
		_vvMap[i].clear();
	}
	_vvMap.clear();




	HANDLE file;
	DWORD read;

	//itoa(무엇을, 어디에저장,몇진수?)
	//strcat_s(des, sizof(des), sour) '\0'에 붙여넣기
	//잘린것 = strtok_s(무엇을 / seperator/ 남은거저장)
	//strtok_s 가 실행될떄마다 원본의 seperator 부분을 NULL로 만들어버린다.
	//연속해서 사용시, token = strtok_s(원본, seperator, &context)는 한번만 사용,
	//		  이후에는, token = strtok_s(NULL, seperator, &context)로 계속 진행한다.
	//	char* token , context 임에 유의.


	// tilenumX] tilenumY]
	// 인덱스
	// tile - pos, rc, framex/y, attr, imgKey
	char load[5000000] = {};
	char* token;			//1번 잘려진 문자열의 주소
	char* context;			//2번 잘려진 문자열의
	char tmp[10] = {};
	const char* seperator = "/";	//구분자
	char fileName[20] = "saveMap";
	//char tmpStr[128];
	int tmpInt;

	//	로드할 파일이름 설정
	itoa(_curMapIdx, tmp, 10);
	strcat_s(fileName, sizeof(fileName), tmp);
	strcat_s(fileName, sizeof(fileName), ".map");


	file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, load, sizeof(load), &read, NULL);
	CloseHandle(file);


	//	=== 여까지 load에 데이터 입력받은 상태 ===

	//	맵 크기 로드
	token = strtok_s(load, "]", &context);
	tmpInt = atoi(token);
	_tileNumX = tmpInt;
	token = strtok_s(NULL, "]", &context);
	tmpInt = atoi(token);
	_tileNumY = tmpInt;

	tile* tmpTile;
	// tile - pos, rc, framex/y, attr, imgKey
	for (int i = 0; i < _tileNumY; i++) {
		vLine vLineX;
		vLineX.clear();
		for (int j = 0; j < _tileNumX; j++) {
			tmpTile = new tile;
			//	인덱스
			POINT tmpIdx;

			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpIdx.x = tmpInt;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpIdx.y = tmpInt;
			tmpTile->setTopIdx(tmpIdx);

			// 타일정보 로드 - pos, rc, framex/y, attr, imgKey
			{
				//	pos
				POINT tmpPos;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.x = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.y = tmpInt;
				tmpTile->setTopTilePos(tmpPos);

				// rect
				RECT tmpRc;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.left = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.top = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.right = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.bottom = tmpInt;
				tmpTile->setTopTileRc(tmpRc);

				//	tileframeX
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileFrameX(tmpInt);

				//	tileframeY
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileFrameY(tmpInt);

				//	attribute
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileAttr(tmpInt);

				//	imgKeyValue
				token = strtok_s(NULL, "/", &context);
				tmpTile->setTopTileImgKey(token);

				//	이미지 키로 받은다음 찾아서 넣어줘야함
				if (token == "none") {
					tmpTile->setTopTileImage(nullptr);
				}
				else {
					tmpTile->setTopTileImage(IMAGEMANAGER->findImage(token));
				}


			}
			//	타일정보 로드 끗

			// 오브젝트정보 로드 - pos, rc, framex/y, attr, imgKey
			{
				//	pos
				POINT tmpPos;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.x = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.y = tmpInt;
				tmpTile->setTopObjPos(tmpPos);

				// rect
				RECT tmpRc;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.left = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.top = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.right = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.bottom = tmpInt;
				tmpTile->setTopObjRc(tmpRc);

				//	tileframeX
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjFrameX(tmpInt);

				//	tileframeY
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjFrameY(tmpInt);

				//	attribute
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjAttr(tmpInt);

				//	imgKeyValue
				token = strtok_s(NULL, "/", &context);
				tmpTile->setTopObjImgKey(token);

				//	이미지 키로 받은다음 찾아서 넣어줘야함
				if (token == "none") {
					tmpTile->setTopObjImage(nullptr);
				}
				else {
					tmpTile->setTopObjImage(IMAGEMANAGER->findImage(token));
				}
			}
			//	obj 끗

			//	isAvailMove
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			if (tmpInt == 0)
				tmpTile->setIsAvailMove(false);
			else if (tmpInt == 1)
				tmpTile->setIsAvailMove(true);

			//	AreaIdx
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setAreaIdx(tmpInt);


			vLineX.push_back(tmpTile);

		}	// for j 끝
		_vvMap.push_back(vLineX);
	}
	_currentCursorTileInfo = _vvMap[0][0];

}

void mapEditor::MapResizeCountDelayFunc()
{
	if (_mapResizeCount > RESIZE_COUNTFRAME)
		return;
	_mapResizeCount++;

}

bool mapEditor::IsRdyToResize()
{
	if (_mapResizeCount >= RESIZE_COUNTFRAME)
		return true;

	return false;
}

void mapEditor::LoadView()
{
	if (PtInRect(&_roadViewRc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_roadViewOn == true)
			{
				_roadViewOn = false;
				_roadViewFrameY = 1;
			}
			else if (_roadViewOn == false)
			{
				_roadViewOn = true;
				_roadViewFrameY = 0;
			}
		}
	}
}

