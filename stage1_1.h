#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"
#include "minimapUI.h"
#include "boss.h"
#include "npc_warp.h"
#include "dialogueMaker.h"

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

	npc_warp* _npc_warp;
	dialogueMaker* _dialogueMaker;
	image* _npcFaceImg;
	string _npcFaceText1;
	string _npcFaceText2;
	bool _IsTalk;

//	int _savePlayerHp;
//	bool _isOneSavePlayerHp;
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
//	int getPlayerHp(){return _savePlayerHp;}
	//int getIsOneSavePlayerHp(){return _isOneSavePlayerHp;}

};

