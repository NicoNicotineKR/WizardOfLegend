#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tile : public gameNode
{
private:
	POINT _topIdx;
	image* _topImg;
	POINT _topPos;
	RECT _topRc;

	
	




public:
	tile();
	~tile();
};

