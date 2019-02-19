#pragma once
#include "gameNode.h"
#include "tile.h"
#include "objectInfo.h"
#include "enemyMgr.h"

//	====	stageMapLoader가 누구입니꽈~~~!!!!! -> 맵 로드하고 오브젝트/에너미 매니저에 적용시켜주는 애  ====
//	사용방법

//	먼저 깨끗하고 신선한 vvMap, tileNum x,y(저장할 int변수), enemyMgr 을 준비한다.
//	이 클래스의 LoadMap에 위 재료들의 주소를 넣어준다. 이때 로드할 맵숫자도 같이 넣어주면 더 맛있다.
//	그럼 얘가 쫠쫠쫠하면서 알아서 데이터값을 넣어줄거시다.
//	그럼 준비가 된 재료 vvMap과, vector<Objectinfo*> 인 오브젝트 매니저를
//	MakeObjects에 넣고 푹 고아주면,
//	마싰는 vvMap과 오브젝트 매니저를 얻을 수 이따.
//	앞으로 출력할때는 vvMap에선 CamTileRender() 를 사용하여 냠냠한다.
//	오브젝트는 CamRender로 따로 출력해주도록 하쟈.


class stageMapLoader : public gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	typedef vector<objectInfo*> vObjects;


	int _tileNumX;
	int _tileNumY;
	enemyMgr* _enemyMgr;

public:
	stageMapLoader();
	~stageMapLoader();

	//	로드맵 사용후, MakeObjects사용하시오!!!
	void LoadMap(vvMap * vvMapAddress, int * tileNumX, int * tileNumY, int stageNum);
	void MakeObjects(vvMap * vvMapAddress, vObjects * vectorObjAddress, enemyMgr* enemyMgr);


	void setLinktoEnemyMgr(enemyMgr* enemyMgrAddr) { _enemyMgr = enemyMgrAddr; }
};


