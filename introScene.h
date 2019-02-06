#pragma once
#include "gameNode.h"
class introScene : public gameNode
{
private:
	//폰트
	image* _nikotin;
	int _nikotinAlpha;

	//그림
	image* _niko;
	int _nikoAlpha;

	//담배
	image* _smoke;
	int _smokeIndex;
	int _smokeAlpha;

	int _startCount;

	bool _isStart;
	bool _isOncePlaySound;
	int _smokeImgFrameCount;



	//니코 폰트 알파값 스피드 예외처리
	const int NIKOFONT_ALPHA_SPEED = 3;
	//담배알파값 스피드 예외처리
	const int SMOKE_ALPHA_SPEED = 1;
	//니코담배그림 알파값 스피드 예외처리
	const int NIKO_ALPHA_SPEED = 2;

	const int WAITING_START_FRAME = 50;

	const int SMOKE_FRAME_SPEED = 10;
public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void StartWaitingFunc();
	void FontAlphaFunc();
	void PlayVoiceOnce();
	void SmokeAlphaFunc();
	void SmokeFrameFunc();
	void NikoEnterTheStage();
};

