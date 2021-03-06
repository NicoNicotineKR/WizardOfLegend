#pragma once
#include "gameNode.h"
#include "enemy_Knight.h"
#include "enemy_Ghoul.h"
#include "rotateImgMaker.h"
#include "aStar.h"

class player;

class enemyMgr : public gameNode
{
private:
	vector<enemy*>			 _vEnemy;
	vector<enemy*>::iterator _vIEnemy;

	player* _player;					//플레이어 주소 여따 넣을거임

	vector<vector<tile*>> _vvMap;

	rotateImgMaker* _rotateMaker;

	image* _ghoulEff[3][36];
	image* _knightEff[3][36];

	aStar* _aStar;
	float _aStarTime;

private:
	const float ASTAR_MAX_TIME = 0.5;
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

	//벡터 주소 넘겨줌. 이걸로 적 개체수와 , 맵 로드했을때 에너미 만들 용도
	vector<enemy*>* getVEnemyAdress() { return &_vEnemy; }
	//ghoul == 114, Knight == 115, Lancer == 116, Archer == 117
	void makeEnemy(int makeNum, POINTFLOAT enemyPos_LT);

	//재만 추가 -> 스킬쪽에서 에너미메니저 불러와서, 벡터에 있는애들 충돌했는지 검사하고, 충돌한 애 있으면, 그놈에게 데미지를 줌.
	void RcCollideBySkillFunc(RECT* skillRc, int dmg, bool* isHit);
	void DistanceBySkillFunc(POINTFLOAT skillPos, float range, int dmg, bool* isHit);

};

