#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"
#include "minimapUI.h"
#include "boss.h"
#include "dialogueMaker.h"

enum stateBossStage
{
	NON,
	CAMERAMOVE,
	TALK,
	BATTLE,
};


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
	dialogueMaker* _dialogueMaker;

	int _tileNumX;
	int _tileNumY;

	bool _allStop;

	int		_savePlayerHp;
	bool	_isOneSavePlayerHp;

	//보스이미지
	image* _npcFaceImg;
	string _npcFaceText;

	stateBossStage _stateBossStage;


public:
	stage1_Boss();
	~stage1_Boss();

	HRESULT init();
	void release();
	void update();
	void render();

	//함수들
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
	void setPlayerStartHp(int playerHp) { _savePlayerHp = playerHp; }
};

