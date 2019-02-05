#pragma once
#include "gameNode.h"
class introScene : public gameNode
{
private:
	image* _nikotin;
	int _nikotinAlpha;

	image* _niko;
	int _nikoAlpha;

	image* _smoke;
	int _smokeIndex;
	int _smokeAlpha;

	int _startCount;
	bool _stopVoice;

	//니코 폰트 알파값 스피드 예외처리
	const int NIKOPONT_ALPHA_SPEED = 3;
	//담배알파값 스피드 예외처리
	const int SMOKE_ALPHA_SPEED = 1;
	//니코담배그림 알파값 스피드 예외처리
	const int NIKO_ALPHA_SPEED = 1;
public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

