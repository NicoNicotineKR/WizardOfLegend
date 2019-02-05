#pragma once
#include "gameNode.h"
class camera2D : public gameNode
{
private:
	int _mapSizeX;
	int _mapSizeY;

	int _camPosX;
	int _camPosY;

	POINT _playerPos;


public:
	camera2D();
	~camera2D();

	HRESULT init(int mapSizeX, int mapSizeY);
	void release();
	void update();

	int getCamPosX() { return _camPosX; }
	int getCamPosY() { return _camPosY; }

	void setPos(POINT playerPos);
};

