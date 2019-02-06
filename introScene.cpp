#include "stdafx.h"
#include "introScene.h"


introScene::introScene()
{
}


introScene::~introScene()
{
}

HRESULT introScene::init()
{
	IMAGEMANAGER->addImage("����ȭ��", "images/blackBackground.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڴ���ƾ", "images/nikonikotin.bmp", 653, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "images/niko.bmp", 651, 323, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/smoke.bmp", 768, 92, 12, 1, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("��������", "sound/logoSound.mp3", true, false);

	_nikotin = IMAGEMANAGER->findImage("���ڴ���ƾ");
	_nikotinAlpha = 0;

	_niko = IMAGEMANAGER->findImage("����");
	_nikoAlpha = 0;

	_smoke = IMAGEMANAGER->findImage("����");
	_smoke->setAlpahBlend(true, 255);
	_smokeAlpha = 0;
	_smokeIndex = 0;

	_startCount = 0;

	_isStart = false;
	_isOncePlaySound = false;
	_smokeImgFrameCount = 0;


	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	//��ٸ��� �������̴ٵǸ�, _isStart�� true���Ѵ�.
	StartWaitingFunc();

	if (_isStart == true)
	{
		_smokeImgFrameCount++;

		//ó���� ��Ʈ�����ߵ�
		FontAlphaFunc();
		//���ÿ� ������ ���;ߵ�
		PlayVoiceOnce();
		//��迬�� ���İ��� ���ߵ�
		SmokeAlphaFunc();
		//��迬��������
		SmokeFrameFunc();

		//�����̳������� ����»�̵���
		NikoEnterTheStage();
	}



}

void introScene::render()
{
	IMAGEMANAGER->render("����ȭ��", getMemDC());
	_niko->alphaRender(getMemDC(), WINSIZEX / 3 - 50, WINSIZEY / 3 - 50, _nikoAlpha);
	_nikotin->alphaRender(getMemDC(), WINSIZEX / 3 - 50, WINSIZEY / 3 - 100, _nikotinAlpha);


	_smoke->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 205, WINSIZEY / 2 - 10, _smokeIndex, 0, _smokeAlpha);
}

void introScene::StartWaitingFunc()
{
	if (_isStart == false)
	{
		_startCount++;
	}

	if (_startCount > WAITING_START_FRAME)
	{
		_isStart = true;
	}
}

void introScene::FontAlphaFunc()
{
	if (_nikotinAlpha < 255)
	{
		_nikotinAlpha += NIKOFONT_ALPHA_SPEED;
	}
	if (_nikotinAlpha >= 255)
	{
		_nikotinAlpha = 255;
	}
}

void introScene::PlayVoiceOnce()
{
	if (SOUNDMANAGER->isPlaySound("��������") == false && _isOncePlaySound == false)
	{
		SOUNDMANAGER->play("��������", 1.0f);
		_isOncePlaySound = true;
	}
}

void introScene::SmokeAlphaFunc()
{
	if (_smokeAlpha < 255)
	{
		_smokeAlpha += SMOKE_ALPHA_SPEED;
	}
	if (_smokeAlpha >= 255)
	{
		_smokeAlpha = 255;
	}
}

void introScene::SmokeFrameFunc()
{
	if (_smokeImgFrameCount > SMOKE_FRAME_SPEED)
	{
		_smokeImgFrameCount = 0;
		_smokeIndex++;

		if (_smokeIndex >= 12)
		{
			_smokeIndex = 0;
		}
	}
}

void introScene::NikoEnterTheStage()
{
	if (SOUNDMANAGER->isPlaySound("��������") == false && _isOncePlaySound == true)
	{
		if (_nikoAlpha < 255)
		{
			_nikoAlpha += NIKO_ALPHA_SPEED;
		}
		if (_nikoAlpha >= 255)
		{
			_nikoAlpha = 255;
		}
	}
}
