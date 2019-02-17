#include "stdafx.h"
#include "flameStrike.h"

HRESULT flameStrike::init(player * Player)
{
	_name = "FlameStrike";
	//_img = IMAGEMANAGER->findImage("flameStrike");
	//_img2 = IMAGEMANAGER->findImage("flameStrike");
	//_img3 = IMAGEMANAGER->findImage("flameStrike");

	_img = new image;
	_img->init("images/player/flameStrike.bmp", 2560, 256, 10, 1, true, RGB(255, 0, 255));
	_img2 = new image;
	_img2->init("images/player/flameStrike.bmp", 2560, 256, 10, 1, true, RGB(255, 0, 255));
	_img3 = new image;
	_img3->init("images/player/flameStrike.bmp", 2560, 256, 10, 1, true, RGB(255, 0, 255));


	_vvMap = Player->getVVMapMemoryAddress();
	_totalCoolTime = 1;
	_maxReLoad = 3;
	_imgCount = 0;
	_reLoadCount = 0;
	_curCoolTime = 0;
	_img->SetFrameX(0);
	_img->SetFrameY(0);
	_isSkill = false;
	_isSkillImgRender = false;
	return S_OK;
}

void flameStrike::release(player * Player)
{
}

void flameStrike::update(player * Player)
{

	if (_isSkillImgRender)
	{
		_imgCount += TIMEMANAGER->getElapsedTime();

		if (_imgCount > 0.05f)
		{
			_imgCount = 0;
			if (_img->getMaxFrameX() <= _img->getFrameX())
			{
				_isRender[0] = false;
			}
			else
			{
				if (_reLoadCount >= 1)
				{
					_img->SetFrameX(_img->getFrameX() + 1);
				}
			}

			if (_img2->getMaxFrameX() <= _img2->getFrameX())
			{
				_isRender[1] = false;
			}
			else
			{
				if (_isRender[1])
				{
					_img2->SetFrameX(_img2->getFrameX() + 1);
				}
			}

			if (_img3->getMaxFrameX() <= _img3->getFrameX())
			{
				_isSkillImgRender = false;
				_isRender[2] = false;
			}
			else
			{
				if (_isRender[2])
				{
					_img3->SetFrameX(_img3->getFrameX() + 1);
				}
			}
		}
	}

	if (_isSkill)
	{
		_attackCount += TIMEMANAGER->getElapsedTime();
		if (_maxReLoad >= _reLoadCount)
		{

			if (_attackCount > 0.5f)
			{
				_attackCount = 0;
				_reLoadCount = 0;
				Player->setState(STATE::IDLE);
				Player->currentPlayerState();
				Player->startAni();

				_isSkill = false;
			}
			if (_index != _reLoadCount)
			{
				_angle = Player->getPlayerAngle();
				if (Player->getAniDirection() != ANIDIRECTION::FRONT)
				{
					_pos.x = cosf(_angle) * 50 + (Player->getTileCheckRcPos().x + 14) - 128;
					_pos.y = -sinf(_angle) * 50 + (Player->getTileCheckRcPos().y + 14) - 192;
				}
				else
				{
					_pos.x = cosf(_angle) * 50 + (Player->getTileCheckRcPos().x + 14) - 128;
					_pos.y = -sinf(_angle) * 50 + (Player->getTileCheckRcPos().y + 14) - 128;
				}
				_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth() / 2, _pos.y + _img->getFrameHeight() / 2, 200, 200);
				_index = _reLoadCount;
				_attackCount = 0;
				if (_reLoadCount == 2)
				{
					_isRender[1] = true;
				}
				if (_reLoadCount == 3)
				{
					_isRender[2] = true;
				}
			}
		}
		else
		{
			_isSkill = false;
			_reLoadCount = 0;


		}
	}
	else
	{
		_collisionRc = RectMakeCenter(-400, -400, 200, 200);
	}
}

void flameStrike::render(player * Player)
{
	if (_isSkillImgRender)
	{
		Rectangle(getMemDC(), _collisionRc);
		if (_isRender[0])
		{
			_img->frameRender(Player->getPlayerMemDC(), _pos.x, _pos.y);

		}

		if (_isRender[1])
		{
			//if (Player->getAniDirection() != ANIDIRECTION::FRONT)
			//{
				_img2->frameRender(Player->getPlayerMemDC(), _pos.x, _pos.y);
			//}
			//else
			//{
			//	_img2->frameRender(Player->getPlayerMemDC(), _pos.x - 128, _pos.y - 128);
			//}
		}
		if (_isRender[2])
		{
			_img3->frameRender(Player->getPlayerMemDC(), _pos.x, _pos.y);

		}
	}
}

void flameStrike::skillPosSet(player * Player)
{
	_angle = Player->getPlayerAngle();
	if (Player->getAniDirection() != ANIDIRECTION::FRONT)
	{
		_pos.x = cosf(_angle) * 50 + (Player->getTileCheckRcPos().x + 14) -128;
		_pos.y = -sinf(_angle) * 50 + (Player->getTileCheckRcPos().y + 14) - 192;
	}
	else
	{
		_pos.x = cosf(_angle) * 50 + (Player->getTileCheckRcPos().x + 14) - 128;
		_pos.y = -sinf(_angle) * 50 + (Player->getTileCheckRcPos().y + 14) - 128;
	}
	_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth()/2, _pos.y + _img->getFrameHeight()/2, 200, 200);

	_reLoadCount = 0;
	_curCoolTime = 0;
	_index = _reLoadCount;
	_attackCount = 0;
	_isSkillImgRender = true;
	_img->SetFrameX(0);
	_imgCount = 0;
	_img->SetFrameX(0);
	_img2->SetFrameX(0);
	_img3->SetFrameX(0);
	_isRender[0] = true;
}
