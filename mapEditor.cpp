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
	IMAGEMANAGER->addFrameImage("objCastle", "images/map/CastleBaseObjSet.bmp", 896, 384, 28, 12, true, 0xFF00FF);
	IMAGEMANAGER->addImage("mapEditorFrame", "images/mapEditor/mapEditorFrame.bmp", 1600, 900, true, 0xFF00FF);
	IMAGEMANAGER->addImage("sampleMask", "images/mapEditor/sampleMask.bmp", 32, 32, false, 0x000000);

	//	버튼 이미지 imagemanager 넣고
	{
		IMAGEMANAGER->addFrameImage("btn_areamode", "images/mapEditor/btn_areamode.bmp", 141, 44, 1, 2, false, 0x000000);
		IMAGEMANAGER->addFrameImage("btn_autofill", "images/mapEditor/btn_autofill.bmp", 105, 44, 1, 2, false, 0x000000);
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
	}

	//	기본 크기
	_tileNumX = 10;
	_tileNumY = 10;
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

	//	tileCastle 샘플 생성
	InitSampleCastleTile();
	

	_curTileSampleIdx = CASTLETILE1;


	_isAreaMode = false;
	_isAutoFill = false;
	_isErase = false;

	_cursorSampleIdx[0] = { 0,0 };
	_cursorSampleIdx[1] = { 0,0 };
	_currentCursorTileInfo = new tile;

	_isClickDown = false;
	_isCursorSelected = false;

	_camLeftTop = { 0,0 };

	return S_OK;
}

void mapEditor::release()
{
}

void mapEditor::update()
{
	OverlayClickFunc();
	CursorSampleSelectFunc();
	ArrowClickFunc();
	CursorClickOnMap();

	CursorGetTileInfoFunc();

	CamMove();
}

void mapEditor::render()
{

	//타일 출력
	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {
			//_vvMap[i][j]->render();
			_vvMap[i][j]->CamRender(_camLeftTop.x, _camLeftTop.y);
		}
	}

	//프레임 출력
	_frame->render(getMemDC(), 0, 0);

	//버튼들 출력
	for (int i = 0; i < E_BUTTONS_END; i++)
	{
		_buttons[i].img->frameRender(getMemDC(), _buttons[i].rc.left, _buttons[i].rc.top, _buttons[i].frameX, _buttons[i].frameY);
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
			Rectangle(getMemDC(), _sampleRc[i][j]);
		}
	}

	//샘플이미지 렌더
	SampleRender();
	SampleSelectedRectRender();


	//	텍스트 숫자들 출력
	TextNumberRender();

	//	타일 Info 출력
	TileInfoRender();


	//	테스트용
	char str[128];
	sprintf_s(str, "_curTileSampleIdx : %d", _curTileSampleIdx);
	TextOut(getMemDC(), 30, 30, str, strlen(str));

	
	
	
	
	

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

void mapEditor::InitButtons()
{
	for (int i = 0; i < E_BUTTONS_END; i++) {
		switch (i) {
		case AREAMODE:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_areamode");
			_buttons[i].pos = { 174,814 };
			break;
		case AUTOFILL:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_autofill");
			_buttons[i].pos = { 1087,36 };
			break;
		case SELECT:
			_buttons[i].img = IMAGEMANAGER->findImage("btn_select");
			_buttons[i].pos = { 1087,92 };
			break;
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
		for (int i = 0; i <= IMAGEMANAGER->findImage("tileCastle")->getMaxFrameY(); i++)	//	12
		{
			for (int j = 0; j <= IMAGEMANAGER->findImage("tileCastle")->getMaxFrameX(); j++)	//	22
			{
				_castleTileSample[i][j] = new tile;
				SetNewSampleTile(_castleTileSample[i][j], j, i);
				_castleTileSample[i][j]->setTopTileImage(IMAGEMANAGER->findImage("tileCastle"));

				//	개별적 셋팅
				//	1번
				if (i <= 11 && j <= 11)
				{
					//	1번 윗벽
					if (0 <= i && i <= 3) {
						_castleTileSample[i][j]->setIsAvailMove(false);
						_castleTileSample[i][j]->setTopTileAttr(TILE_WALL);
					}

					//	1번 왼쪽벽
					if (j == 0) {
						_castleTileSample[i][j]->setIsAvailMove(false);
						_castleTileSample[i][j]->setTopTileAttr(TILE_WALL);
					}
					//	1번 아래벽
					if (i == 11) {
						if (0 <= j && j <= 11) {
							_castleTileSample[i][j]->setIsAvailMove(false);
							_castleTileSample[i][j]->setTopTileAttr(TILE_WALL);
						}
					}
					//	1번 우측벽
					if (j == 11) {
						if (0 <= i && i <= 11) {
							_castleTileSample[i][j]->setIsAvailMove(false);
							_castleTileSample[i][j]->setTopTileAttr(TILE_WALL);
						}
					}
					//	1번 바닥
					if (4 <= i && i <= 10) {
						if (1 <= j && j <= 10) {
							_castleTileSample[i][j]->setIsAvailMove(true);
							_castleTileSample[i][j]->setTopTileAttr(TILE_FLOOR);
						}
					}
				}	//	1번 타일 끝

				//	2번 
				if (i <= 6 && 12 <= j && j <= 17) {
					if (i <= 3) {
						_castleTileSample[i][j]->setIsAvailMove(true);
						_castleTileSample[i][j]->setTopTileAttr(TILE_FLOOR);
					}
					if (4 <= i && i <= 6) {
						_castleTileSample[i][j]->setIsAvailMove(true);
						_castleTileSample[i][j]->setTopTileAttr(TILE_HOLE);
					}
				}

				//	3번
				if (18 <= j && j <= 21 && i <= 6) {
					_castleTileSample[i][j]->setIsAvailMove(true);
					_castleTileSample[i][j]->setTopTileAttr(TILE_FLOOR);
				}

				//	4번
				if (12 <= j && j <= 15 && 7 <= i && i <= 11) {
					_castleTileSample[i][j]->setIsAvailMove(true);
					_castleTileSample[i][j]->setTopTileAttr(TILE_FLOOR);
				}


			}
		}

		//캐슬 타일 프레임 갯수 이닛
		{
			_castleTileFrameIdx[0][CASTLETILE1] = { 0,0 };
			_castleTileFrameIdx[1][CASTLETILE1] = { 11,11 };
			_castleTileFrameIdx[0][CASTLETILE2] = { 12,0 };
			_castleTileFrameIdx[1][CASTLETILE2] = { 17,6 };
			_castleTileFrameIdx[0][CASTLETILE3] = { 18,0 };
			_castleTileFrameIdx[1][CASTLETILE3] = { 23,6 };
			_castleTileFrameIdx[0][CASTLETILE4] = { 12,7 };
			_castleTileFrameIdx[1][CASTLETILE4] = { 15,11 };
		}

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
		else if (i == AREAMODE || i == AUTOFILL || i == ERASE)
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
					case AUTOFILL:
						_isAutoFill = !_isAutoFill;
						if (_isAutoFill) _buttons[i].frameY = 1;
						else             _buttons[i].frameY = 0;

						break;
					case ERASE:
						_isErase = !_isErase;
						if (_isErase) _buttons[i].frameY = 1;
						else          _buttons[i].frameY = 0;

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

						case ARROW_MAPSIZEX:
							_tileNumX--;
							if (_tileNumX < 1) {
								_tileNumX = 1;
								break;
							}
								
							EraseMapX();
							break;

						case ARROW_MAPSIZEY:
							_tileNumY--;
							if (_tileNumY < 1) {
								_tileNumY = 1;
								break;
							}
							EraseMapY();
							break;

						case ARROW_TILES:
							_curTileSampleIdx--;
							//캐슬타일중일경우,
							if (_curTileKind == CASTLE_TILE) {
								if (_curTileKind < 0) {
								
									_curTileSampleIdx = CASTLETILE_KINDS_END - 1;
								}
								//	다른 종류 타일 추가시 여기에 추가
								//else if () {
								//
								//}
								
							}
								
							
							break;

						case ARROW_OBJECTS:
							_curObjKind--;
							if (_curObjKind < 0)
								_curObjKind = OBJ_KINDS_END - 1;
							break;
							
						case ARROW_UNITS:
							_curUnitKind--;
							if (_curUnitKind < 0)
								_curUnitKind = UNIT_KINDS_END - 1;
							break;
						}
					}
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

						case ARROW_MAPSIZEX:
							_tileNumX++;
							AddMapX();
							break;

						case ARROW_MAPSIZEY:
							_tileNumY++;
							AddMapY();
							break;

						case ARROW_TILES:
							_curTileSampleIdx++;
							//	캐슬타일중일경우,
							if (_curTileKind == CASTLE_TILE) {
							
								if (_curTileSampleIdx >= CASTLETILE_KINDS_END) {
								
									_curTileSampleIdx = 0;
								}
								//	다른 종류 타일 추가시 여기에 추가
								//else if () {
								//
								//}

							}

							break;

						case ARROW_OBJECTS:
							_curObjKind++;
							if (_curObjKind == OBJ_KINDS_END)
								_curObjKind = 0;
							break;

						case ARROW_UNITS:
							_curUnitKind++;
							if (_curUnitKind == UNIT_KINDS_END)
								_curUnitKind = 0;
							break;
						}
					}
				}
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
	if (PtInRect(&_mapZoneRc, _ptMouse)) {
		for (int i = 0; i < _tileNumY; i++) {
			for (int j = 0; j < _tileNumX; j++) {
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
		//타일인 경우,
	case SELECT_TILE:
		//캐슬타일이면,
		if (_curTileKind == CASTLE_TILE)
		{
			int xStartIdx = _castleTileFrameIdx[0][_curTileSampleIdx].x;
			int yStartIdx = _castleTileFrameIdx[0][_curTileSampleIdx].y;
			int xEndIdx = _castleTileFrameIdx[1][_curTileSampleIdx].x;
			int yEndIdx = _castleTileFrameIdx[1][_curTileSampleIdx].y;

			for (int i = yStartIdx; i <= yEndIdx; i++) {
				for (int j = xStartIdx; j <= xEndIdx; j++) {
					//_castleTileSampleImg->frameRender(getMemDC(), _sampleRc[0][0].left + (j-xStartIdx) * TOP_TILESIZE, _sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE, j, i);	//일단 죽여봄
					_castleTileSample[i][j]->getTopTileImg()->frameRender(getMemDC(), 
						_sampleRc[0][0].left + (j - xStartIdx) * TOP_TILESIZE,
						_sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE,
						j, i);

					//	위와 같은 내용
					//_castleTileSample[i][j]->getTileImg()->frameRender(getMemDC(),
					//	_sampleRc[0][0].left + (j - xStartIdx) * TOP_TILESIZE,
					//	_sampleRc[0][0].top + (i - yStartIdx) * TOP_TILESIZE,
					//	_castleTileFrameIdx[0][_curTileSampleIdx].x
					//	_castleTileFrameIdx[0][_curTileSampleIdx].y,
					//	);


				}
			}

			//for (int i = _castleTileFrameIdx[0][_curTileSampleIdx].y; i <= _castleTileFrameIdx[1][_curTileSampleIdx].y; i++) {
			//	for (int j = _castleTileFrameIdx[0][_curTileSampleIdx].x; j <= _castleTileFrameIdx[1][_curTileSampleIdx].y; j++) {
			//		_castleTileSampleImg->frameRender(getMemDC(), _sampleRc[0][0].left + j * TOP_TILESIZE, _sampleRc[0][0].top + i * TOP_TILESIZE,
			//			_castleTileFrameIdx[0][_curTileSampleIdx].x + j, _castleTileFrameIdx[0][_curTileSampleIdx].y + i);
			//	}
			//}
		}
		
		

		break;
	}
}

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
	
	if (_currentCursorTileInfo->getTopTileImg() != nullptr) {

		string toptileImgName = _currentCursorTileInfo->getTopTileImgKey();
		//	이미지 이름
		TextOut(getMemDC(), 1024, 300, toptileImgName.c_str(), strlen(toptileImgName.c_str()));

		//	맵 인덱스
		sprintf_s(tmpStr, "MapIdxX : %d", _currentCursorTileInfo->getTopIdx().x);
		TextOut(getMemDC(), 1024, 320, tmpStr, strlen(tmpStr));
		sprintf_s(tmpStr, "MapIdxY : %d", _currentCursorTileInfo->getTopIdx().y);
		TextOut(getMemDC(), 1024, 340, tmpStr, strlen(tmpStr));

		//	타일 속성
		sprintf_s(tmpStr, "Tile Atr : ");
		TextOut(getMemDC(), 1024, 380, tmpStr, strlen(tmpStr));
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
		TextOut(getMemDC(), 1024, 400, tmpStr, strlen(tmpStr));

		//	타일프레임
		sprintf_s(tmpStr, "Tile frameX : %d", _currentCursorTileInfo->getTopTileFrameX());
		TextOut(getMemDC(), 1024, 420, tmpStr, strlen(tmpStr));
		sprintf_s(tmpStr, "Tile frameY : %d", _currentCursorTileInfo->getTopTileFrameY());
		TextOut(getMemDC(), 1024, 440, tmpStr, strlen(tmpStr));
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
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					{
						_cursorMapIdx.x = j;
						_cursorMapIdx.y = i;
						if (!_isErase)
						{
							CursorAdjustOnMap();
						}
						else if (_isErase)
						{
							CursorEraseMap(_vvMap[i][j]);
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
			if (_curSampleKind == SELECT_TILE) {
				if (_curTileKind == TILETYPE_CASTLE) {
					//	드래그 + 실제맵스프라이트의 인덱스(프레임) 적용
					int adjustIdxY = i + _castleTileFrameIdx[0][_curTileSampleIdx].y;
					int adjustIdxX = j + _castleTileFrameIdx[0][_curTileSampleIdx].x;
					//	이미지랑 프레임, 필요한 정보만 넣어줘야함, 렉트까지 넣어주지말고
					//_vvMap[mapIdxY + (i-iStart)][mapIdxX + (j-jStart)] = _castleTileSample[adjustIdxY][adjustIdxX];
					TransTileSampleToMap(_castleTileSample[adjustIdxY][adjustIdxX], _vvMap[mapIdxY + (i - iStart)][mapIdxX + (j - jStart)]);
					_vvMap[mapIdxY + (i - iStart)][mapIdxX + (j - jStart)]->setTopTileImgKey("tileCastle");	//	트랜스 타일에서 안되서...ㅠ_ㅠ 별도로 써줌
					
					
				}
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

	mapTile->setIsAvailMove(false);

	mapTile->setAreaIdx(0);
}

void mapEditor::TransTileSampleToMap(tile * sampleTile, tile * mapTile)
{
	
	mapTile->setTopTileImage(sampleTile->getTopTileImg());
	mapTile->setTopTileFrameX(sampleTile->getTopTileFrameX());
	mapTile->setTopTileFrameY(sampleTile->getTopTileFrameY());
	mapTile->setTopTileAttr(sampleTile->getTopTileAttr());

	
	mapTile->setIsAvailMove(sampleTile->getIsAvailMove());

	mapTile->setAreaIdx(_curAreaIdx);
	
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
	char save[500000] = {};
	char token[10000] = {};
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





				//	밑에 오브젝트들도 해야함...

				/*
				



				//	오브젝타입
				itoa(_vvTable[i][j]->getObjAttr(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);		//	정수하나임.10자리까지
				strcat_s(token, sizeof(token), "/");	//	구분자추가



				
				//	objframeX
				itoa(_vvTable[i][j]->getObjFrameX(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");
				//	objframeY
				itoa(_vvTable[i][j]->getObjFrameY(), tmp, 10);
				strcat_s(token, sizeof(token), tmp);
				strcat_s(token, sizeof(token), "/");
				*/

				strcat_s(save, sizeof(save), token);
			}
			


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
	char load[500000] = {};
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
				

			}	//	타일정보 로드 끗

			/*

			// idxX
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setIdxX(tmpInt);
			// idxY
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setIdxY(tmpInt);


			// tileType
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setTileAttr(tmpInt);

			// objType
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setObjAttr(tmpInt);



			//	objFrameX
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setObjFrameX(tmpInt);
			//	objFrameY
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setObjFrameY(tmpInt);

			tmpTile->setTileImg(tileImg);
			tmpTile->setObjImg(objImg);
			*/


			vLineX.push_back(tmpTile);

		}	// for j 끝
		_vvMap.push_back(vLineX);

	}

}

