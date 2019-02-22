#include "stdafx.h"
#include "playerInfoBoxUI.h"


playerInfoBoxUI::playerInfoBoxUI()
{
}


playerInfoBoxUI::~playerInfoBoxUI()
{
}

HRESULT playerInfoBoxUI::init()
{
	IMAGEMANAGER->addFrameImage("icon", "images/UIs/playerInfoBox/tapAndMapButton.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("icon2", "images/UIs/playerInfoBox/tapAndMapButton2.bmp", 120, 48, 2, 1, true, RGB(255, 0, 255));

	for (int i = 0; i < ICONMAX; i++)
	{
		_icon[i].img = IMAGEMANAGER->findImage("icon");
		_icon2[i].img = IMAGEMANAGER->findImage("icon2");
	}


	return S_OK;
}

void playerInfoBoxUI::release()
{
	IMAGEMANAGER->deleteImage("icon");
	IMAGEMANAGER->deleteImage("icon2");
}

void playerInfoBoxUI::update()
{
}

void playerInfoBoxUI::render()
{
	for (int i = 0; i < ICONMAX; i++)
	{
		_icon[i].img->alphaFrameRenderFixed(getMemDC(), 470 + i * 70, WINSIZEY - 85, i, 0, 50);
		_icon2[i].img->alphaFrameRenderFixed(getMemDC(), 465 + i * 70, WINSIZEY - 150, i, 0, 255);
	}
}
