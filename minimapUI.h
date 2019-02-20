#pragma once
#include "gameNode.h"
#include "tile.h"
#include "printNumber.h"
#include "enemyMgr.h"
//#include "tileNode.h"

//	ĳ������ �νİŸ� : 50/28
//	�̴ϸ� ��°Ÿ� : 100/56 �¿� +1, ���� +1

//	======== ���� ==========

//	�̴����Ѵ�.(��, �÷��̾�, ���ʹ̺��� �ּ��ʿ�)
//	������Ʈ/���� �ɾ��ش�.
//	�׷��˾Ƽ��Ѵ�.


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

