#include "stdafx.h"
#include "stoneShot.h"

HRESULT stoneShot::init(player * Player)
{
	_name = "stoneShot";
	for (int i = 0; i < 2; ++i)
	{
		_stoneShotImg[i] = new image;
		_stoneShotImg[i]->init("images/player/stoneShot.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	}
	_stoneShotImg[2] = new image;
	_stoneShotImg[2]->init("images/player/stoneShotLast.bmp", 512, 128, 4, 1, true, RGB(255, 0, 255));

	_vvMap = Player->getVVMapMemoryAddress();
	_totalCoolTime = 1;
	_maxReLoad = 3;
	_imgCount = 0;
	_reLoadCount = 0;
	_curCoolTime = 0;
	_isSkill = false;
	_isSkillImgRender = false;
	_speed = 10.0f;
	_range = 200.0f;
	for (int i = 0; i < 3; ++i)
	{
		_stoneShotPos[i].x = 0;
		_stoneShotPos[i].y = 0;
	}
	return S_OK;
}

void stoneShot::release(player * Player)
{
}

void stoneShot::update(player * Player)
{

	if (_isSkillImgRender)
	{
		_imgCount += TIMEMANAGER->getElapsedTime();
		if (_imgCount > 0.05f)
		{
			_imgCount = 0;
			for (int i = 0; i < 3; ++i)
			{
				if (!_isRender[i]) continue;
				if (_stoneShotImg[i]->getMaxFrameX() <= _stoneShotImg[i]->getFrameX())
				{
					_stoneShotImg[i]->SetFrameX(0);
				}
				_stoneShotImg[i]->SetFrameX(_stoneShotImg[i]->getFrameX() + 1);
			}
		}
	}

	if (_isSkill)
	{
		_attackCount += TIMEMANAGER->getElapsedTime();
		if (_maxReLoad > _reLoadCount)
		{

			if (_index != _reLoadCount)
			{
				_index = _reLoadCount;
				_attackCount = 0;
				//_angle = Player->getPlayerAngle();

				_isRender[_reLoadCount] = true;
				_stoneShotAngle[_reLoadCount] = Player->getPlayerAngle();
				if (Player->getAniDirection() != ANIDIRECTION::FRONT)
				{
					_stoneShotPos[_reLoadCount].x = cosf(_stoneShotAngle[_reLoadCount]) * 50 + (Player->getTileCheckRcPos().x + 14) - (_stoneShotImg[_reLoadCount]->getFrameWidth()/2);
					_stoneShotPos[_reLoadCount].y = -sinf(_stoneShotAngle[_reLoadCount]) * 50 + (Player->getTileCheckRcPos().y + 14) - (_stoneShotImg[_reLoadCount]->getFrameHeight() / 2);
				}
				else
				{
					_stoneShotPos[_reLoadCount].x = cosf(_stoneShotAngle[_reLoadCount]) * 50 + (Player->getTileCheckRcPos().x + 14) - (_stoneShotImg[_reLoadCount]->getFrameWidth() / 2);
					_stoneShotPos[_reLoadCount].y = -sinf(_stoneShotAngle[_reLoadCount]) * 50 + (Player->getTileCheckRcPos().y + 14) - (_stoneShotImg[_reLoadCount]->getFrameHeight() / 2);

				}
				
				_firePos[_reLoadCount] = _stoneShotPos[_reLoadCount];

			}
	

			if (_attackCount > 0.5f)
			{
				_attackCount = 0;
				_reLoadCount = 0;
				Player->setState(STATE::IDLE);
				Player->currentPlayerState();
				Player->startAni();
				_isSkill = false;
			}
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (!_isRender[i]) continue;
		_stoneShotPos[i].x += cosf(_stoneShotAngle[i]) * (_speed + TIMEMANAGER->getElapsedTime());
		_stoneShotPos[i].y += -sinf(_stoneShotAngle[i]) * (_speed + TIMEMANAGER->getElapsedTime());
		_stoneShotRc[i] = RectMakeCenter(_stoneShotPos[i].x + _stoneShotImg[i]->getFrameWidth() / 2,
			_stoneShotPos[i].y + _stoneShotImg[i]->getFrameHeight() / 2, _stoneShotImg[i]->getFrameWidth(), _stoneShotImg[i]->getFrameHeight());
		if (_range * _range < getDistance(_firePos[i].x, _firePos[i].y, _stoneShotPos[i].x, _stoneShotPos[i].y) ||
			!(*_vvMap)[(_stoneShotPos[i].y + _stoneShotImg[i]->getFrameHeight() / 2) / 32][(_stoneShotPos[i].x+ _stoneShotImg[i]->getFrameWidth()/2)/ 32]->getIsAvailMove())
		{
			_isRender[i] = false;
			_stoneShotRc[i] = RectMake(-100, -100, 64, 64);
		}
	
	}
}

void stoneShot::render(player * Player)
{
	if (_isSkillImgRender)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (!_isRender[i])continue;
			_stoneShotImg[i]->frameRender(Player->getPlayerMemDC(), _stoneShotPos[i].x - CAMERA2D->getCamPosX(), _stoneShotPos[i].y-CAMERA2D->getCamPosY());

		}
	}

}

void stoneShot::skillPosSet(player * Player)
{
	_reLoadCount = 0;
	_curCoolTime = 0;
	_index = -1;
	_attackCount = 0;
	_isSkillImgRender = true;
	_imgCount = 0;
	for (int i = 0; i < 3; ++i)
	{
		_stoneShotImg[i]->SetFrameX(0);
		_stoneShotImg[i]->SetFrameY(0);
	}
	//_isRender[0] = true;
}

void stoneShot::destroySkill(int i)
{
	_isRender[i] = false;
	_stoneShotRc[i] = RectMake(-100, -100, 64, 64);
}
