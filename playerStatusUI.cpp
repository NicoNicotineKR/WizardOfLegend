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
	IMAGEMANAGER->addImage("mpBar", "images/UIs/playerStatus/playerMpBar.bmp", 158, 13, false, 0x000000);
	IMAGEMANAGER->addFrameImage("portrait", "images/UIs/playerStatus/playerPortrait.bmp", 53, 54, 1,1, false, 0x000000);
	
	//	위치setting
	_statusBarFrame.img = IMAGEMANAGER->findImage("statusBarFrame");
	_statusBarFrame.posLT = { 54,48 };
	_statusBarFrame.rc = RectMake(54, 48, _statusBarFrame.img->GetWidth(), _statusBarFrame.img->GetHeight());
	
	_hpBar.img = IMAGEMANAGER->findImage("hpBar");
	_hpBar.posLT = { 61, 54 };
	_hpBar.rc = RectMake(61, 54, _hpBar.img->GetWidth(), _hpBar.img->GetHeight());
	_hpBarCurWid = _hpBar.img->GetWidth();

	_hpBackBar.img = IMAGEMANAGER->findImage("backBar");
	_hpBackBar.posLT = _hpBar.posLT;
	_hpBackBar.rc = _hpBar.rc;
	_hpBackBarCurWid = _hpBackBar.img->GetWidth();

	_mpBar.img = IMAGEMANAGER->findImage("mpBar");
	_mpBar.posLT = { 118, 91 };
	_mpBar.rc = RectMake(118, 91, _mpBar.img->GetWidth(), _mpBar.img->GetHeight());
	_mpBarCurWid = _mpBar.img->GetWidth();

	_playerPortrait.img = IMAGEMANAGER->findImage("portraitRed");
	_playerPortrait.img->SetFrameX(0);
	_playerPortrait.img->SetFrameY(0);
	_playerPortrait.posLT = { 61,54 };
	_playerPortrait.rc = RectMake(61, 54, _playerPortrait.img->getFrameWidth(), _playerPortrait.img->getFrameHeight());

	_maxMp = MAX_MP;

	//	임시설정
	_maxHp = 500;


	return S_OK;
}

void playerStatusUI::release()
{
}

void playerStatusUI::update()
{
	SetRatioFunc();
	DimHpBackBarFunc();
	DimMpBarFunc();

}

void playerStatusUI::render()
{
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
	_mpBar.img->render(getMemDC(), _mpBar.posLT.x, _mpBar.posLT.y, 0, 0,
		_mpBarCurWid, _mpBar.img->GetHeight());

	// statusFrame
	_statusBarFrame.img->render(getMemDC(), _statusBarFrame.posLT.x, _statusBarFrame.posLT.y);

}

void playerStatusUI::SetRatioFunc()
{
	_hpRatio = _curHp / _maxHp;
	_mpRatio = _curMp / _maxMp;

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

void playerStatusUI::DimMpBarFunc()
{
	if (_mpBarCurWid > 0)
	{
		_mpBarCurWid -= MP_DIM_SPD;

		if (_mpBarCurWid < 0)	_mpBarCurWid = 0;
	}
}
