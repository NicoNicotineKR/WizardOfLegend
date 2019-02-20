#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"

#include "dialogueMaker.h"
#include "npcMgr.h"
#include "skillbookUI.h"

#include "playerInfoBoxUI.h"
#include "playerInfoBox.h"


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

	playerInfoBoxUI* _playerInfoBoxUI;
	playerInfoBox* _playerInfoBox;
	bool _allStop2;

	int _tileNumX;
	int _tileNumY;

	bool _allStop;

	bool _isTalk;
	bool _isSkillbookMode;

	//추가
	bool _isOnceEndSkillUi;

public:
	home();
	~home();

	HRESULT init();
	void release();
	void update();
	void render();

	//함수들
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
};

