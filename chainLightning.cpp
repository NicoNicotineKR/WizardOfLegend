#include "stdafx.h"
#include "chainLightning.h"


chainLightning::chainLightning()
{
}

chainLightning::~chainLightning()
{
}

HRESULT chainLightning::init(player* Player)
{
	_name = "chainLightgning";
	_vvMap = Player->getVVMapMemoryAddress();
	_img = IMAGEMANAGER->findImage("lightningChain");
	_angle = Player->getPlayerAngle();
	_pos.x = cosf(_angle) *  100 + (Player->getTileCheckRcPos().x+14);
	_pos.y = -sinf(_angle) * 100 + (Player->getTileCheckRcPos().y+14);
	_imgCount = 0;
	_attackCount = 0;
	_img->SetFrameX(0);
	_img->SetFrameY(0);
	return S_OK;
}

void chainLightning::release(player* Player)
{
}

void chainLightning::update(player* Player)
{
	if ((*_vvMap)[_pos.y / 32][_pos.x / 32]->getIsAvailMove())
	{
		_imgCount += TIMEMANAGER->getElapsedTime();
		if (_imgCount > 0.05f)
		{
			_imgCount = 0;
			if (_img->getMaxFrameX() == _img->getFrameX())
			{
				if (_attackCount > 4)
				{
					Player->setIsUsingSkill(false);
				}
				_img->SetFrameX(0);
				if (_img->getFrameY() == 0)
				{
					_img->SetFrameY(1);
				}
				else
				{
					_img->SetFrameY(0);
				}
				_pos.x = cosf(_angle) * 30 + _pos.x;
				_pos.y = -sinf(_angle) * 30 + _pos.y;
				_attackCount++;

			}
			_img->SetFrameX(_img->getFrameX() + 1);
		}
	}
	else
	{
		Player->setIsUsingSkill(false);
	}
}

void chainLightning::render(player* Player)
{
	if ((*_vvMap)[_pos.y / 32][_pos.x / 32]->getIsAvailMove())
	{
		_img->frameRender(Player->getPlayerMemDC(), _pos.x - 135 / 2, _pos.y - 900);

	}
	char str[128];
	sprintf_s(str, "%lf , _angle", _angle * (180 / PI), strlen(str));
	TextOut(Player->getPlayerMemDC(), 100, 100, str, strlen(str));
}
