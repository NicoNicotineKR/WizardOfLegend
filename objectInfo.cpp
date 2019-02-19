#include "stdafx.h"
#include "objectInfo.h"


objectInfo::objectInfo()
{
}


objectInfo::~objectInfo()
{
}

HRESULT objectInfo::ClearNewObj()
{
	_idx = { 0,0 };
	_img = nullptr;
	_posLT = { 0,0 };
	_rc = { 0,0,0,0 };
	_startFrame = { 0,0 };
	_endFrame = { 0,0 };
	_size = { 0,0 };
	_attribute = 0;
	_imgKeyName.clear();

	return S_OK;
}

void objectInfo::render()
{
	for (int i = 0; i < _size.y; i++) {
		for (int j = 0; j < _size.x; j++) {
			_img->frameRender(getMemDC(), _rc.left + j * TOP_TILESIZE, _rc.top + i * TOP_TILESIZE);
		}
	}



}

void objectInfo::CamRender(int camLeft, int camTop)
{
	if (_img == nullptr)	return;
	for (int i = 0; i < _size.y; i++) {
		for (int j = 0; j < _size.x; j++) {
			_img->frameRender(getMemDC(), _rc.left + j * TOP_TILESIZE - camLeft, _rc.top + i * TOP_TILESIZE - camTop, _startFrame.x + j, _startFrame.y + i);
		}
	}
	//Rectangle(getMemDC(), _rc);

}
