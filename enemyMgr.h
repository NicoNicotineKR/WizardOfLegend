#pragma once
#include "gameNode.h"
#include "enemy_Knight.h"
#include "enemy_Ghoul.h"

class player;

class enemyMgr : public gameNode
{
private:
	vector<enemy*>			 _vEnemy;
	vector<enemy*>::iterator _vIEnemy;

	player* _player;					//플레이어 주소 여따 넣을거임

	vector<vector<tile*>> _vvMap;

public:
	enemyMgr();
	~enemyMgr();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setPlayerAdress(player* player) { _player = player; }
	virtual void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }

	vector<enemy*> getVEnemy() { return _vEnemy; }
};

