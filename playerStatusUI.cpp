#include "stdafx.h"
#include "playerStatusUI.h"


playerStatusUI::playerStatusUI()
{
}


playerStatusUI::~playerStatusUI()
{
}

HRESULT playerStatusUI::init()
{
	//	이미지매니저 추가
	IMAGEMANAGER->addImage("statusBarFrame", "images/UIs/playerStatus/playerStatusBar.bmp", 271, 66, true, 0xFF00FF);
	IMAGEMANAGER->addImage("hpBar", "images/UIs/playerStatus/playerHpBar.bmp", 201, 26, false, 0x000000);
	IMAGEMANAGER->addImage("hpBackBar", "images/UIs/playerStatus/playerHpBackBar.bmp", 201, 26, false, 0x000000);
	IMAGEMANAGER->addFrameImage("mpBar", "images/UIs/playerStatus/playerMpBar.bmp", 158, 13,1,1, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("portrait", "images/UIs/playerStatus/playerPortrait.bmp", 53, 54, 1,1, false, 0x000000);
	
	//	위치setting
	_statusBarFrame.img = IMAGEMANAGER->findImage("statusBarFrame");
	_statusBarFrame.posLT = { 54,48 };
	_statusBarFrame.rc = RectMake(54, 48, _statusBarFrame.img->GetWidth(), _statusBarFrame.img->GetHeight());
	
	_hpBar.img = IMAGEMANAGER->findImage("hpBar");
	_hpBar.posLT = { 118, 58 };
	_hpBar.rc = RectMake(61, 54, _hpBar.img->GetWidth(), _hpBar.img->GetHeight());
	_hpBarCurWid = _hpBar.img->GetWidth();

	_hpBackBar.img = IMAGEMANAGER->findImage("hpBackBar");
	_hpBackBar.posLT = _hpBar.posLT;
	_hpBackBar.rc = _hpBar.rc;
	_hpBackBarCurWid = _hpBackBar.img->GetWidth();

	_mpBar.img = IMAGEMANAGER->findImage("mpBar");
	_mpBar.posLT = { 118, 91 };
	_mpBar.rc = RectMake(118, 91, _mpBar.img->GetWidth(), _mpBar.img->GetHeight());
	_mpBarCurWid = _mpBar.img->GetWidth();
	_mpBarMaxWid = _mpBar.img->GetWidth();

	_playerPortrait.img = IMAGEMANAGER->findImage("portrait");
	_playerPortrait.img->SetFrameX(0);
	_playerPortrait.img->SetFrameY(0);
	_playerPortrait.posLT = { 61,54 };
	_playerPortrait.rc = RectMake(61, 54, _playerPortrait.img->getFrameWidth(), _playerPortrait.img->getFrameHeight());

	

	_hpBarMaxWid = _hpBar.img->GetWidth();
	_mpBarMaxWid = _mpBar.img->GetWidth();


	//	숫자이미지
	_printNum = new printNumber;
	_printNum->init();
	//	숫자이미지 출력rc이닛
	for (int i = 0; i < 7; i++) {
		//205,50 부터, 가로로, 
		hpNumPos[i] = { 205 + i* _printNum->getFrameWid(), 50 };
	}


	//	임시설정 - 테스트용
	_maxHp = 500;
	_curHp = 500;
	_maxMp = MAX_MP;
	_curMp = _maxMp;

	_isSignitureOn = true;
	_isMpAlphaRising = false;

	return S_OK;
}

void playerStatusUI::release()
{
}

void playerStatusUI::update()
{
	SetRatioFunc();
	DimHpBackBarFunc();
	SetHpBackBarFunc();

	
	
	if (_isSignitureOn) {
		MpAlphaFunc();
	}

}

void playerStatusUI::render()
{
	// statusFrame
	_statusBarFrame.img->render(getMemDC(), _statusBarFrame.posLT.x, _statusBarFrame.posLT.y);

	//초상화
	_playerPortrait.img->frameRender(getMemDC(), _playerPortrait.posLT.x, _playerPortrait.posLT.y,
		_playerPortrait.img->getFrameX(), _playerPortrait.img->getFrameY());

	//hp back bar
	_hpBackBar.img->render(getMemDC(), _hpBackBar.posLT.x, _hpBackBar.posLT.y, 0, 0,
		_hpBackBarCurWid, _hpBackBar.img->GetHeight());

	//hp bar
	_hpBar.img->render(getMemDC(), _hpBar.posLT.x, _hpBar.posLT.y, 0, 0,
		_hpBar.img->GetWidth()* _hpRatio, _hpBar.img->GetHeight());

	//mp bar
	if (!_isSignitureOn) {
		_mpBar.img->render(getMemDC(), _mpBar.posLT.x, _mpBar.posLT.y, 0, 0,
			_mpBarCurWid, _mpBar.img->GetHeight());
	}
	else {
		_mpBar.img->alphaRenderFixed(getMemDC(), _mpBar.posLT.x, _mpBar.posLT.y, 0, 0,
			_mpBarCurWid, _mpBar.img->GetHeight(), _mpAlpha);
	}

	//	숫자출력
	NumberRenderFunc();

}

void playerStatusUI::NumberRenderFunc()
{
	aryCurHp[0] = _curHp / 100;
	aryMaxHp[0] = _maxHp / 100;
	aryCurHp[1] = (int)(_curHp / 10) % 10;
	aryMaxHp[1] = (int)(_maxHp / 10) % 10;
	aryCurHp[2] = (int)_curHp % 10;
	aryMaxHp[2] = (int)_maxHp % 10;

	bool isPrintStart = false;

	isPrintStart = false;
	for (int i = 0; i < 3; i++) {
		if (aryCurHp[i] == 0 && !isPrintStart)	continue;
		_printNum->renderNum(aryCurHp[i], hpNumPos[i].x, hpNumPos[i].y);
		isPrintStart = true;
	}
	_printNum->renderNum(10, hpNumPos[3].x, hpNumPos[3].y);

	isPrintStart = false;
	for (int i = 0; i < 3; i++) {
		if (aryMaxHp[i] == 0 && !isPrintStart)	continue;
		_printNum->renderNum(aryMaxHp[i], hpNumPos[i+4].x, hpNumPos[i+4].y);
		isPrintStart = true;
	}
	


}

void playerStatusUI::SetRatioFunc()
{
	_hpRatio = (_curHp / _maxHp);
	_hpBarCurWid = _hpBarMaxWid * _hpRatio;

	_mpRatio = _curMp / _maxMp;
	_mpBarCurWid = _mpBarMaxWid * _mpRatio;
}

void playerStatusUI::DimHpBackBarFunc()
{
	if (_hpBackBarCurWid > _hpBarCurWid)
	{
		_hpBackBarCurWid -= BACK_HPBAR_DIM_SPD;

		if (_hpBackBarCurWid < _hpBarCurWid) {
			_hpBackBarCurWid = _hpBarCurWid;
		}
	}
		
}

void playerStatusUI::SetHpBackBarFunc()
{
	if (_hpBackBarCurWid < _hpBarCurWid)
		_hpBackBarCurWid = _hpBarCurWid;
}


void playerStatusUI::MpAlphaFunc()
{
	if (_isMpAlphaRising) {
		_mpAlpha += MPALPHA_BLINKSPD;
		if (_mpAlpha > 255) {
			_mpAlpha = 255;
			_isMpAlphaRising = false;
		}
	}
	else {
		_mpAlpha -= MPALPHA_BLINKSPD;
		if (_mpAlpha < 0) {
			_mpAlpha = 0;
			_isMpAlphaRising = true;
		}
	}

}
