#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"

class stage1_1 : public gameNode
{
private:
	//	���� �����ϰ� �ż��� vvMap, tileNum x,y(������ int����), enemyMgr �� �غ��Ѵ�.
	//	�� Ŭ������ LoadMap�� �� ������ �ּҸ� �־��ش�. �̶� �ε��� �ʼ��ڵ� ���� �־��ָ� �� ���ִ�.
	//	�׷� �갡 �������ϸ鼭 �˾Ƽ� �����Ͱ��� �־��ٰŽô�. Load()
	//	�׷� �غ� �� ��� vvMap��, vector<Objectinfo*> �� ������Ʈ �Ŵ�����
	//	MakeObjects�� �ְ� ǫ ����ָ�,
	//	����� vvMap�� ������Ʈ �Ŵ����� ���� �� �̵�.
	//	������ ����Ҷ��� vvMap���� CamTileRender() �� ����Ͽ� �ȳ��Ѵ�.
	//	������Ʈ�� CamRender�� ���� ������ֵ��� ����.
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

	int _tileNumX;
	int _tileNumY;

	aStar* _aStar;
	float _aStarCount;

	bool _allStop;

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
};

