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
	IMAGEMANAGER->addImage("검은화면", "images/intro/blackBackground.bmp", 1600, 900, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("니코니코틴", "images/intro/nikonikotin.bmp", 1600, 900, true, RGB(255, 0, 255));
	_nikotin = IMAGEMANAGER->findImage("니코니코틴");
	_nikotinAlpha = 0;

	IMAGEMANAGER->addImage("니코", "images/intro/niko.bmp", 1600, 900, true, RGB(255, 0, 255));
	_niko = IMAGEMANAGER->findImage("니코");
	_nikoAlpha = 0;

	IMAGEMANAGER->addFrameImage("연기", "images/intro/smoke.bmp",768,92,12,1,true,RGB(255,0,255));
	_smoke = IMAGEMANAGER->findImage("연기");
	_smoke->setAlpahBlend(true,255);
	_smokeAlpha = 0;
	_smokeIndex = 0;
	
	SOUNDMANAGER->addSound("니코음성","sound/logoSound.mp3",true,false);
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
			SOUNDMANAGER->play("니코음성", 1);
			_stopVoice = true;
		}
	}

	//음성 출력될때 로고 천천히 띄워짐
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

		//담배알파값 스피드 예외처리
		if (_smokeAlpha >= 255)
		{
			_smokeAlpha = 255;
		}


		if (_nikotinAlpha >= 255)
		{
			//니코 폰트 알파값 예외처리
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
	IMAGEMANAGER->render("검은화면",getMemDC());
	_niko->alphaRender(getMemDC(), _nikoAlpha);
	_nikotin->alphaRender(getMemDC(), _nikotinAlpha);


	_smoke->alphaFrameRender(getMemDC(),WINSIZEX/2 - 205,WINSIZEY/2 - 10, _smokeIndex,0,_smokeAlpha);
}
