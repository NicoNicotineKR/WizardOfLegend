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

	player* _player;					//�÷��̾� �ּ� ���� ��������

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

	//���� �ּ� �Ѱ���. �̰ɷ� �� ��ü���� , �� �ε������� ���ʹ� ���� �뵵
	vector<enemy*>* getVEnemyAdress() { return &_vEnemy; }
	//ghoul == 114, Knight == 115, Lancer == 116, Archer == 117
	void makeEnemy(int makeNum, POINTFLOAT enemyPos_LT);
};

