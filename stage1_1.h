#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"
#include "minimapUI.h"
#include "boss.h"

class stage1_1 : public gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	typedef vector<objectInfo*> vObjects;

	//타일의 포인터형을 담는 백터의 이름을 vLine만들겠다.
	//vLine담는 백터를 vvMap이라고 이름을 짓겟다.

	//vector<objectInfo*>			_vObjMgr;
	//vector<objectInfo*>::iterator	_viObjMgr;

	//objectInfo포인터형을 담는 백터를 만들겠다.
	//vector<int>
	//int자료형을 담는 백터를 만들겠다.

	stageMapLoader* _stageMapLoader;
	vvMap		_vvMap;
	vObjects	_vObjects;

	player*	_player;
	enemyMgr* _enemyMgr;
	minimapUI* _miniMap;
	boss* _boss;

	int _tileNumX;
	int _tileNumY;

	bool _allStop;

	int _savePlayerHp;
	bool _isOneSavePlayerHp;
public:
	stage1_1();
	~stage1_1();

	HRESULT init();
	void release();
	void update();
	void render();

	//함수들
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
	int getPlayerHp(){return _savePlayerHp;}
	int getIsOneSavePlayerHp(){return _isOneSavePlayerHp;}

};

