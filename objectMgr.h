#pragma once
#include "gameNode.h"
#include "objectInfo.h"

class objectMgr : public gameNode
{
private:
	vector<objectInfo*>				_vObjMgr;
	vector<objectInfo*>::iterator	_viObjMgr; 



public:
	objectMgr();
	~objectMgr();

	HRESULT init();
	void release();
	void update();
	void render();
	void CamRender(int camLeft, int camTop);


	vector<objectInfo*>* getVObjMgrAddress() { return &_vObjMgr; }

};

