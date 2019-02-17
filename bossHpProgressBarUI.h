#pragma once
#include "gameNode.h"
class bossHpProgressBarUI : public gameNode
{
private:
	
	image* _barFrameImg;
	image* _hpBarImg;
	image* _hpBackBarImg;
	POINT _barFramePos;
	RECT _barFrameRc;
	RECT _barRc;
	
	
	float _ratio;
	float _hpBarCurWid;
	float _hpBackBarCurWid;
	float _hpBarHei;
	float _hpBarMaxWid;
	float _hpBackBarMaxWid;

	int* _maxHp;
	int* _curHp;
	

	bool* _isStart;


	bool _isInitAniEnd;


	const float INIT_ANI_RATIOSPD = 0.005f;
	const float BACKBAR_DIMSPD = 0.2f;

public:
	bossHpProgressBarUI();
	~bossHpProgressBarUI();

	HRESULT init(int* maxHp, int* curHp, bool* isBossStart);
	void release();
	void update();
	void render();

	void InitAniFunc();
	inline void HpCurWidFunc();
	inline void HpBackBarCurWidFunc();

};

