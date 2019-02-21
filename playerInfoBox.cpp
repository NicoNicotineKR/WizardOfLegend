#include "stdafx.h"
#include "playerInfoBox.h"
#include "player.h"


playerInfoBox::playerInfoBox()
{
}


playerInfoBox::~playerInfoBox()
{
}

HRESULT playerInfoBox::init()
{
	_isStart = false;

	IMAGEMANAGER->addImage("box", "images/UIs/playerInfoBox/playerinfoBox.bmp", 480, 705, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("edge", "images/UIs/playerInfoBox/buttonFrameIcon2.bmp", 70, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("changeFont", "images/UIs/playerInfoBox/changeFont.bmp", 354, 45, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("button", "images/UIs/playerInfoBox/playerinfoBoxButton.bmp", 360, 60, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("buttonBox", "images/UIs/playerInfoBox/buttonFrameIcon1.bmp", 120, 60, 2, 1, true, RGB(255, 0, 255));

	_skillIconList = new skillIconList;
	_skillIconList->init();

	_box.img = IMAGEMANAGER->findImage("box");
	_box.pos.x = 200;
	_box.pos.y = 100;

	char str2[128];

	for (int i = 0; i < 6; i++)
	{
		_button[i].img = IMAGEMANAGER->findImage("button");
		_button[i].frameX = i;
		_button[i].pos.x = 235 + i * 70;
		_button[i].pos.y = 140;

		_skillBox[i].pos.x = 270 + i * 70;
		_skillBox[i].pos.y = 230;
		_skillBox[i].boxNumber = i;
		_skillBox[i].boxFrameX = 0;
		_skillBox[i].alpha = 255;
		_skillBox[i].isBlink = false;
		_skillBox[i].isBlinkUp = false;
		_skillBox[i].img = IMAGEMANAGER->findImage("buttonBox");
		//�ٲܳ༮
		sprintf_s(str2, "%d", i);
		_skillBox[i].skillName = str2;
		_skillBox[i].rc = RectMakeCenter(_skillBox[i].pos.x, _skillBox[i].pos.y, 70, 70);
		_skillBox[i].skillImg = IMAGEMANAGER->findImage("skillIcons");
	}

	_skillBoxEdge.image = IMAGEMANAGER->findImage("edge");
	_skillBoxEdge.alpha = 255;

	_changeModeImg.image = IMAGEMANAGER->findImage("changeFont");
	_changeModeImg.alpha = 255;
	_changeModeImg.pos.x = 280;
	_changeModeImg.pos.y = 300;
	_changeModeImg.FrameX = 0;
	_changeModeImg.rc = RectMakeCenter(_changeModeImg.pos.x, _changeModeImg.pos.y, 118, 45);

	_selectIdx = 0;
	_isChanging = false;

	_skillBox[0].skillName = _player->getCurSkills1()->getName();
	_skillBox[1].skillName = _player->getCurSkills2()->getName();
	_skillBox[2].skillName = _player->getCurSkills3()->getName();
	_skillBox[3].skillName = _player->getCurSkills4()->getName();



	return S_OK;
}
void playerInfoBox::release()
{

}
void playerInfoBox::update()
{
	_skillIconList->update();

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_isStart == false)
		{
			_isStart = true;
			//�׵θ� ù��°�� �̵�
			_skillBoxEdge.pos.x = _skillBox[0].pos.x - 5;
			_skillBoxEdge.pos.y = _skillBox[0].pos.y - 5;
			_skillBoxEdge.rc = RectMakeCenter(_skillBoxEdge.pos.x, _skillBoxEdge.pos.y, 70, 70);


		}
		else if (_isStart == true)
		{
			_isStart = false;
		}
	}

	if (_isStart == true)
	{
		//���2 - ��ų��ȣ�ٲٱ� 
		if (_isChanging == false)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//���� ���õ� Idx�� ���õ� ��ų�ڽ��� ����
				_currentboxNumber = _skillBox[_selectIdx].boxNumber;

				//��¦�� ����(�ʷϻ�)
				_skillBox[_selectIdx].boxFrameX = 1;
				_skillBox[_selectIdx].isBlink = true;

				//��ų�ڽ��� �����̴� �ӵ� ����
				_skillBoxEdge.alpha = 255;
				_changeModeImg.FrameX = 1;
				_changeModeImg.isBlink = true;
				_changeModeImg.alpha = 255;
				_isChanging = true;
			}
		}
		else if (_isChanging == true)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				//�ٲٱ����� �̸� Idx�� ����
				_saveSkillName = _skillBox[_selectIdx].skillName;
				//�Ʊ� ��ų ����� ��ų�ڽ� ��ȣ�� Ŭ���� ��ų�ڽ��� �־���
				_skillBox[_selectIdx].skillName = _skillBox[_currentboxNumber].skillName;
				_player->changeCurSkill(_selectIdx, _skillBox[_currentboxNumber].skillName);
				//�Ʊ� ����� ��ų�ڽ��� ����� Idx�� ��ȯ
				_skillBox[_currentboxNumber].skillName = _saveSkillName;
				_player->changeCurSkill(_currentboxNumber, _saveSkillName);

				//_currentboxNumber, _selectIdx
				//����
				//_player->changeCurSkill(_currentboxNumber, "FlameStrike");
				////���õȾ�
				//_player->changeCurSkill(_selectIdx, "flameStrike");







				_skillBox[_currentboxNumber].isBlink = false;
				_skillBox[_currentboxNumber].boxFrameX = 0;
				_skillBox[_currentboxNumber].alpha = 255;
				_skillBox[_selectIdx].boxFrameX = 0;
				_skillBox[_selectIdx].isBlink = false;

				_changeModeImg.FrameX = 0;
				_changeModeImg.isBlink = false;
				_isChanging = false;
				_changeModeImg.alpha = 255;
			}
		}

		//���3 - �ڽ����ڰŸ�
		for (int i = 0; i < 6; i++)
		{
			if (_skillBox[i].isBlink == true)
			{
				if (_skillBox[i].isBlinkUp == false)
				{
					//if (_skillBox[i].alpha > BLINK_ALPHA_MIN)
					//{
					_skillBox[i].alpha -= BLINK_ALPHA_SPEED;
					//}
					if (_skillBox[i].alpha <= BLINK_ALPHA_MIN)
					{
						_skillBox[i].alpha = BLINK_ALPHA_MIN;
						_skillBox[i].isBlinkUp = true;
					}
				}
				if (_skillBox[i].isBlinkUp == true)
				{
					//if (_skillBox[i].alpha < 255)
					//{
					_skillBox[i].alpha += BLINK_ALPHA_SPEED;
					//}
					if (_skillBox[i].alpha >= 255)
					{
						_skillBox[i].alpha = 255;
						_skillBox[i].isBlinkUp = false;
					}
				}
			}
		}

		//���4 - ���콺����
		for (int i = 0; i < 4; i++)
		{
			if (i == 1)continue;

			if (PtInRect(&_skillBox[i].rc, _ptMouse))
			{
				_selectIdx = _skillBox[i].boxNumber;
				_skillBoxEdge.pos.x = _skillBox[i].pos.x - 5;
				_skillBoxEdge.pos.y = _skillBox[i].pos.y - 5;
				_skillBoxEdge.rc = RectMakeCenter(_skillBoxEdge.pos.x, _skillBoxEdge.pos.y, 70, 70);
			}
		}

		//���4-1 - Ű���弱��(������)
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_selectIdx < 4)
			{
				_selectIdx++;
				if (_selectIdx == 1) { _selectIdx++; }
				_skillBoxEdge.pos.x = _skillBox[_selectIdx].pos.x - 5;
				_skillBoxEdge.pos.y = _skillBox[_selectIdx].pos.y - 5;
				_skillBoxEdge.rc = RectMakeCenter(_skillBoxEdge.pos.x, _skillBoxEdge.pos.y, 70, 70);
			}
			if (_selectIdx >= 4)
			{
				_selectIdx = 0;
				_skillBoxEdge.pos.x = _skillBox[_selectIdx].pos.x - 5;
				_skillBoxEdge.pos.y = _skillBox[_selectIdx].pos.y - 5;
				_skillBoxEdge.rc = RectMakeCenter(_skillBoxEdge.pos.x, _skillBoxEdge.pos.y, 70, 70);
			}
		}
		//���4-2 - Ű���弱��(����)
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			if (_selectIdx > -1)
			{
				_selectIdx--;
				if (_selectIdx == 1) { _selectIdx--; }
				_skillBoxEdge.pos.x = _skillBox[_selectIdx].pos.x - 5;
				_skillBoxEdge.pos.y = _skillBox[_selectIdx].pos.y - 5;
				_skillBoxEdge.rc = RectMakeCenter(_skillBoxEdge.pos.x, _skillBoxEdge.pos.y, 70, 70);
			}
			if (_selectIdx <= -1)
			{
				_selectIdx = 3;
				_skillBoxEdge.pos.x = _skillBox[_selectIdx].pos.x - 5;
				_skillBoxEdge.pos.y = _skillBox[_selectIdx].pos.y - 5;
				_skillBoxEdge.rc = RectMakeCenter(_skillBoxEdge.pos.x, _skillBoxEdge.pos.y, 70, 70);
			}
		}



		//���5 - �׵θ�������
		if (_skillBoxEdge.isBlinkUp == false)
		{
			if (_skillBoxEdge.alpha > BLINK_ALPHA_MIN)
			{
				_skillBoxEdge.alpha -= BLINK_ALPHA_SPEED;
			}
			if (_skillBoxEdge.alpha <= BLINK_ALPHA_MIN)
			{
				_skillBoxEdge.alpha = BLINK_ALPHA_MIN;
				_skillBoxEdge.isBlinkUp = true;
			}
		}
		if (_skillBoxEdge.isBlinkUp == true)
		{
			if (_skillBoxEdge.alpha < 255)
			{
				_skillBoxEdge.alpha += BLINK_ALPHA_SPEED;
			}
			if (_skillBoxEdge.alpha >= 255)
			{
				_skillBoxEdge.alpha = 255;
				_skillBoxEdge.isBlinkUp = false;
			}
		}

		//���6 - ��ü��Ʈ������
		if (_changeModeImg.isBlink == true)
		{
			if (_changeModeImg.isBlinkUp == false)
			{
				if (_changeModeImg.alpha > BLINK_ALPHA_MIN)
				{
					_changeModeImg.alpha -= BLINK_ALPHA_SPEED;
				}
				if (_changeModeImg.alpha <= BLINK_ALPHA_MIN)
				{
					_changeModeImg.alpha = BLINK_ALPHA_MIN;
					_changeModeImg.isBlinkUp = true;
				}
			}
			if (_changeModeImg.isBlinkUp == true)
			{
				if (_changeModeImg.alpha < 255)
				{
					_changeModeImg.alpha += BLINK_ALPHA_SPEED;
				}
				if (_changeModeImg.alpha >= 255)
				{
					_changeModeImg.alpha = 255;
					_changeModeImg.isBlinkUp = false;
				}
			}
		}
	}

}
void playerInfoBox::render()
{
	_skillIconList->render();

	char str[128];

	if (_isStart == true)
	{
		_box.img->render(getMemDC(), _box.pos.x, _box.pos.y);

		for (int i = 0; i < 4; i++)
		{
			_button[i].img->frameRender(getMemDC(), _button[i].pos.x, _button[i].pos.y, _button[i].frameX, 0);

			_skillBox[i].img->alphaFrameRenderFixed(getMemDC(), _skillBox[i].rc.left, _skillBox[i].rc.top, _skillBox[i].boxFrameX, 0, _skillBox[i].alpha);

			_skillBox[i].skillImg->frameRender(getMemDC(), _skillBox[i].rc.left + 10, _skillBox[i].rc.top + 10,_skillIconList->FindSkillIdx(_skillBox[i].skillName).x, _skillIconList->FindSkillIdx(_skillBox[i].skillName).y);

			


		}

		_skillBoxEdge.image->alphaRender(getMemDC(), _skillBoxEdge.rc.left, _skillBoxEdge.rc.top, _skillBoxEdge.alpha);
		_changeModeImg.image->alphaFrameRenderFixed(getMemDC(), _changeModeImg.rc.left, _changeModeImg.rc.top, _changeModeImg.FrameX, 0, _changeModeImg.alpha);
	}

	sprintf_s(str, "_currentboxNumber : %d _selectIdx : %d", _currentboxNumber, _selectIdx);
	TextOut(getMemDC(), 20, 400, str, strlen(str));
}
