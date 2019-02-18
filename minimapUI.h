#pragma once
#include "gameNode.h"
#include "tile.h"
#include "printNumber.h"
//#include "tileNode.h"

//	캐릭터의 인식거리 : 50/28
//	미니맵 출력거리 : 100/56 좌우 +1, 상하 +1


class minimapUI : public gameNode
{
private:

	struct tagImgSet {

		image* img;
		POINT pos;
		RECT rc;
	};

	struct tagMinimap {
		//enum E_TILE_ATR {TILE_NONE,	TILE_FLOOR,	TILE_WALL, TILE_HOLE,};
		bool isExplorerd;
		image* tileImg;

	};

	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	typedef vector<tagMinimap*> vMiniLine;
	typedef vector<vMiniLine> vvMinimap;

	printNumber* _printNum;
	vvMap* _vvMap;
	POINTFLOAT* _playerPos;
	POINT _playerPosIdx;

	int _tileNumX;
	int _tileNumY;

	vvMinimap _vvMinimap;


	tagImgSet _minimapMask;
	tagImgSet _playerMark;
	tagImgSet _txtEnemies;
	tagImgSet _txtProgress;
	tagImgSet _txtPercentage[2];

	int _totalTileNum;
	int _exploreTileNum;
	int _totalEnemyNum;
	int* _curEnemyNum;
	int _excutedEnemyNum;

	float _exploreRatio;
	float _excuteEnemyRatio;





	const int MINIMAP_MASK_ALPHA = 30;


public:
	minimapUI();
	~minimapUI();

	HRESULT init(vvMap* vvMapAddress, POINTFLOAT* playerPosAddress, int* curEnemyNum);
	void release();
	void update();
	void render();

	inline void UpdatePlayerPosIdx();
	void InitMinimapTile();
	void ChkExploreFunc();
	inline void ProgressRatioFunc();


	void RenderMinimap();
	void RenderProgressRate();

};

