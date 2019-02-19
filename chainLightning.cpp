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
	_name = "thunderingChain";
	_vvMap = Player->getVVMapMemoryAddress();
	_img = IMAGEMANAGER->findImage("lightningChain");
	_thunderFloorImg = IMAGEMANAGER->findImage("thunderFloor");
	_totalCoolTime = 5.0f;
	_reLoadCount = _maxReLoad;
	_maxReLoad = 1;
	_imgCount = 0;
	_attackCount = 0;
	_img->SetFrameX(0);
	_img->SetFrameY(0);
	_thunderFloorImg->SetFrameX(0);
	_thunderFloorImg->SetFrameY(0);
	_isSkill = false;
	return S_OK;
}

void chainLightning::release(player* Player)
{
}

void chainLightning::update(player* Player)
{


	if (_curCoolTime < _totalCoolTime)
	{
		_curCoolTime += TIMEMANAGER->getElapsedTime();
		_imgCount += TIMEMANAGER->getElapsedTime();
		if (10 > _attackCount)
		{

			if ((*_vvMap)[_pos.y / 32][_pos.x / 32]->getIsAvailMove())
			{
			
				if (_imgCount > 0.05f)
				{
					_imgCount = 0;
					if (_thunderFloorImg->getMaxFrameX() == _thunderFloorImg->getFrameX())
					{
						_thunderFloorImg->SetFrameX(0);
					}
					if (_img->getMaxFrameX() == _img->getFrameX())
					{
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
						_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth() / 2 - 135 / 2, 
							_pos.y + _img->getFrameHeight() - 25 - 900, 50, 50);

						_attackCount++;

					}
					_img->SetFrameX(_img->getFrameX() + 1);
					_thunderFloorImg->SetFrameX(_thunderFloorImg->getFrameX()+1);
				}
			}
			else
			{
				_attackCount = 10;
			}
		}
	}
	else if (_isSkill)
	{
		_isSkill = false;
		_reLoadCount = _maxReLoad;
	}


}

void chainLightning::render(player* Player)
{
	if (10 > _attackCount)
	{
		if ((*_vvMap)[_pos.y / 32][_pos.x / 32]->getIsAvailMove())
		{
			_img->frameRender(Player->getPlayerMemDC(), _pos.x - (135 / 2) - CAMERA2D->getCamPosX(), _pos.y - 900 - CAMERA2D->getCamPosY());
			_thunderFloorImg->frameRender(Player->getPlayerMemDC(), _pos.x-_thunderFloorImg->getFrameWidth()/2 - CAMERA2D->getCamPosX(),
				_pos.y - _thunderFloorImg->getFrameHeight() / 2 - CAMERA2D->getCamPosY());
		}
	}
}

void chainLightning::skillPosSet(player* Player)
{
	_angle = Player->getPlayerAngle();
	_pos.x = cosf(_angle) * 100 + (Player->getTileCheckRcPos().x + 14);
	_pos.y = -sinf(_angle) * 100 + (Player->getTileCheckRcPos().y + 14);
	_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth()/2 - 135 / 2, _pos.y + _img->getFrameHeight() - 25 - 900, 50, 50);
	_curCoolTime = 0;
	_attackCount = 0;
}

void chainLightning::destroySkill(int i)
{
}
