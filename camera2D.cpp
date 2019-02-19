#include "stdafx.h"
#include "camera2D.h"


camera2D::camera2D()
{
}


camera2D::~camera2D()
{
}

HRESULT camera2D::init()
{
	_camPosX = 0;
	_camPosY = 0;

	_playerPos.x = 0;
	_playerPos.y = 0;

	return S_OK;
}

void camera2D::release()
{
}

void camera2D::update()
{

	_camPosX = _playerPos.x;
	_camPosY = _playerPos.y;

}

void camera2D::setPos(POINTFLOAT playerPos)
{
	if (playerPos.x > WINSIZEX / 2 && playerPos.x < _mapSizeX - WINSIZEX / 2)
	{
		_playerPos.x = playerPos.x - WINSIZEX / 2;
	}
	else if(playerPos.x <= WINSIZEX / 2)
	{
		_playerPos.x = 0;
	}



	if (playerPos.y > WINSIZEY / 2 && playerPos.y < _mapSizeY - WINSIZEY / 2)
	{
		_playerPos.y = playerPos.y - WINSIZEY / 2;
	}
	else if (playerPos.y <= WINSIZEY / 2)
	{
		_playerPos.y = 0;
	}
}

void camera2D::getMapSize(int mapSizeX, int mapSizeY)
{
	_mapSizeX = mapSizeX;
	_mapSizeY = mapSizeY;
}

