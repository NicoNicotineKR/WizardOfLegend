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

	//	재만추가 -> enemyMgr 주소 넣어줌 : 몹에게 데미지 줌
	_em = Player->getEnemyMgrAddress();
	_boss = Player->getBossAdresss();
	for (int i = 0; i < 5; i++) {
		_isHit[5] = false;
	}
	
	return S_OK;
}

void searingRush::release(player * Player)
{
}

void searingRush::update(player * Player)
{
	for (int i = 0; i < 5; i++) {
		if (!_isHit[i]) {
			_flameRc[i] = RectMakeCenter(_flamePos[i].x, _flamePos[i].y + 78, 50, 50);
			if (_em != nullptr)
			{
				_em->RcCollideBySkillFunc(&_flameRc[i], ATK_DMG, &_isHit[i]);
			}
			if (_boss != nullptr)
			{
				_boss->RcCollideBySkillFunc(&_flameRc[i], ATK_DMG, &_isHit[i]);
			}
		}
	}
	
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
					if (_flameImg[i]->getFrameX() == _flameImg[i]->getMaxFrameX())
					{
						_flamePos[i] = { -500, -500 };
						_flameRc[i] = { -500,-500,-500 ,-500 };
						continue;
					}
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
					//_flameRc[(int)_attackCount] = RectMakeCenter(_flamePos[(int)_attackCount].x, _flamePos[(int)_attackCount].y+78, 50, 50);

					//	재만 추가 -- 충돌렉트 업데이트했으면, 맞았는지 검사해야게찌?
					//if (!_isHit[(int)_attackCount]) {
					//	_flameRc[(int)_attackCount] = RectMakeCenter(_flamePos[(int)_attackCount].x, _flamePos[(int)_attackCount].y + 78, 50, 50);
					//	_em->RcCollideBySkillFunc(&_flameRc[(int)_attackCount], ATK_DMG, &_isHit[(int)_attackCount]);
					//}


				}
			}
		}

	}
	else
	{
		_isSkill = false;
		_reLoadCount = _maxReLoad;
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

			//RECT tmprc = _flameRc[i];
			//tmprc.left -= CAMERA2D->getCamPosX();
			//tmprc.right -= CAMERA2D->getCamPosX();
			//tmprc.top -= CAMERA2D->getCamPosY();
			//tmprc.bottom -= CAMERA2D->getCamPosY();
			//Rectangle(Player->getMemDC(), tmprc);
		}
		
		
	}
//	for (int i = 0; i < _em->getVEnemy().size(); i++) {
//
//		RECT tmprc = _em->getVEnemy()[i]->getCollision();
//		tmprc.left -= CAMERA2D->getCamPosX();
//		tmprc.right -= CAMERA2D->getCamPosX();
//		tmprc.top -= CAMERA2D->getCamPosY();
//		tmprc.bottom -= CAMERA2D->getCamPosY();
//		Rectangle(Player->getMemDC(), tmprc);
//	}
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

	//	재만추가
	for (int i = 0; i < 5; i++) {
		_isHit[i] = false;
	}
	
}

void searingRush::destroySkill(int i)
{
}
