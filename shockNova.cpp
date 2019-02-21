#include "stdafx.h"
#include "shockNova.h"


shockNova::shockNova()
{
}


shockNova::~shockNova()
{
}

HRESULT shockNova::init(player * Player)
{
	_name = "shockNova";
	_vvMap = Player->getVVMapMemoryAddress();
	_img = IMAGEMANAGER->findImage("shockNova");
	_thunderSharftImg = IMAGEMANAGER->findImage("lightningChain");
	_totalCoolTime = 5.0f;
	_curCoolTime = 0;
	_maxReLoad = 1;
	_reLoadCount = _maxReLoad;
	_imgCount = 0;
	_attackCount = 0;
	_img->SetFrameX(0);
	_img->SetFrameY(0);
	_thunderSharftImg->SetFrameX(0);
	_thunderSharftImg->SetFrameY(0);
	_isSkill = false;

	//	재만추가 -> enemyMgr 주소 넣어줌 : 몹에게 데미지 줌
	_em = Player->getEnemyMgrAddress();
	_boss = Player->getBossAdresss();
	_isHit = false;
	return S_OK;
}

void shockNova::release(player * Player)
{
}

void shockNova::update(player * Player)
{
	if (_curCoolTime < _totalCoolTime)
	{
		_curCoolTime += TIMEMANAGER->getElapsedTime();
		_imgCount += TIMEMANAGER->getElapsedTime();
		if (6 > _attackCount)
		{
			//	재만추가
			if (_em != nullptr)
			{
				_em->DistanceBySkillFunc(_pos, ATK_RANGE, ATK_DMG, &_isHit);
			}
			if (_boss != nullptr)
			{
				_boss->DistanceBySkillFunc(_pos, ATK_RANGE, ATK_DMG, &_isHit);
			}


			if (_imgCount > 0.05f)
			{
				_imgCount = 0;
				if (_thunderSharftImg->getMaxFrameX() == _thunderSharftImg->getFrameX())
				{
					_thunderSharftImg->SetFrameX(0);
					_attackCount++;
					_isHit = false;

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
					_attackCount++;

				}

				if (_attackCount < 1)
				{

					_thunderSharftImg->SetFrameX(_thunderSharftImg->getFrameX() + 1);

				}
				else
				{
					_img->SetFrameX(_img->getFrameX() + 1);
				}
			}
		}
		else
		{
			SOUNDMANAGER->stop("chainLightning");
		}
	}
	else if (_isSkill)
	{
		_isSkill = false;
		_reLoadCount = _maxReLoad;
	}
}

void shockNova::render(player * Player)
{
	if (_isSkill)
	{
		if (_attackCount < 1)
		{
			_thunderSharftImg->frameRender(Player->getPlayerMemDC(), _pos.x - 50 - CAMERA2D->getCamPosX(), _pos.y - 900 - CAMERA2D->getCamPosY());
		}
		else if (_attackCount < 6)
		{
			_img->frameRender(Player->getPlayerMemDC(), _pos.x - _img->getFrameWidth() / 2 - CAMERA2D->getCamPosX(), _pos.y - _img->getFrameHeight() / 2 - CAMERA2D->getCamPosY());
		}
	}
}

void shockNova::skillPosSet(player * Player)
{
	SOUNDMANAGER->play("chainLightning", OPTIONMANAGER->getSoundEffectVolume());
	_pos.x = Player->getPlayerTileCheckRc().right - (Player->getPlayerTileCheckRc().right - Player->getPlayerTileCheckRc().left);
	_pos.y = Player->getPlayerTileCheckRc().bottom - (Player->getPlayerTileCheckRc().bottom - Player->getPlayerTileCheckRc().top);
	//_collisionRc = RectMakeCenter(_pos.x + _img->getFrameWidth() / 2, _pos.y + _img->getFrameHeight()/2, 50, 50);
	_reLoadCount = 0;
	_curCoolTime = 0;
	_attackCount = 0;
	_isHit = false;

}

void shockNova::destroySkill(int i)
{
}
