#pragma once
#include "gameNode.h"
class introScene : public gameNode
{
private:
	//��Ʈ
	image* _nikotin;
	int _nikotinAlpha;

	//�׸�
	image* _niko;
	int _nikoAlpha;

	//���
	image* _smoke;
	int _smokeIndex;
	int _smokeAlpha;

	int _startCount;

	bool _isStart;
	bool _isOncePlaySound;
	int _smokeImgFrameCount;



	//���� ��Ʈ ���İ� ���ǵ� ����ó��
	const int NIKOFONT_ALPHA_SPEED = 3;
	//�����İ� ���ǵ� ����ó��
	const int SMOKE_ALPHA_SPEED = 1;
	//���ڴ��׸� ���İ� ���ǵ� ����ó��
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

