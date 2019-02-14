#pragma once
#include "gameNode.h"
#include "enemy_Knight.h"

class player;

class enemyMgr : public gameNode
{
private:
	vector<enemy*>			 _vEnemy;
	vector<enemy*>::iterator _vIEnemy;

	player* _player;					//�÷��̾� �ּ� ���� ��������

public:
	enemyMgr();
	~enemyMgr();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setPlayerAdress(player* player) { _player = player; }

	vector<enemy*> getVEnemy() { return _vEnemy; }
};

