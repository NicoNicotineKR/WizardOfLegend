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

	int _savePlayerHp;
	bool _isOneSavePlayerHp;
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
	int getPlayerHp(){return _savePlayerHp;}
	int getIsOneSavePlayerHp(){return _isOneSavePlayerHp;}

};

