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

	//Ÿ���� ���������� ��� ������ �̸��� vLine����ڴ�.
	//vLine��� ���͸� vvMap�̶�� �̸��� ���ٴ�.

	//vector<objectInfo*>			_vObjMgr;
	//vector<objectInfo*>::iterator	_viObjMgr;

	//objectInfo���������� ��� ���͸� ����ڴ�.
	//vector<int>
	//int�ڷ����� ��� ���͸� ����ڴ�.

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

	//�Լ���
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
//	int getPlayerHp(){return _savePlayerHp;}
	//int getIsOneSavePlayerHp(){return _isOneSavePlayerHp;}

};

