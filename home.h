#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"

#include "dialogueMaker.h"
#include "npcMgr.h"
#include "skillbookUI.h"


class home : public gameNode
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
	dialogueMaker* _dialogueMaker;
	npcMgr* _nm;
	skillbookUI* _skillbookUI;


	int _tileNumX;
	int _tileNumY;

	bool _allStop;

	bool _isTalk;
	bool _isSkillbookMode;

public:
	home();
	~home();

	HRESULT init();
	void release();
	void update();
	void render();

	//ÇÔ¼öµé
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
};

