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
	IMAGEMANAGER->addImage("����ȭ��", "images/intro/blackBackground.bmp", 1600, 900, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���ڴ���ƾ", "images/intro/nikonikotin.bmp", 1600, 900, true, RGB(255, 0, 255));
	_nikotin = IMAGEMANAGER->findImage("���ڴ���ƾ");
	_nikotinAlpha = 0;

	IMAGEMANAGER->addImage("����", "images/intro/niko.bmp", 1600, 900, true, RGB(255, 0, 255));
	_niko = IMAGEMANAGER->findImage("����");
	_nikoAlpha = 0;

	IMAGEMANAGER->addFrameImage("����", "images/intro/smoke.bmp",768,92,12,1,true,RGB(255,0,255));
	_smoke = IMAGEMANAGER->findImage("����");
	_smoke->setAlpahBlend(true,255);
	_smokeAlpha = 0;
	_smokeIndex = 0;
	
	SOUNDMANAGER->addSound("��������","sound/logoSound.mp3",true,false);
	_startCount = 0;
	_stopVoice = false;
	

	return S_OK;
}

void introScene::release()
{
}

void introScene::update()
{
	_startCount++;

	if (_startCount >= 50)
	{
		if (_stopVoice == false)
		{
			SOUNDMANAGER->play("��������", 1);
			_stopVoice = true;
		}
	}

	//���� ��µɶ� �ΰ� õõ�� �����
	if (_stopVoice == true)
	{
		if (_nikotinAlpha < 255)
		{
			_nikotinAlpha += NIKOPONT_ALPHA_SPEED;
		}
		if (_smokeAlpha < 255)
		{
			_smokeAlpha += SMOKE_ALPHA_SPEED;
		}

		//�����İ� ���ǵ� ����ó��
		if (_smokeAlpha >= 255)
		{
			_smokeAlpha = 255;
		}


		if (_nikotinAlpha >= 255)
		{
			//���� ��Ʈ ���İ� ����ó��
			_nikotinAlpha = 255;

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

	if (_startCount % 10 == 0)
	{
		if (_smokeIndex < 12)
		{
			_smokeIndex++;
			if (_smokeIndex == 12)
			{
				_smokeIndex = 0;
			}
		}
	}
}

void introScene::render()
{
	IMAGEMANAGER->render("����ȭ��",getMemDC());
	_niko->alphaRender(getMemDC(), _nikoAlpha);
	_nikotin->alphaRender(getMemDC(), _nikotinAlpha);


	_smoke->alphaFrameRender(getMemDC(),WINSIZEX/2 - 205,WINSIZEY/2 - 10, _smokeIndex,0,_smokeAlpha);
}
