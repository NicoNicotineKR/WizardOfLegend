#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"
#include "minimapUI.h"
#include "boss.h"
#include "dialogueMaker.h"
#include "bossHpProgressBarUI.h"

enum stateBossStage
{
	NON,
	CAMERAMOVE,
	TALK,
	BATTLE,
	BOSSDEAD,
	ENDBOSS,
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
	bossHpProgressBarUI* _bossHpBar;

	int _tileNumX;
	int _tileNumY;

	bool _allStop;

	image* _blackMaskImg;
	int _maskAlpha;
	int _alphaStartCount;
	//int		_savePlayerHp;
	//bool	_isOneSavePlayerHp;

	//보스이미지
	image* _npcFaceImg;
	string _npcFaceText;
	string _npcFaceText2;

	stateBossStage _stateBossStage;

	

	const int ALPHA_AUG = 1;
	const int ALPHA_STARTCOUNT_MAX = 200;


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
	//void setPlayerStartHp(int playerHp) { _savePlayerHp = playerHp; }
};

