#include "stdafx.h"
#include "objects.h"


objects::objects()
{
}


objects::~objects()
{
}

HRESULT objects::init()
{
	return S_OK;
}

void objects::release()
{
}

void objects::update()
{
}

void objects::render()
{
}

void objects::SetObj(image * img, POINT posLT, int frameX, int frameY, int attr, string keyName, POINT xySize)
{
	_img = img;
	_posLT = posLT;
	_frameX = frameX;
	_frameY = frameY;
	_attribute = attr;
	_imgKeyValue = keyName;
	_xySize = xySize;

	_rc = RectMake(posLT.x, posLT.y, TOP_TILESIZE * xySize.x, TOP_TILESIZE * xySize.y);

}
