#pragma once
#include "gameNode.h"
#include "tile.h"
#include "printNumber.h"
#include "enemyMgr.h"
//#include "tileNode.h"

//	캐릭터의 인식거리 : 50/28
//	미니맵 출력거리 : 100/56 좌우 +1, 상하 +1

//	======== 사용법 ==========

//	이닛을한다.(맵, 플레이어, 에너미벡터 주소필요)
//	업데이트/렌더 걸어준다.
//	그럼알아서한다.


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
		bool isEmpty;
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
	int _curEnemyNum;
	int _excutedEnemyNum;

	float _exploreRatio;
	float _excuteEnemyRatio;

	int adjustIdxX;
	int adjustIdxY;

	vector<enemy*>* _vEnemy;
	


	const int MINIMAP_MASK_ALPHA = 30;


public:
	minimapUI();
	~minimapUI();

	HRESULT init(vvMap* vvMapAddress, POINTFLOAT* playerPosAddress, vector<enemy*>* vEnemy);
	void release();
	void update();
	void render();

	inline void UpdatePlayerPosIdx();
	void InitMinimapTile();
	void ChkExploreFunc();
	inline void ProgressRatioFunc();


	void RenderMinimap();
	void RenderProgressRate();

	void SetLinktoVEnemy(vector<enemy*>* vEnemy) { _vEnemy = vEnemy; }

};

