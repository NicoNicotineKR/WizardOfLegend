#pragma once
#include "gameNode.h"
class printNumber : public gameNode
{
	image* _img;

	const int FRAME_WID = 22;
	const int FRAME_HEI = 29;
public:
	printNumber();
	~printNumber();

	HRESULT init();
	void release();
	void render();
	void renderNum(int num, int destCenX, int destCenY);

};

