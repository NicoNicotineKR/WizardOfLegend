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

	_shakeValue = 0;
	_shakeCount = 0;

	_stateCamera = 0;

	return S_OK;
}

void camera2D::release()
{
}

void camera2D::update()
{
	if (_stateCamera == PLAYER)
	{
		_camPosX = _playerPos.x;
		_camPosY = _playerPos.y;
	}

	if (_shakeCount > 0) {
		_shakeCount--;
		int shakeX = RND->getFromIntTo(-1, 2);
		int shakeY = RND->getFromIntTo(-1, 2);
		_camPosX += shakeX * _shakeValue;
		_camPosY += shakeY * _shakeValue;
	}

	if (_stateCamera == BOSS)
	{
		if (_camPosY > 200)
		{
			_camPosY -= CAMERA_SPEED;
		}
		if (_camPosY <= 200)
		{
			_camPosY = 200;
		}
	}

}

void camera2D::setPos(POINTFLOAT playerPos)
{
	if (playerPos.x > WINSIZEX / 2 && playerPos.x < _mapSizeX - WINSIZEX / 2)
	{
		_playerPos.x = playerPos.x - WINSIZEX / 2;
	}
	else if (playerPos.x <= WINSIZEX / 2)
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

void camera2D::ShakeYourBodyBabe(int shakeValue, int shakeCount)
{
	_shakeValue = shakeValue;
	_shakeCount = shakeCount;
}

