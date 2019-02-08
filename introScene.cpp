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
	IMAGEMANAGER->addImage("blackWindow", "images/blackBackground.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("nikonikotin", "images/introScene/nikonikotin.bmp", 653, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("niko", "images/introScene/niko.bmp", 651, 323, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smoke", "images/introScene/smoke.bmp", 768, 92, 12, 1, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("logoSound", "sound/logoSound.mp3", true, false);

	_nikotin = IMAGEMANAGER->findImage("nikonikotin");
	_nikotinAlpha = 0;

	_niko = IMAGEMANAGER->findImage("niko");
	_nikoAlpha = 0;

	_smoke = IMAGEMANAGER->findImage("smoke");
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
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeScene("mainmenu");
	}

	//기다리는 프레임이다되면, _isStart를 true로한다.
	StartWaitingFunc();

	if (_isStart == true)
	{
		_smokeImgFrameCount++;

		//처음에 폰트가떠야됨
		FontAlphaFunc();
		//동시에 음성이 나와야됨
		PlayVoiceOnce();
		//담배연기 알파값도 떠야됨
		SmokeAlphaFunc();
		//담배연기프레임
		SmokeFrameFunc();
		//음성이끝낫을때 니코쨩이등장
		NikoEnterTheStage();
	}



}

void introScene::render()
{
	IMAGEMANAGER->render("blackWindow", getMemDC());
	_niko->alphaRender(getMemDC(), WINSIZEX / 3 - 50, WINSIZEY / 3 - 50, _nikoAlpha);
	_nikotin->alphaRender(getMemDC(), WINSIZEX / 3 - 50, WINSIZEY / 3 - 100, _nikotinAlpha);


	_smoke->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 205, WINSIZEY / 2 - 10, _smokeIndex, 0, _smokeAlpha);
	
	//SOUNDMANAGER->isPlaySound("logoSound") == false && _isOncePlaySound == true

	//char str[128];
	//sprintf_s(str, " 음악플레이 : %d , %d", SOUNDMANAGER->isPlaySound("logoSound"), _isOncePlaySound);
	//TextOut(getMemDC(), 50, 50, str, strlen(str));


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
	if (SOUNDMANAGER->isPlaySound("logoSound") == false && _isOncePlaySound == false)
	{
		bool tmpIsSoundPlay = false;
		tmpIsSoundPlay = SOUNDMANAGER->play("logoSound", 1.0f);
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
	if (SOUNDMANAGER->isPlaySound("logoSound") == false && _isOncePlaySound == true)
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
