#include "stdafx.h"
#include "minimapUI.h"


minimapUI::minimapUI()
{
}


minimapUI::~minimapUI()
{
}

HRESULT minimapUI::init(vvMap* vvMapAddress, POINTFLOAT* playerPosAddress, int* curEnemyNum)
{
	IMAGEMANAGER->addImage("minimapMask", "images/UIs/minimap/minimapMask.bmp", 300, 270, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapPlayerMark", "images/UIs/minimap/minimapPlayer.bmp", 34, 35, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapTxtEnemies", "images/UIs/minimap/minimapEnemies.bmp", 55, 11, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapTxtProgress", "images/UIs/minimap/minimapProgress.bmp", 71, 11, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapTxtPercent", "images/UIs/minimap/minimapPercentage.bmp", 14, 11, true, 0xFF00FF);

	IMAGEMANAGER->addImage("minimapNone", "images/UIs/minimap/minimapNone.bmp", 3, 3, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapFloor", "images/UIs/minimap/minimapFloor.bmp", 3, 3, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapWall", "images/UIs/minimap/minimapWall.bmp", 3, 3, true, 0xFF00FF);
	IMAGEMANAGER->addImage("minimapHole", "images/UIs/minimap/minimapHole.bmp", 3, 3, true, 0xFF00FF);

	_printNum = new printNumber;
	_printNum->init();
	_vvMap = vvMapAddress;
	_playerPos = playerPosAddress;

	_tileNumX = (*_vvMap)[1].size();
	_tileNumY = (*_vvMap).size();

	//	미니맵 벡터 생성
	_vvMinimap.clear();
	_vvMinimap.reserve(sizeof(tagMinimap) * (_tileNumY) * (_tileNumX));
	for (int i = 0; i < _tileNumY; i++) {
		vMiniLine tmpVLine;
		tmpVLine.clear();
		tmpVLine.reserve(sizeof(tagMinimap) *(_tileNumX));
		for (int j = 0; j < _tileNumX; j++) {
			tagMinimap* tmpMiniTile = new tagMinimap;
			tmpVLine.push_back(tmpMiniTile);
		}
		_vvMinimap.push_back(tmpVLine);
	}


	//_minimap = new tagMinimap*[_tileNumY];
	//for (int i = 0; i < _tileNumY; i++) {
	//	 _minimap[i] = new tagMinimap[_tileNumX];
	//}

	_totalTileNum = _tileNumX * _tileNumY;

	InitMinimapTile();

	_minimapMask.img = IMAGEMANAGER->findImage("minimapMask");
	_playerMark.img = IMAGEMANAGER->findImage("minimapPlayerMark");
	_txtEnemies.img = IMAGEMANAGER->findImage("minimapTxtEnemies");
	_txtProgress.img = IMAGEMANAGER->findImage("minimapTxtProgress");
	_txtPercentage[0].img = IMAGEMANAGER->findImage("minimapTxtPercent");
	_txtPercentage[1].img = IMAGEMANAGER->findImage("minimapTxtPercent");

	_minimapMask.pos = { 29 + 160,191 + 144 };
	_playerMark.pos = _minimapMask.pos;
	_txtEnemies.pos = { 160,445 };
	_txtProgress.pos = { 160,210 };
	_txtPercentage[0].pos = { 288,210 };
	_txtPercentage[1].pos = { 288,445 };

	_minimapMask.rc = RectMakeCenter(_minimapMask.pos.x, _minimapMask.pos.y, _minimapMask.img->GetWidth(), _minimapMask.img->GetHeight());
	_playerMark.rc = RectMakeCenter(_playerMark.pos.x, _playerMark.pos.y, _playerMark.img->GetWidth(), _playerMark.img->GetHeight());
	_txtEnemies.rc = RectMakeCenter(_txtEnemies.pos.x, _txtEnemies.pos.y, _txtEnemies.img->GetWidth(), _txtEnemies.img->GetHeight());
	_txtProgress.rc = RectMakeCenter(_txtProgress.pos.x, _txtProgress.pos.y, _txtProgress.img->GetWidth(), _txtProgress.img->GetHeight());
	_txtPercentage[0].rc = RectMakeCenter(_txtPercentage[0].pos.x, _txtPercentage[0].pos.y, _txtPercentage[0].img->GetWidth(), _txtPercentage[0].img->GetHeight());
	_txtPercentage[1].rc = RectMakeCenter(_txtPercentage[1].pos.x, _txtPercentage[1].pos.y, _txtPercentage[1].img->GetWidth(), _txtPercentage[1].img->GetHeight());

	//totalTileNum 은 맵읽어들이면서, 안그린 타일을 -- 해주고있음.
	//_totalTileNum = _tileNumX * _tileNumY;
	_exploreTileNum = 0;
	_totalEnemyNum = *curEnemyNum;
	_curEnemyNum = curEnemyNum;
	_excutedEnemyNum = _totalEnemyNum - (*_curEnemyNum);



	return S_OK;
}

void minimapUI::release()
{
}

void minimapUI::update()
{
	UpdatePlayerPosIdx();
	ChkExploreFunc();
	ProgressRatioFunc();



}

void minimapUI::render()
{

	//	인터페이스 이미지들 기본 출력
	_minimapMask.img->alphaRenderFixed(getMemDC(), _minimapMask.rc.left, _minimapMask.rc.top, 0, 0, _minimapMask.img->GetWidth(), _minimapMask.img->GetHeight(), MINIMAP_MASK_ALPHA);
	_txtEnemies.img->render(getMemDC(), _txtEnemies.rc.left, _txtEnemies.rc.top);
	_txtProgress.img->render(getMemDC(), _txtProgress.rc.left, _txtProgress.rc.top);
	for (int i = 0; i < 2; i++) {
		_txtPercentage[i].img->render(getMemDC(), _txtPercentage[i].rc.left, _txtPercentage[i].rc.top);
	}

	RenderMinimap();
	RenderProgressRate();


	//	플레이어 마크는 맨 마지막 렌더할 것.
	_playerMark.img->render(getMemDC(), _playerMark.rc.left, _playerMark.rc.top);



	//	테스트용

	//RECT tmprc = RectMakeCenter(_minimapMask.pos.x, _minimapMask.pos.y, 4, 4);
	//Rectangle(getMemDC(), tmprc);
	//
	//char str[128];
	//sprintf_s(str, "ratioEnemy/Progress : [%f, %f]", _excuteEnemyRatio, _exploreRatio);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));
	//sprintf_s(str, "destStartXY : [%d, %d]", destStartX, destStartY);
	//TextOut(getMemDC(), 100, 120, str, strlen(str));
	//sprintf_s(str, "playerPos : [%d, %d]", _playerPosIdx.x, _playerPosIdx.y);
	//TextOut(getMemDC(), 100, 140, str, strlen(str));

	//for (int i = 0; i < _tileNumY; i++) {
	//	for (int j = 0; j < _tileNumX; j++) {
	//		_vvMinimap[i][j]->tileImg->render(getMemDC(), 100 + j * 3, 100 + i * 3);
	//	}
	//}

}

inline void minimapUI::UpdatePlayerPosIdx()
{
	_playerPosIdx.x = (*_playerPos).x / TOP_TILESIZE;
	_playerPosIdx.y = (*_playerPos).y / TOP_TILESIZE;
}

void minimapUI::InitMinimapTile()
{
	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {

			_vvMinimap[i][j]->isExplorerd = false;


			int tileAttr = (*_vvMap)[i][j]->getTopTileAttr();

			//enum E_TILE_ATR {TILE_NONE,	TILE_FLOOR,	TILE_WALL, TILE_HOLE,};
			switch (tileAttr) {
			case TILE_NONE:
				_vvMinimap[i][j]->tileImg = IMAGEMANAGER->findImage("minimapNone");
				_totalTileNum--;
				break;

			case TILE_FLOOR:
				_vvMinimap[i][j]->tileImg = IMAGEMANAGER->findImage("minimapFloor");

				break;

			case TILE_WALL:
				_vvMinimap[i][j]->tileImg = IMAGEMANAGER->findImage("minimapWall");

				break;

			case TILE_HOLE:
				_vvMinimap[i][j]->tileImg = IMAGEMANAGER->findImage("minimapHole");

				break;

			}





		}	//	for j end
	}	//	for i end
}

void minimapUI::ChkExploreFunc()
{
	int adjustIdxX;
	int adjustIdxY;
	//창에는 가로 50, 세로 28칸짜리 
	for (int i = -14; i < 14; i++) {
		for (int j = -25; j < 25; j++) {
			adjustIdxX = _playerPosIdx.x + j;
			adjustIdxY = _playerPosIdx.y + i;
			//	맵 밖의 인덱스 로드 예외상황 처리
			if (adjustIdxX < 0 || _tileNumX - 1 < adjustIdxX)	continue;
			if (adjustIdxY < 0 || _tileNumY - 1 < adjustIdxY)	continue;

			if (_vvMinimap[adjustIdxY][adjustIdxX]->isExplorerd == false) {
				_vvMinimap[adjustIdxY][adjustIdxX]->isExplorerd = true;
				_exploreTileNum++;
			}
		}
	}
}

inline void minimapUI::ProgressRatioFunc()
{
	_excutedEnemyNum = _totalEnemyNum - (*_curEnemyNum);
	_excuteEnemyRatio = (float)(_excutedEnemyNum) / (float)(_totalEnemyNum);

	_exploreRatio = (float)(_exploreTileNum) / (float)(_totalTileNum);
}

void minimapUI::RenderMinimap()
{
	//	출력시작 left = mask.left -3 , 
	//	출력시작 top = mask.top + 51 - 3,
	int destStartX = _minimapMask.rc.left - 3 - 16;
	int destStartY = _minimapMask.rc.top + 51 - 5;
	int adjustIdxX;
	int adjustIdxY;

	for (int i = -29; i < 29; i++) {
		for (int j = -56; j < 56; j++) {
			adjustIdxX = _playerPosIdx.x + j;
			adjustIdxY = _playerPosIdx.y + i;
			//	맵 밖의 인덱스 로드 예외상황 처리
			if (adjustIdxX < 0 || _tileNumX - 1 < adjustIdxX)	continue;
			if (adjustIdxY < 0 || _tileNumY - 1 < adjustIdxY)	continue;
			if (_vvMinimap[adjustIdxY][adjustIdxX]->isExplorerd) {
				int destX = destStartX + (j + 29) * 3;
				int destY = destStartY + (i + 56) * 3;
				//	출력시작 맨왼쪽 + j(0~57)*타일크기
				_vvMinimap[adjustIdxY][adjustIdxX]->tileImg->render(getMemDC(), destStartX + (j + 56) * 3, destStartY + (i + 29) * 3);
			}

		}
	}

	//char str[128];
	//sprintf_s(str, "_minimapMaskRcLT : [%d, %d]", _minimapMask.rc.left, _minimapMask.rc.top);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));
	//sprintf_s(str, "destStartXY : [%d, %d]", destStartX, destStartY);
	//TextOut(getMemDC(), 100, 120, str, strlen(str));
	//sprintf_s(str, "playerPos : [%d, %d]", _playerPosIdx.x, _playerPosIdx.y);
	//TextOut(getMemDC(), 100, 140, str, strlen(str));
	//


}

void minimapUI::RenderProgressRate()
{
	int num[3] = { 0,0,0 };
	//	맵타일 프로그레스
	num[0] = (int)(_exploreRatio);
	num[1] = (int)(_exploreRatio * 10) % 10;
	num[2] = (int)(_exploreRatio * 100) % 10;

	for (int i = 0; i < 3; i++) {
		if (i == 0 && num[0] == 0) continue;
		if (i == 1 && num[0] == 0 && num[1] == 0)continue;
		_printNum->renderNum(num[i], _txtProgress.rc.right + 35 + 18 * i, _txtProgress.rc.top + 5);
	}
	num[0] = (int)(_excuteEnemyRatio);
	num[1] = (int)(_excuteEnemyRatio * 10) % 10;
	num[2] = (int)(_excuteEnemyRatio * 100) % 10;

	for (int i = 0; i < 3; i++) {
		if (i == 0 && num[0] == 0) continue;
		if (i == 1 && num[0] == 0 && num[1] == 0)continue;
		_printNum->renderNum(num[i], _txtEnemies.rc.right + 35 + 18 * i, _txtEnemies.rc.top + 5);
	}
	//_printNum.


}
