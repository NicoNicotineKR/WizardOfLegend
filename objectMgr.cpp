#include "stdafx.h"
#include "objectMgr.h"


objectMgr::objectMgr()
{
}


objectMgr::~objectMgr()
{
}

HRESULT objectMgr::init()
{
	_vObjMgr.clear();


	return S_OK;
}

void objectMgr::release()
{
}

void objectMgr::update()
{
}

void objectMgr::render()
{
	for (int i = 0; i < _vObjMgr.size(); i++) {
		_vObjMgr[i]->render();
	}
}

void objectMgr::CamRender(int camLeft, int camTop)
{
	for (int i = 0; i < _vObjMgr.size(); i++) {
		_vObjMgr[i]->CamRender(camLeft, camTop);
	}
}
