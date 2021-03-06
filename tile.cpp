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
	//Rectangle(getMemDC(), _topTile.rc);
	if (_topTile.img != nullptr)
	{
		_topTile.img->frameRender(getMemDC(), _topTile.rc.left, _topTile.rc.top, _topTile.frameX, _topTile.frameY);
	}
	if (_topObj.img != nullptr)
	{
		_topObj.img->frameRender(getMemDC(), _topObj.rc.left, _topObj.rc.top, _topObj.frameX, _topObj.frameY);
	}



}

void tile::CamRender(int camLeft, int camTop)
{
//	Rectangle(getMemDC(), _topTile.rc);
	Rectangle(getMemDC(), _topTile.rc.left - camLeft, _topTile.rc.top - camTop,		//	맵에디터만 키고 사용할 것!
		_topTile.rc.right - camLeft, _topTile.rc.bottom - camTop);
	if (_topTile.img != nullptr)
	{
		_topTile.img->frameRender(getMemDC(), _topTile.rc.left - camLeft, _topTile.rc.top - camTop, _topTile.frameX, _topTile.frameY);
	}
	if (_topObj.img != nullptr)
	{
		_topObj.img->frameRender(getMemDC(), _topObj.rc.left - camLeft, _topObj.rc.top - camTop, _topObj.frameX, _topObj.frameY);
	}
}

void tile::CamTileRender(int camLeft, int camTop)
{
	if (_topTile.img != nullptr)
	{
		_topTile.img->frameRender(getMemDC(), _topTile.rc.left - camLeft, _topTile.rc.top - camTop, _topTile.frameX, _topTile.frameY);
	}
}

void tile::AlphaFrameRender(int destX, int destY,  BYTE alpha)
{

	//void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
	if (_topTile.img != nullptr)
	{
		
		_topTile.img->alphaFrameRenderFixed(getMemDC(), destX, destY, _topTile.frameX, _topTile.frameY, alpha);
		
		
	}
	if (_topObj.img != nullptr)
	{
		_topObj.img->alphaFrameRenderFixed(getMemDC(), destX, destY, _topObj.frameX, _topObj.frameY, alpha);
	}
}

