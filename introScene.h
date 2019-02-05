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

	//���� ��Ʈ ���İ� ���ǵ� ����ó��
	const int NIKOPONT_ALPHA_SPEED = 3;
	//�����İ� ���ǵ� ����ó��
	const int SMOKE_ALPHA_SPEED = 1;
	//���ڴ��׸� ���İ� ���ǵ� ����ó��
	const int NIKO_ALPHA_SPEED = 1;
public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

