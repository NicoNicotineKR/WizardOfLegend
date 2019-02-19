#pragma once
#include "gameNode.h"
#include "stageMapLoader.h"
#include "player.h"
#include "aStar.h"

class stage1_1 : public gameNode
{
private:
	//	먼저 깨끗하고 신선한 vvMap, tileNum x,y(저장할 int변수), enemyMgr 을 준비한다.
	//	이 클래스의 LoadMap에 위 재료들의 주소를 넣어준다. 이때 로드할 맵숫자도 같이 넣어주면 더 맛있다.
	//	그럼 얘가 쫠쫠쫠하면서 알아서 데이터값을 넣어줄거시다. Load()
	//	그럼 준비가 된 재료 vvMap과, vector<Objectinfo*> 인 오브젝트 매니저를
	//	MakeObjects에 넣고 푹 고아주면,
	//	마싰는 vvMap과 오브젝트 매니저를 얻을 수 이따.
	//	앞으로 출력할때는 vvMap에선 CamTileRender() 를 사용하여 냠냠한다.
	//	오브젝트는 CamRender로 따로 출력해주도록 하쟈.
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	typedef vector<objectInfo*> vObjects;

	//타일의 포인터형을 담는 백터의 이름을 vLine만들겠다.
	//vLine담는 백터를 vvMap이라고 이름을 짓겟다.

	//vector<objectInfo*>			_vObjMgr;
	//vector<objectInfo*>::iterator	_viObjMgr;

	//objectInfo포인터형을 담는 백터를 만들겠다.
	//vector<int>
	//int자료형을 담는 백터를 만들겠다.

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

	//함수들
	void TileMapRender();
	void VObjectRender();

	void setPlayerLink(player* player) { _player = player; }
};

