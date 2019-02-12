#include "stdafx.h"
#include "skillIconList.h"


skillIconList::skillIconList()
{
}


skillIconList::~skillIconList()
{
}

HRESULT skillIconList::init()
{
	IMAGEMANAGER->addFrameImage("skillIcons", "images/UIs/skillIcons/skillIcons.bmp", 1008, 1008, 24, 24, true, 0xFF00FF);
	_frameWid = _skillsImg->getFrameWidth();
	_frameHei = _skillsImg->getFrameHeight();

	return S_OK;
}

void skillIconList::release()
{
}

void skillIconList::update()
{
}


void skillIconList::frameRender(int centerX, int centerY, int idxX, int idxY)
{
	_skillsImg->frameRender(getMemDC(), centerX - _frameWid / 2, centerY - _frameHei / 2, idxX, idxY);
}

void skillIconList::alphaFrameRender(int centerX, int centerY, int idxX, int idxY, int alpha)
{
	_skillsImg->alphaFrameRenderFixed(getMemDC(), 
		centerX - _frameWid / 2, 
		centerY - _frameHei / 2,
		idxX, idxY, 
		alpha);
}

void skillIconList::InitSkillList()
{
	AddSkillList("FlameStrike", 0, 0);
	AddSkillList("stoneShot", 0, 2);
	AddSkillList("searingRush", 0, 6);
	AddSkillList("shatteringStrike", 0, 20);
	AddSkillList("shockNova", 0, 21);
	AddSkillList("frostFan, ", 0, 22);
	AddSkillList("reboundingIcicles, ", 1, 22);


}

void skillIconList::AddSkillList(string keyName, int idxX, int idxY)
{
	POINT tmpPoint;
	tmpPoint.x = idxX;
	tmpPoint.y = idxY;

	_mSkillIdxList.insert(make_pair(keyName, tmpPoint));
}

POINT skillIconList::FindSkillIdx(string keyName)
{
	POINT tmpIdx = { 0,0 };

	_miSkillIdxList = _mSkillIdxList.find(keyName);
	tmpIdx = _miSkillIdxList->second;

	return tmpIdx;
}