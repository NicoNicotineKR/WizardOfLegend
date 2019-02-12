#pragma once
#include "gameNode.h"
#include "printNumber.h"
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
	
	float _hpBarMaxWid;
	float _hpBarCurWid;
	float _hpBackBarCurWid;
	float _mpBarMaxWid;
	float _mpBarCurWid;

	tagImgSet _playerPortrait;

	float _curHp;
	float _curMp;
	float _maxHp;
	float _maxMp;
	float _hpRatio;
	float _mpRatio;

	printNumber* _printNum;
	POINT hpNumPos[7];
	int aryCurHp[3];
	int aryMaxHp[3];
	
	bool _isSignitureOn;
	int _mpAlpha;
	bool _isMpAlphaRising;


	const float BACK_HPBAR_DIM_SPD = 0.2;
	const float MP_DIM_SPD = 1;
	const float MAX_MP = 100;
	const int MPALPHA_BLINKSPD = 10;


public:
	playerStatusUI();
	~playerStatusUI();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void NumberRenderFunc();


	void SetRatioFunc();
	void DimHpBackBarFunc();
	void SetHpBackBarFunc();
	void MpAlphaFunc();
	


	


	void setCurHp(int curHp)	{ _curHp = curHp; }
	void setCurMp(float curMp)	{ _curMp = curMp; }
	void setMaxHp(int maxHp)	{ _maxHp = maxHp; }
	void setMaxMp(float maxMp)	{ _maxHp = maxMp; }
	void setIsSignitureOn(bool value) { _isSignitureOn = value; }


};