#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"
#include "minimapUI.h"
#include "boss.h"


class stage1_Boss : public gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	typedef vector<objectInfo*> vObjects;

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

	int		_savePlayerHp;
	bool	_isOneSavePlayerHp;
public:
	stage1_Boss();
	~stage1_Boss();

	HRESULT init();
	void release();
	void update();
	void render();

	//ÇÔ¼öµé
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
	void setPlayerStartHp(int playerHp){ _savePlayerHp = playerHp;}
};

