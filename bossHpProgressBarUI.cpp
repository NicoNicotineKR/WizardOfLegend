#include "stdafx.h"
#include "bossHpProgressBarUI.h"


bossHpProgressBarUI::bossHpProgressBarUI()
{
}


bossHpProgressBarUI::~bossHpProgressBarUI()
{
}

HRESULT bossHpProgressBarUI::init(int * maxHp, int * curHp, bool* isBossStart)
{
	IMAGEMANAGER->addFrameImage("bossBarFrame", "images/UIs/bossProgressBar/bossProgressBarFrame.bmp", 452, 64, 1, 1, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("bossHpBar", "images/UIs/bossProgressBar/bossHpBar.bmp", 356, 28, 1, 1, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("bossHpBackBar", "images/UIs/bossProgressBar/bossHpBackBar.bmp", 356, 28, 1, 1, true, 0xFF00FF);
	
	_barFrameImg = IMAGEMANAGER->findImage("bossBarFrame");
	_hpBarImg = IMAGEMANAGER->findImage("bossHpBar");
	_hpBackBarImg = IMAGEMANAGER->findImage("bossHpBackBar");

	_barFramePos = { WINSIZEX / 2, 60 };
	_barFrameRc = RectMakeCenter(_barFramePos.x, _barFramePos.y, _barFrameImg->GetWidth(), _barFrameImg->GetHeight());
	_barRc = RectMakeCenter(_barFramePos.x, _barFramePos.y, _hpBarImg->GetWidth(), _hpBarImg->GetHeight());

	_ratio = 0;
	_hpBarCurWid = 0;
	_hpBackBarCurWid = 0;
	_hpBarHei = _hpBarImg->GetHeight();
	_hpBarMaxWid = _hpBarImg->GetWidth();
	_hpBackBarMaxWid = _hpBarImg->GetWidth();

	_maxHp = maxHp;
	_curHp = curHp;
	_isStart = isBossStart;

	_isInitAniEnd = false;

	return S_OK;
}

void bossHpProgressBarUI::release()
{
}

void bossHpProgressBarUI::update()
{
	if (*_isStart) {
		if (!_isInitAniEnd) {
			InitAniFunc();
		}

		//	시작 애니메이션이 끝나면,
		else {
			HpCurWidFunc();
			HpBackBarCurWidFunc();
			
		}

	}

}

void bossHpProgressBarUI::render()
{
	if (*_isStart) {
		_barFrameImg->render(getMemDC(), _barFrameRc.left, _barFrameRc.top);

		_hpBackBarImg->render(getMemDC(), _barRc.left, _barRc.top, 0, 0, _hpBackBarCurWid, _hpBarHei);
		_hpBarImg->render(getMemDC(), _barRc.left, _barRc.top, 0, 0, _hpBarCurWid, _hpBarHei);

	}
	
}

void bossHpProgressBarUI::InitAniFunc()
{
	_ratio += INIT_ANI_RATIOSPD;
	if (_ratio >= 1.0f) {
		_ratio = 1.0f;
		_isInitAniEnd = true;
	}
	_hpBarCurWid = _hpBarMaxWid * _ratio;
	_hpBackBarCurWid = _hpBackBarMaxWid * _ratio;

}

inline void bossHpProgressBarUI::HpCurWidFunc()
{
	_ratio = (float)(*_curHp) / (float)(*_maxHp);
	_hpBarCurWid = _hpBarMaxWid * _ratio;
}

inline void bossHpProgressBarUI::HpBackBarCurWidFunc()
{
	//	백바가 체력바보다 더 길면,
	if (_hpBarCurWid < _hpBackBarCurWid) {
		_hpBackBarCurWid -= BACKBAR_DIMSPD;
		if (_hpBackBarCurWid < _hpBarCurWid)
			_hpBackBarCurWid = _hpBarCurWid;
	}
	//	백바가 체력바보다 더 짧으면,
	else if (_hpBackBarCurWid < _hpBarCurWid) {
		_hpBackBarCurWid = _hpBarCurWid;
	}
}
