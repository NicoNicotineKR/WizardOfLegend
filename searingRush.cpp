#include "stdafx.h"
#include "searingRush.h"


searingRush::searingRush()
{
}


searingRush::~searingRush()
{

}

HRESULT searingRush::init(player * Player)
{
	_name = "searingRush";
	_vvMap = Player->getVVMapMemoryAddress();
	//_img = IMAGEMANAGER->findImage("searingRush");
	for (int i = 0; i < 5; ++i)
	{
		_flameImg[i] = new image;
		_flameImg[i]->init("images/player/searingRush.bmp", 4096, 128, 32, 1, true, RGB(255, 0, 255));
		_flameImg[i]->SetFrameX(0);
		_flameImg[i]->SetFrameY(0);
	}
	_totalCoolTime = 3.0f;
	_curCoolTime = 0;
	_maxReLoad = 1;
	_reLoadCount = _maxReLoad;
	_imgCount = 0;
	_attackCount = 0;

	_isSkill = false;

	//	Àç¸¸Ãß°¡ -> enemyMgr ÁÖ¼Ò ³Ö¾îÁÜ : ¸÷¿¡°Ô µ¥¹ÌÁö ÁÜ
	_em = Player->getEnemyMgrAddress();
	return S_OK;
}

void searingRush::release(player * Player)
{
}

void searingRush::update(player * Player)
{
	
	if (_totalCoolTime > _curCoolTime)
	{
		_curCoolTime += TIMEMANAGER->getElapsedTime();
		if (_isSkill)
		{
			_imgCount += TIMEMANAGER->getElapsedTime();
			if (_imgCount > 0.05f)
			{
				_imgCount = 0;

				for (int i = 0; i < 5; ++i)
				{
					if (_flameImg[i]->getFrameX() == _flameImg[i]->getMaxFrameX()) continue;
					if (_attackCount < i)continue;
					_flameImg[i]->SetFrameX(_flameImg[i]->getFrameX() + 1);
				}
				if (_attackCount < 4)
				{
					_attackCount++;
					_flamePos[(int)_attackCount].x = Player->getPlayerTileCheckRc().right -
						(Player->getPlayerTileCheckRc().right - Player->getPlayerTileCheckRc().left);
					_flamePos[(int)_attackCount].y = Player->getPlayerTileCheckRc().bottom- 
						_flameImg[(int)_attackCount]->getFrameHeight();
					_flameRc[(int)_attackCount] = RectMakeCenter(_flamePos[(int)_attackCount].x, _flamePos[(int)_attackCount].y+78, 50, 50);


				}
			}
		}

	}
	else
	{
		_isSkill = false;
	}
}

void searingRush::render(player* Player)
{
	if (_isSkill)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (_flameImg[i]->getFrameX() == _flameImg[i]->getMaxFrameX()) continue;
			if (_attackCount < i) continue;
			_flameImg[i]->frameRender(Player->getPlayerMemDC(), _flamePos[i].x - _flameImg[i]->getFrameWidth()/2 +20 - CAMERA2D->getCamPosX(),
				_flamePos[i].y - CAMERA2D->getCamPosY());
		}
	}
}

void searingRush::skillPosSet(player * Player)
{

	//_pos.x = Player->getTileCheckRcPos().x;
	//_pos.y = Player->getTileCheckRcPos().y;
	//_flamePos[0].x = _pos.x;
	//_flamePos[0].y = _pos.y;
	_imgCount = 0;
	_attackCount = -1;
	_curCoolTime = 0;
	_reLoadCount = 1;
	for (int i = 0; i < 5; ++i)
	{
		_flameImg[i]->SetFrameX(0);
		_flameImg[i]->SetFrameY(0);
	}
}

void searingRush::destroySkill(int i)
{
}
