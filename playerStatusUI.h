#pragma once
#include "gameNode.h"
class playerStatusUI : public gameNode
{
	struct tagImgSet {
		image* img;
		POINT posLT;
		RECT rc;
	};
	

	tagImgSet _statusBarFrame;
	tagImgSet _hpBar;
	tagImgSet _hpBackBar;
	tagImgSet _mpBar;
	
	int _hpBarCurWid;
	int _hpBackBarCurWid;
	int _mpBarCurWid;

	tagImgSet _playerPortrait;

	int _curHp;
	float _curMp;
	int _maxHp;
	float _maxMp;
	float _hpRatio;
	float _mpRatio;
	

	const int BACK_HPBAR_DIM_SPD = 1;
	const int MP_DIM_SPD = 2;
	const float MAX_MP = 100;


public:
	playerStatusUI();
	~playerStatusUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void SetRatioFunc();
	void DimHpBackBarFunc();
	void DimMpBarFunc();


	void setCurHp(int curHp) { _curHp = curHp; }
	void setCurMp(int curMp) { _curMp = curMp; }
	void setMaxHp(int maxHp) { _maxHp = maxHp; }
	void setMaxMp(int maxMp) { _maxHp = maxMp; }

};