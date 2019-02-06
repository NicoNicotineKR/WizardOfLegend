#include "stdafx.h"
#include "tile.h"


tile::tile()
{
}


tile::~tile()
{
}

HRESULT tile::init()
{
	return S_OK;
}

void tile::release()
{
}

void tile::update()
{
}

void tile::render()
{
	Rectangle(getMemDC(), _topTile.rc);
	if (_topTile.img != nullptr)
	{
		_topTile.img->frameRender(getMemDC(), _topTile.rc.left, _topTile.rc.top, _topTile.frameX, _topTile.frameY);
	}
	if (_topObj.img != nullptr)
	{
		_topObj.img->frameRender(getMemDC(), _topObj.rc.left, _topObj.rc.top, _topObj.frameX, _topObj.frameY);
	}



}
