#include "stdafx.h"
#include "skillCooldownUI.h"


skillCooldownUI::skillCooldownUI()
{
}


skillCooldownUI::~skillCooldownUI()
{
}

HRESULT skillCooldownUI::init()
{
	IMAGEMANAGER->addFrameImage("skillBorder", "images/UIs/skillUI/skillIconFrame.bmp", 120, 60, 2, 1, true, 0xFF00FF);
	IMAGEMANAGER->addImage("skillMask", "images/UIs/skillUI/skillBorderMask.bmp", 60, 60, true, 0xFF00FF);

	_iconList = new skillIconList;
	_iconList->init();

	for (int i = 0; i < 6; i++)
	{
		//_skills[i].borderImg = IMAGEMANAGER->findImage("skillBorder");
		//_skills[i].borderPos = { SKILLBORDER_STARTX + i * SKILLBORDER_GAP, SKILLBORDER_STARTY };
		//_skills[i].borderRc = RectMakeCenter(_skills[i].borderPos.x, _skills[i].borderPos.y, 60, 60);
		//
		//_skills[i].iconImg = nullptr;
		//_skills[i].iconPos = _skills[i].borderPos;
		//_skills[i].iconRc = RectMakeCenter(_skills[i].iconPos.x, _skills[i].iconPos.y, 42, 42);
		//
		//_skills[i].maskImg = IMAGEMANAGER->findImage("")
	}
	


	return S_OK;
}

void skillCooldownUI::release()
{
}

void skillCooldownUI::update()
{
	
}

void skillCooldownUI::render()
{

	//	스킬 창 테두리
	for (int i = 0; i < 6; i++)
	{
		//if(i!=3)
		//	_skills[i].borderImg->alphaFrameRender(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top, 0, 0, SKILLBORDER_ALPHA);
		//else
		//	_skills[i].borderImg->alphaFrameRender(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top, 1, 0, SKILLBORDER_ALPHA);
	}	
}


