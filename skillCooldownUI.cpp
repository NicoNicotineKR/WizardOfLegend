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
	_printNum = new printNumber;
	_printNum->init();

	for (int i = 0; i < 6; i++)
	{
		_skills[i].name.clear();
		_skills[i].pos = { ICONSTART_X + i * ICONGAB, ICONSTART_Y };

		_skills[i].borderImg = IMAGEMANAGER->findImage("skillBorder");
		_skills[i].borderRc = RectMakeCenter(_skills[i].pos.x, _skills[i].pos.y, 60, 60);
		
		_skills[i].iconImg = nullptr;
		_skills[i].iconRc = RectMakeCenter(_skills[i].pos.x, _skills[i].pos.y, 42, 42);
		
		_skills[i].maskImg = IMAGEMANAGER->findImage("skillMask");

		_skills[i].totalReloadNum = 0;
		_skills[i].curReloadNum = 0;
		_skills[i].coolDownTime = 0;
		_skills[i].curTime = 0;
		_skills[i].lastingTime = 0;
		_skills[i].curMaskWid = MASK_MAX_WID;
		
	}
	


	return S_OK;
}

void skillCooldownUI::release()
{
}

void skillCooldownUI::update()
{
	for (int i = 0; i < 6; i++) {
		if (_skills[i].iconImg != nullptr && _skills[i].curReloadNum <= 0) {
 			_skills[i].lastingTime = CalLastingTime(i);
			_skills[i].curMaskWid = CalMaskWid(i);
		}
	}
}

void skillCooldownUI::render()
{

	
	for (int i = 0; i < 6; i++) {

		//	스킬 창 테두리
		if (i != 3)
			_skills[i].borderImg->alphaFrameRender(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top, 0, 0, BORDER_ALPHA);
		else
			_skills[i].borderImg->alphaFrameRender(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top, 1, 0, BORDER_ALPHA);


		//	스킬 이미지 출력
		if (_skills[i].iconImg != nullptr) {
			_skills[i].iconImg->frameRender(getMemDC(), _skills[i].iconRc.left, _skills[i].iconRc.top,
				_skills[i].iconImg->getFrameX(), _skills[i].iconImg->getFrameY());
		}


		//	마스크 출력 & 쿨다운 남은시간 숫자 출력
		if (_skills[i].curReloadNum <= 0) {
			//	마스크
			_skills[i].maskImg->alphaRenderFixed(getMemDC(), _skills[i].borderRc.right - _skills[i].curMaskWid, _skills[i].borderRc.top,
				0, 0, _skills[i].curMaskWid, 60, MASK_ALPHA);

			if (_skills[i].iconImg != nullptr) {
				//	숫자
				_printNum->renderNum((int)_skills[i].lastingTime % 10, _skills[i].borderRc.left + 15, _skills[i].borderRc.top + BORDER_SIZE / 2);
				_printNum->renderNum(11, _skills[i].borderRc.left + BORDER_SIZE / 2, _skills[i].borderRc.top + BORDER_SIZE / 2);
				_printNum->renderNum((int)(_skills[i].lastingTime * 10) % 10, _skills[i].borderRc.right - 15, _skills[i].borderRc.top + BORDER_SIZE / 2);
			}

			
		}

		//	남은 스킬수 출력
		if (_skills[i].totalReloadNum > 1 && _skills[i].curReloadNum >= 1) {
			_printNum->renderNum(_skills[i].curReloadNum, _skills[i].pos.x, _skills[i].pos.y);
		}
	}

}

void skillCooldownUI::ChangeSkill(int idx, string name, int totalReloadedNum, float coolDownTime)
{
	_skills[idx].name = name;
	_skills[idx].iconImg = _iconList->getIconsImg();

	POINT iconFrame = _iconList->FindSkillIdx(name);

	_skills[idx].iconImg->SetFrameX(iconFrame.x);
	_skills[idx].iconImg->SetFrameY(iconFrame.y);

	_skills[idx].totalReloadNum = totalReloadedNum;
	_skills[idx].curReloadNum = 0;
	_skills[idx].coolDownTime = coolDownTime;
	_skills[idx].curTime = 0.f;
	_skills[idx].lastingTime = CalLastingTime(idx);
}

void skillCooldownUI::DropSkill(int idx)
{
	_skills[idx].iconImg = nullptr;
	_skills[idx].totalReloadNum = 0;
	_skills[idx].curReloadNum = 0;
	_skills[idx].coolDownTime = 0;
	_skills[idx].curTime = 0;
	_skills[idx].lastingTime = 0;
	_skills[idx].curMaskWid = MASK_MAX_WID;


}

float skillCooldownUI::CalLastingTime(int idx)
{
	if (_skills[idx].curTime > _skills[idx].coolDownTime) {
		_skills[idx].curTime = _skills[idx].coolDownTime;
	}

	return _skills[idx].coolDownTime - _skills[idx].curTime;
}

float skillCooldownUI::CalMaskWid(int idx)
{
	float ratio;
	ratio = _skills[idx].lastingTime / _skills[idx].coolDownTime;

	return MASK_MAX_WID * ratio;
}


