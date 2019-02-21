#pragma once
#include "singletonBase.h"

enum stateCamera
{
	PLAYER,
	BOSS,
};


class camera2D : public singletonBase<camera2D>
{
private:
	int _mapSizeX;
	int _mapSizeY;

	int _camPosX;
	int _camPosY;

	POINTFLOAT _playerPos;

	int _shakeCount;
	int _shakeValue;

	int _stateCamera;

	const int CAMERA_SPEED = 2;
public:
	camera2D();
	~camera2D();

	HRESULT init();
	void release();
	void update();

	int getCamPosX() { return _camPosX; }
	int getCamPosY() { return _camPosY; }

	void setPos(POINTFLOAT playerPos);
	void getMapSize(int mapSizeX, int mapSizeY);
	void ShakeYourBodyBabe(int shakeValue, int shakeCount);

	void setStateCamera(int stateCamera) { _stateCamera = stateCamera; }

};

