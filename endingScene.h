#pragma once
#include "gameNode.h"

class endingScene : public gameNode
{
private:
	struct tagDrawTxts
	{
		string txt;
		POINTFLOAT pos;
		RECT rc;
	};
	
	vector<tagDrawTxts*> _vTxt;

	image* _nikoImg;
	image* _teamLogoTxtImg;
	image* _smoke;
	int _nikoImgAlpha;
	int _teamLogoTxtImgAlpha;
	int _smokeImgAlpha;


	int _moveStrIdx[2];		//	begin, end
	int _startMoveCounter;
	int _txtStrNum;
	

	float _timer;

	int _smokeImgFrameCount;
	int _smokeIndex;

	bool _isNikoAlphaFinish;
	bool _isLogoTxtAlphaFinish;

	float _txtMoveSpd;
	
	
	const int MOVEUP_SPD_DEFAULT = 1;
	const int MOVEUP_SPD_FASTER = 8;

	const int START_MOVE_MAXCOUNT = 80;
	const int SMOKE_ALPHA_MAX = 100;
	//const int SMOKE_ALPHA_AUG = 10;
	const int SMOKE_FRAME_SPEED = 10;
	const int NIKOIMG_ALPHA_MAX = 100;
	const int NIKOIMG_ALPHA_AUG = 1;
	const int TEAMLOGOIMG_ALPHA_MAX = 100;
	const int TEAMLOGOIMG_ALPHA_AUG = 1;
	const int TXT_Y_GAP = 120;
	const int TXT_START_X = 0;


public:
	endingScene();
	~endingScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void AddString(string str);

	void AlphaIncreaseFunc();
	void SmokeFrameFunc();
	void MoveStrIdxCountFunc();
	void MoveTxts();
	void ChangeMoveSpd();
	void EndFunc();

	



	void StringRender();
};

