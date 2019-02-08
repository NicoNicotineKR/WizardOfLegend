#include "stdafx.h"
#include "optionManager.h"


optionManager::optionManager()
{
}

optionManager::~optionManager()
{
}


HRESULT optionManager::init()
{
	IMAGEMANAGER->addImage("option", "images/option/option.bmp", 624, 725, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("longBar", "images/option/longBar.bmp", 40, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cursor", "images/option/cursor.bmp", 192,96,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("optionButton", "images/option/optionButton.bmp", 356, 304, 2, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ShortButton", "images/option/button.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));


	_optionImg = IMAGEMANAGER->findImage("option");
	_optionAlpha = 255;

	for (int i = 0; i < 6; i++)
	{
		_optionButton[i].pos.x = WINSIZEX / 2 - 200;
	}
	for (int i = 6; i < 8; i++)
	{
		_optionButton[i].pos.x = WINSIZEX / 2;
	}

	_optionButton[0].pos.y = WINSIZEY / 2 - 185;
	_optionButton[1].pos.y = WINSIZEY / 2 - 145;
	_optionButton[2].pos.y = WINSIZEY / 2 - 70;
	_optionButton[3].pos.y = WINSIZEY / 2 - 10;
	_optionButton[4].pos.y = WINSIZEY / 2 + 45;
	_optionButton[5].pos.y = WINSIZEY / 2 + 127;
	_optionButton[6].pos.y = WINSIZEY / 2 + 260;
	_optionButton[7].pos.y = WINSIZEY / 2 + 310;

	for (int i = 0; i < 8; i++)
	{
		_optionButton[i].imgAlpha = 255;
		_optionButton[i].img = IMAGEMANAGER->findImage("optionButton");
		_optionButton[i].img->setAlpahBlend(true, _optionButton[i].imgAlpha);
		_optionButton[i].idxX = 0;
		_optionButton[i].idxY = i;
		_optionButton[i].rc = RectMakeCenter(_optionButton[i].pos.x, _optionButton[i].pos.y, 178, 38);
	}
	_selectOption = EFFECT_SOUND;
	_optionButton[_selectOption].idxX = 1;

	for (int i = 0; i < 2; i++)
	{
		_smallButton[i].img = IMAGEMANAGER->findImage("ShortButton");
		_smallButton[i].idxX = 1;
		_smallButton[i].ratio = 1;
		_smallButton[i].idxY = 0;
		_smallButton[i].pos.x = WINSIZEX / 2 + 157;
		_smallButton[i].pos.y = WINSIZEY / 2 - 10 + i * 47;
		_smallButton[i].rc = RectMakeCenter(_smallButton[i].pos.x, _smallButton[i].pos.y, 32, 32);
	}


	_longButton[0].pos.y = 255;
	_longButton[1].pos.y = 295;
	_longButton[2].pos.y = 375;

	for (int i = 0; i < 3; i++)
	{
		_longButton[i].img = IMAGEMANAGER->findImage("longBar");
		_longButton[i].pos.x = CONTROLBAR_START_XPOS + CONTROLBAR_LENGTH / 2;
		_longButton[i].ratio = 0.5;
		_longButton[i].rc = RectMakeCenter(_longButton[i].pos.x + _longButton[i].img->GetWidth()/2, _longButton[i].pos.y + _longButton[i].img->GetHeight()/2, CONTROLBAR_LENGTH + _longButton[i].img->GetWidth(), 20);
	}

	_mouse = IMAGEMANAGER->findImage("cursor");

	for (int i = 0; i < 3; i++)
	{
		_isBarClick[i] = false;
	}

	return S_OK;
}

void optionManager::release()
{
}

void optionManager::update()
{
	if (_isStartOption == true)
	{
		SelectOption();
	}
}

void optionManager::render()
{

	char str[1000];

	if (_isStartOption == true)
	{
		_optionImg->alphaRender(getMemDC(), WINSIZEX / 2 - _optionImg->GetWidth() / 2, WINSIZEY / 2 - _optionImg->GetHeight() / 2, _optionAlpha);

		for (int i = 0; i < 8; i++)
		{
			_optionButton[i].img->alphaFrameRender(getMemDC(), _optionButton[i].rc.left, _optionButton[i].rc.top, _optionButton[i].idxX, _optionButton[i].idxY, _optionButton[i].imgAlpha);
		}

		for (int i = 0; i < 2; i++)
		{
			_smallButton[i].img->alphaFrameRender(getMemDC(), _smallButton[i].rc.left, _smallButton[i].rc.top, _smallButton[i].idxX, _smallButton[i].idxY);
		
			//sprintf_s(str, "%f", _smallButton[i].ratio);
			//TextOut(getMemDC(), WINSIZEX / 2, 20 + i * 20, str, strlen(str));
		}

		for (int i = 0; i < 3; i++)
		{
			_longButton[i].img->render(getMemDC(), _longButton[i].pos.x, _longButton[i].pos.y);
			
			//sprintf_s(str,"%f", _longButton[i].ratio);
			//TextOut(getMemDC(),WINSIZEX/2,100+i*20,str,strlen(str));
		}
	}

	//if ((0 < _ptMouse.x && _ptMouse.x < WINSIZEX) && (0 < _ptMouse.y && _ptMouse.y < WINSIZEY))
	//{
		_mouse->frameRender(getMemDC(), _ptMouse.x - _mouse->getFrameWidth() / 2, _ptMouse.y - _mouse->getFrameHeight() / 2, _smallButton[1].ratio, 0);
	//}
}

void optionManager::SelectOption()
{
	//선택 옵션 조절
	UpDownSelectOption();

	//볼륨조절
	longButtonControl();

	//버튼형 조절
	ShortButtonControl();

	//리셋버튼
	resetResult();

	//게임으로 돌아가기
	backTheGame();
}

void optionManager::UpDownSelectOption()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_selectOption >= E_OPTION_KINDS_END)
		{
			_selectOption = 0;
			_optionButton[_selectOption].idxX = 1;
			_optionButton[_selectOption + 7].idxX = 0;
		}
		else if (_selectOption < E_OPTION_KINDS_END)
		{
			_optionButton[_selectOption].idxX = 0;
			_optionButton[_selectOption + 1].idxX = 1;
			_selectOption++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_selectOption <= 0)
		{
			_selectOption = 7;
			_optionButton[_selectOption].idxX = 1;
			_optionButton[_selectOption - 7].idxX = 0;
		}
		else if (_selectOption > 0)
		{
			_optionButton[_selectOption].idxX = 0;
			_optionButton[_selectOption - 1].idxX = 1;
			_selectOption--;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (PtInRect(&_optionButton[i].rc, _ptMouse))
		{
			_optionButton[_selectOption].idxX = 0;
			_selectOption = i;
			_optionButton[_selectOption].idxX = 1;
		}
	}
}

void optionManager::backTheGame()
{
	if (_selectOption == BACK)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_isStartOption = false;
		}
	}
}

void optionManager::ShortButtonControl()
{
	//몬스터를 때릴시 숫자를 보일것인가
	if (_selectOption == NUMBER_VISION)
	{
		NumberVision();
	}

	//커서 모양을 바꿀것인가
	if (_selectOption == SYSTEM_CURSOR)
	{
		SystemCursor();
	}

	for (int i = 0; i < 2; i++)
	{
		if (PtInRect(&_smallButton[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_isBarClick[0] == false && _isBarClick[1] == false && _isBarClick[2] == false)
				{
					_optionButton[_selectOption].idxX = 0;
					_selectOption = i + 3;
					_optionButton[_selectOption].idxX = 1;

					if (_smallButton[i].idxX == 0)
					{
						_smallButton[i].idxX = 1;
						_smallButton[i].ratio = 1;
					}
					else if (_smallButton[i].idxX == 1)
					{
						_smallButton[i].idxX = 0;
						_smallButton[i].ratio = 0;
					}
				}
			}
		}
	}

	for (int i = 3; i < 5; i++)
	{
		if (PtInRect(&_optionButton[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_optionButton[_selectOption].idxX = 0;
				_selectOption = i;
				_optionButton[_selectOption].idxX = 1;

				if (_smallButton[i - 3].idxX == 0)
				{
					_smallButton[i - 3].idxX = 1;
					_smallButton[i - 3].ratio = 1;
				}
				else if (_smallButton[i - 3].idxX == 1)
				{
					_smallButton[i - 3].idxX = 0;
					_smallButton[i - 3].ratio = 0;
				}
			}
		}
	}
		
	
}

void optionManager::NumberVision()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_smallButton[0].idxX == 0)
		{
			_smallButton[0].idxX = 1;
			_smallButton[0].ratio = 1;
		}
		else if (_smallButton[0].idxX == 1)
		{
			_smallButton[0].idxX = 0;
			_smallButton[0].ratio = 0;
		}
	}
}

void optionManager::SystemCursor()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_smallButton[1].idxX == 0)
		{
			_smallButton[1].idxX = 1;
			_smallButton[1].ratio = 1;
		}
		else if (_smallButton[1].idxX == 1)
		{
			_smallButton[1].idxX = 0;
			_smallButton[1].ratio = 0;
		}
	}
}

void optionManager::longButtonControl()
{
	//EFFECT_SOUND = 0,
	//MUSIC_SOUND = 1,
	//CAMERA_SHAKING = 2,
	for (int i = 0; i < 3; i++)
	{
		if (_selectOption == i)
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_longButton[i].pos.x < CONTROLBAR_END_XPOS)
				{
					_longButton[i].pos.x += CONTROLBAR_MOVE_SPEED;

					_longButton[i].ratio = (float)(_longButton[i].pos.x - CONTROLBAR_START_XPOS) / CONTROLBAR_LENGTH;
				}
				if (_longButton[i].pos.x >= CONTROLBAR_END_XPOS)
				{
					_longButton[i].pos.x = CONTROLBAR_END_XPOS;
					_longButton[i].ratio = (float)(_longButton[i].pos.x - CONTROLBAR_START_XPOS) / CONTROLBAR_LENGTH;
				}

			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (_longButton[i].pos.x > CONTROLBAR_START_XPOS)
				{
					_longButton[i].pos.x -= CONTROLBAR_MOVE_SPEED;
					_longButton[i].ratio = (float)(_longButton[i].pos.x - CONTROLBAR_START_XPOS) / CONTROLBAR_LENGTH;
				}
				if (_longButton[i].pos.x <= CONTROLBAR_START_XPOS)
				{
					_longButton[i].pos.x = CONTROLBAR_START_XPOS;
					_longButton[i].ratio = (float)(_longButton[i].pos.x - CONTROLBAR_START_XPOS) / CONTROLBAR_LENGTH;
				}
			}
		}

		if (PtInRect(&_longButton[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				if (_isBarClick[0] == false && _isBarClick[1] == false && _isBarClick[2] == false)
				{
					_isBarClick[i] = true;
				}
				//_longButton[i].pos.x = _ptMouse.x - _mouse->getFrameWidth() / 4;
			}
		}

		if (_isBarClick[i] == true)
		{
			_longButton[i].pos.x = _ptMouse.x - _mouse->getFrameWidth() / 4;
			if (_longButton[i].pos.x <= CONTROLBAR_START_XPOS)
			{
				_longButton[i].pos.x = CONTROLBAR_START_XPOS;
			}
			if (_longButton[i].pos.x >= CONTROLBAR_END_XPOS)
			{
				_longButton[i].pos.x = CONTROLBAR_END_XPOS;
			}
			_longButton[i].ratio = (float)(_longButton[i].pos.x - CONTROLBAR_START_XPOS) / CONTROLBAR_LENGTH;

			_optionButton[_selectOption].idxX = 0;
			_selectOption = i;
			_optionButton[_selectOption].idxX = 1;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = 0; i < 3; i++)
		{
			_isBarClick[i] = false;
		}
	}
}

void optionManager::resetResult()
{
	if (_selectOption == RESET)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//롱버튼들
			for (int i = 0; i < 3; i++)
			{
				_longButton[i].pos.x = CONTROLBAR_START_XPOS + CONTROLBAR_LENGTH/2;
				_longButton[i].ratio = 0.5;
			}

			for (int i = 0; i < 2; i++)
			{
				_smallButton[i].idxX = 1;
				_smallButton[i].ratio = 1;
			}
		}
	}
}

