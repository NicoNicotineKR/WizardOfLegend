#include "stdafx.h"
#include "printNumber.h"


printNumber::printNumber()
{
}


printNumber::~printNumber()
{
}

HRESULT printNumber::init()
{
	IMAGEMANAGER->addFrameImage("numbers", "images/UIs/number/numbers.bmp", 220, 29, 11, 1, true, 0xFF00FF);


	return S_OK;
}

void printNumber::release()
{
}

void printNumber::render()
{

}

void printNumber::renderNum(int num, int destCenX, int destCenY)
{
	switch (num)
	{
	case 0:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 0, 0);
		break;
	case 1:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 1, 0);
		break;
	case 2:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 2, 0);
		break;
	case 3:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 3, 0);
		break;
	case 4:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 4, 0);
	case 5:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 5, 0);
		break;
	case 6:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 6, 0);
		break;
	case 7:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 7, 0);
		break;
	case 8:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 8, 0);
	case 9:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 9, 0);
		break;
	case 10:
		_img->frameRender(getMemDC(), destCenX - FRAME_WID / 2, destCenY - FRAME_HEI / 2, 10, 0);
		break;
		break;
		break;

	}
}
