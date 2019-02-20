#include "stdafx.h"
#include "mainmenu.h"


mainmenu::mainmenu()
{
}


mainmenu::~mainmenu()
{
}

HRESULT mainmenu::init()
{
	IMAGEMANAGER->addImage("blackWindow", "images/blackBackground.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("titleScreen", "images/mainmenu/titleScreen.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pressTheEnterButton", "images/mainmenu/pressTheEnterButton.bmp", 322, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("titleLogo", "images/mainmenu/titleLogo.bmp", 1000, 185, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("titlemenu", "images/mainmenu/titlemenu.bmp", 414, 235, 2, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("loading", "images/mainmenu/loading.bmp", 480, 62, 10, 1, true, RGB(255, 0, 255));

	SOUNDMANAGER->play("titleMusic", 1);

	_loading = IMAGEMANAGER->findImage("loading");
	_loading->setAlpahBlend(true, 255);
	_loadingAlpha = 255;

	_title = IMAGEMANAGER->findImage("titleScreen");
	_titleAlpha = 0;

	_pressTheEnterButton = IMAGEMANAGER->findImage("pressTheEnterButton");
	_pressTheEnterButtonAlpha = 0;
	_isPressTheEnterButtonOn = false;

	_titleLogo = IMAGEMANAGER->findImage("titleLogo");
	_titleLogoAlpha = 0;
	_titleLogoIdxY = 380;

	for (int i = 0; i < 5; i++)
	{
		_button[i].imgAlpha = 0;
		_button[i].img = IMAGEMANAGER->findImage("titlemenu");
		_button[i].img->setAlpahBlend(true, _button[i].imgAlpha);
		_button[i].idxX = 0;
		_button[i].idxY = i;
		_button[i].pos.x = WINSIZEX / 2;
		_button[i].pos.y = WINSIZEY / 2 + i * 80;
		_button[i].rc = RectMakeCenter(_button[i].pos.x, _button[i].pos.y, 207, 47);
	}
	_selectMenu = SINGLE_PLAYER;
	_button[_selectMenu].idxX = 1;

	_startCount = 0;

	_mainMenuState = RUN_WIZARD;

	_mapEditor = new mapEditor;
	SCENEMANAGER->addScene("mapEditor",_mapEditor);

	SOUNDMANAGER->stop(OPTIONMANAGER->getTempSoundName());
	SOUNDMANAGER->play("titleMusic", OPTIONMANAGER->getSoundBackVolume());
	OPTIONMANAGER->setTempSoundName("titleMusic");

	return S_OK;
}

void mainmenu::release()
{
}

void mainmenu::update()
{
	//스킵기능
	if (_mainMenuState < MAIN_MENU)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_mainMenuState = MAIN_MENU;
			_titleAlpha = 255;
			_titleLogoAlpha = 255;
			_titleLogoIdxY = TITLELOGO_POS_Y;
			for (int i = 0; i < 5; i++)
			{
				_button[i].imgAlpha = 255;
			}
			_selectMenu = SINGLE_PLAYER;
			_button[_selectMenu].idxX = 1;
		}
	}

	RunWizard();

	TitleAlphaUp();

	PressTheEnterButton();

	MoveTheTitleFont();

	SelectMenu();

	EnterTheOption();
	

	if (_mainMenuState == MAIN_MENU)
	{
		if (_selectMenu == MAP_TOOL)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
			{
				SCENEMANAGER->changeScene("mapEditor");
			}
		}
	}

	if (_mainMenuState == MAIN_MENU)
	{
		if (_selectMenu == END)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
			{
				PostQuitMessage(0);
			}
		}
	}

	if (_mainMenuState == MAIN_MENU)
	{
		if (_selectMenu == SINGLE_PLAYER)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
			{
				SCENEMANAGER->changeScene("home");
			}
		}
	}


}

void mainmenu::render()
{
	IMAGEMANAGER->render("blackWindow", getMemDC());
	_loading->alphaFrameRender(getMemDC(), WINSIZEX - 150, WINSIZEY - 150, _loadingIdx, 0, _loadingAlpha);
	_title->alphaRender(getMemDC(), _titleAlpha);
	_pressTheEnterButton->alphaRender(getMemDC(), WINSIZEX / 2 - _pressTheEnterButton->GetWidth() / 2, WINSIZEY - 200, _pressTheEnterButtonAlpha);
	_titleLogo->alphaRender(getMemDC(), WINSIZEX / 2 - _titleLogo->GetWidth() / 2, _titleLogoIdxY, _titleLogoAlpha);


	for (int i = 0; i < 5; i++)
	{
		//Rectangle(getMemDC(), _button[i].rc);
		_button[i].img->alphaFrameRender(getMemDC(), _button[i].rc.left, _button[i].rc.top, _button[i].idxX, _button[i].idxY, _button[i].imgAlpha);
	}


	//char str[128];
	//sprintf_s(str, " 메뉴 : %d", _selectMenu);
	//TextOut(getMemDC(), 50, 50, str, strlen(str));

}

void mainmenu::RunWizard()
{
	if (_mainMenuState == RUN_WIZARD)
	{
		_loadingFrameCount++;

		if (_loadingFrameCount / 10 > 0)
		{
			_loadingIdx++;
			_loadingFrameCount = 0;
			if (_loadingIdx == 10)
			{
				_loadingIdx = 0;
			}
		}
	}
}

void mainmenu::TitleAlphaUp()
{
	//처음대기시간
	if (_mainMenuState == RUN_WIZARD)
	{
		_startCount++;
		if (_startCount > TITLE_START_COUNT)
		{
			_mainMenuState = TITLE_ALPHA_UP;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)))
		{
			_mainMenuState = TITLE_ALPHA_UP;
		}
	}

	if (_mainMenuState == TITLE_ALPHA_UP)
	{
		if (_loadingAlpha > 0)
		{
			_loadingAlpha -= LOADING_ALPHA_SPEED;
		}
		if (_loadingAlpha <= 0)
		{
			_loadingAlpha = 0;
		}

		if (_loadingAlpha == 0)
		{
			if (_titleAlpha < 255)
			{
				_titleAlpha += TITLE_ALPHA_UP_SPEED;
				_titleLogoAlpha += TITLE_ALPHA_UP_SPEED;
			}

			if (_titleAlpha >= 255)
			{
				_titleAlpha = 255;
				_mainMenuState = PRESS_ENTER;
			}
			if (_titleLogoAlpha >= 255)
			{
				_titleLogoAlpha = 255;
			}
		}
	}
}

void mainmenu::PressTheEnterButton()
{
	if (_mainMenuState == PRESS_ENTER)
	{
		if (_isPressTheEnterButtonBlink == false)		// _isPressEnterButtonAlphaRise
		{
			if (_pressTheEnterButtonAlpha < 255)
			{
				_pressTheEnterButtonAlpha += PRESS_THE_ENTER_BUTTON_BLINK_SPEED;
			}
			if (_pressTheEnterButtonAlpha >= 255)
			{
				_pressTheEnterButtonAlpha = 255;
				_isPressTheEnterButtonBlink = true;
			}
		}

		if (_isPressTheEnterButtonBlink == true)
		{
			if (_pressTheEnterButtonAlpha > PRESS_THE_ENTER_BUTTON_ALPHA_MIN)
			{
				_pressTheEnterButtonAlpha -= PRESS_THE_ENTER_BUTTON_BLINK_SPEED;
			}
			if (_pressTheEnterButtonAlpha <= PRESS_THE_ENTER_BUTTON_ALPHA_MIN)
			{
				_pressTheEnterButtonAlpha = PRESS_THE_ENTER_BUTTON_ALPHA_MIN;
				_isPressTheEnterButtonBlink = false;
			}
		}
	}

	//렌더부분
	if (_mainMenuState != PRESS_ENTER)
	{
		_pressTheEnterButtonAlpha = 0;
	}
}

void mainmenu::MoveTheTitleFont()
{
	if (_mainMenuState == PRESS_ENTER && _titleAlpha == 255)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_mainMenuState = MOVE_THE_TITLE_FONT;
		}
	}

	if (_mainMenuState == MOVE_THE_TITLE_FONT)
	{
		//알파값
		if (_titleAlpha > TITLE_ALPHA_MIN)
		{
			_titleAlpha -= TITLE_ALPHA_DOWN_SPEED;
		}
		if (_titleAlpha <= TITLE_ALPHA_MIN)
		{
			_titleAlpha = TITLE_ALPHA_MIN;
		}

		//로고 움직일값
		if (_titleLogoIdxY > TITLELOGO_POS_Y)
		{
			_titleLogoIdxY -= TITLELOGO_MOVE_SPEED;
		}
		if (_titleLogoIdxY <= TITLELOGO_POS_Y)
		{
			_titleLogoIdxY = TITLELOGO_POS_Y;
		}

		if (_titleLogoIdxY == TITLELOGO_POS_Y)
		{
			_mainMenuState = MAIN_MENU;

			for (int i = 0; i < 5; i++)
			{
				_button[i].imgAlpha = 255;
			}
		}
	}
}

void mainmenu::SelectMenu()
{
	if (_mainMenuState == MAIN_MENU)
	{
		//for (int i = 0; i < 5; i++)
		//{
		//	_button[i].imgAlpha = 255;
		//}

		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			if (_selectMenu >= 4)
			{
				_selectMenu = 0;
				_button[_selectMenu].idxX = 1;
				_button[_selectMenu + 4].idxX = 0;
			}
			else if (_selectMenu < 4)
			{
				_button[_selectMenu].idxX = 0;
				_button[_selectMenu + 1].idxX = 1;
				_selectMenu++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			if (_selectMenu <= 0)
			{
				_selectMenu = 4;
				_button[_selectMenu].idxX = 1;
				_button[_selectMenu - 4].idxX = 0;
			}
			else if (_selectMenu > 0)
			{
				_button[_selectMenu].idxX = 0;
				_button[_selectMenu - 1].idxX = 1;
				_selectMenu--;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&_button[i].rc, _ptMouse))
			{
				_button[_selectMenu].idxX = 0;
				_selectMenu = i;
				_button[_selectMenu].idxX = 1;
			}
		}
	}
}

void mainmenu::EnterTheOption()
{
	if (_mainMenuState == MAIN_MENU)
	{
		if (_selectMenu == OPTION)
		{
			if ((KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_LBUTTON)))
			{
				_mainMenuState = SELECT_OPTION;
				OPTIONMANAGER->setIsStartOption(true);
			}
		}
	}

	if (_mainMenuState == SELECT_OPTION)
	{
		if (_titleLogoAlpha > 0)
		{
			_titleLogoAlpha -= TITLELOGO_ALPHA_DOWN_SPEED;
		}
		if (_titleLogoAlpha <= 0)
		{
			_titleLogoAlpha = 0;
		}
	}

	if (_mainMenuState == SELECT_OPTION)
	{
		if (OPTIONMANAGER->getIsStartOption() == false)
		{
			this->OptionPressBack(4, 255);
		}
	}

}

void mainmenu::OptionPressBack(int mainMenuState, int titleLogoAlpha)
{
	this->setMainMenuState(mainMenuState);
	this->setTitleLogoAlpha(titleLogoAlpha);
}



