#include "stdafx.h"
#include "dialogueMaker.h"


dialogueMaker::dialogueMaker()
{
}


dialogueMaker::~dialogueMaker()
{
}

HRESULT dialogueMaker::init()
{
	IMAGEMANAGER->addImage("chatBoxImg", "images/dialogueMaker/chatBox.bmp", 1440, 225, true, RGB(255, 0, 255));
	_chatBoxImg = IMAGEMANAGER->findImage("chatBoxImg");

	_text.clear();

	_isStart = false;
	_time = 0;
	_printSpeed = 0;
	_printLen = 0;
	_printSpeed = 0.0f;
	_text.append(" ");

	return S_OK;
}

void dialogueMaker::release()
{
	//폰트가 실행됨
	//폰트가 모두 진행됫다는걸 알려줌
}

void dialogueMaker::update()
{
	if (_isStart == true)
	{
		_time += TIMEMANAGER->getElapsedTime();
		if (_time >= _printSpeed)
		{
			_time = 0;
			if (_printLen < _text.size())
			{
				tmpChar = _text.at(_printLen);

				if (0 <= tmpChar && tmpChar < 128)
				{
					_printLen += 1;
				}
				else
				{
					_printLen += 2;
				}

				if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown('F'))
				{
					_printLen = _text.size();
				}
			}
			else if (_printLen == _text.size())
			{
				if (KEYMANAGER->isOnceKeyDown(VK_RETURN) || KEYMANAGER->isOnceKeyDown('F'))
				{
					_isStart = false;
					//this->setDialogue(_npcName, _text, _printSpeed);
				}
			}
		}
	}
}



void dialogueMaker::render()
{
	if (_isStart == true)
	{
		HFONT font, oldFont;

		font = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "쉐도우9");
		oldFont = (HFONT)SelectObject(getMemDC(), font);

		_chatBoxImg->alphaRender(getMemDC(), (WINSIZEX - 1440) / 2, WINSIZEY - 285, 250);

		_npcPicture->render(getMemDC(), 100, WINSIZEY - 265);

		TextOut(getMemDC(), 330, WINSIZEY - _chatBoxImg->GetHeight() + 50, _text.c_str(), _printLen);
		SelectObject(getMemDC(), oldFont);
		DeleteObject(font);
	}

	char str[128];
	sprintf_s(str, "%d", _printLen);
	TextOut(getMemDC(), WINSIZEX / 2, 100, str, strlen(str));
}

void dialogueMaker::setDialogue(image* npcPicture, string text, float talkSpeed)
{
	_npcPicture = npcPicture;
	_text = text;
	_printSpeed = talkSpeed;
	_isStart = false;
}
