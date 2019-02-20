#include "stdafx.h"
#include "enemyMgr.h"
#include "player.h"


enemyMgr::enemyMgr()
{
}


enemyMgr::~enemyMgr()
{
}

HRESULT enemyMgr::init()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->init();
		_vEnemy[i]->setPlayerAdress(_player);
		_vEnemy[i]->setMapAdress(&_vvMap);
	}
	// ------------------------------ A*--------------------------------------------------------------------------------------
	_aStar = new aStar;
	_aStar->setMap(&_vvMap);

	_aStarTime = 0;

	// ------------------------------ rotate Img--------------------------------------------------------------------------------------

	_rotateMaker = new rotateImgMaker;

	IMAGEMANAGER->addImage("smallSlash1", "images/enemy/effect/smallSlash1.bmp", 82, 82, true, 0xff00ff);
	IMAGEMANAGER->addImage("smallSlash2", "images/enemy/effect/smallSlash2.bmp", 82, 82, true, 0xff00ff);
	IMAGEMANAGER->addImage("smallSlash3", "images/enemy/effect/smallSlash3.bmp", 82, 82, true, 0xff00ff);


	_ghoulEff[0][0] = IMAGEMANAGER->findImage("smallSlash1");
	_ghoulEff[1][0] = IMAGEMANAGER->findImage("smallSlash2");
	_ghoulEff[2][0] = IMAGEMANAGER->findImage("smallSlash3");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 36; j++)
		{
			_ghoulEff[i][j] = _rotateMaker->MakeRotateImg(_ghoulEff[i][0], 0, 0, 82, 82, (PI2 / 36) * j, true, 0xff00ff);
		}
	}

	IMAGEMANAGER->addImage("largeSlash1", "images/enemy/effect/largeSlash1.bmp", 164, 164, true, 0xff00ff);
	IMAGEMANAGER->addImage("largeSlash2", "images/enemy/effect/largeSlash2.bmp", 164, 164, true, 0xff00ff);
	IMAGEMANAGER->addImage("largeSlash3", "images/enemy/effect/largeSlash3.bmp", 164, 164, true, 0xff00ff);

	_knightEff[0][0] = IMAGEMANAGER->findImage("largeSlash1");
	_knightEff[1][0] = IMAGEMANAGER->findImage("largeSlash2");
	_knightEff[2][0] = IMAGEMANAGER->findImage("largeSlash3");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 36; j++)
		{
			_knightEff[i][j] = _rotateMaker->MakeRotateImg(_knightEff[i][0], 0, 0, 164, 164, (PI2 / 36) * j, true, 0xff00ff);
		}
	}

	SAFE_DELETE(_rotateMaker);
	_rotateMaker = nullptr;

	return S_OK;
}

void enemyMgr::release()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
	
		_vEnemy[i]->release();
	}
}

void enemyMgr::update()
{
	RECT temp;
	for (int i = 0; i < _vEnemy.size();i++)
	{
		int mapPosX = _vEnemy[i]->getPos().x / 32;
		int mapPosY = _vEnemy[i]->getPos().y / 32;

		if (mapPosX < _player->getLeftBottomIndex().x - 30)continue;
		if (mapPosX > _player->getLeftBottomIndex().x + 30)continue;
		if (mapPosY < _player->getLeftBottomIndex().y - 18)continue;
		if (mapPosY > _player->getLeftBottomIndex().y + 18)continue;

		if (_vEnemy[i]->getState() == E_STATE::MOVE)
		{
			_aStarTime += TIMEMANAGER->getElapsedTime();
			if (_aStarTime > ASTAR_MAX_TIME)
			{
				//_myWay.clear();
	
				_vEnemy[i]->getPath()->clear();
	
				int e_posX = _vEnemy[i]->getPos().x / TOP_TILESIZE;
				int e_posY = _vEnemy[i]->getPos().y / TOP_TILESIZE;
	
				int p_posX = _vEnemy[i]->getPlayerPos().x / TOP_TILESIZE;
				int p_posY = _vEnemy[i]->getPlayerPos().y / TOP_TILESIZE;
	
				_aStar->pathFinder(PointMake(e_posX, e_posY), PointMake(p_posX, p_posY), PointMake(e_posX, e_posY), *(_vEnemy[i]->getPath()));
				_aStarTime = 0;
	
	
				//for (list<POINT>::iterator iter = _enemyMgr->getVEnemy()[0]->getPath()->begin();
				//	iter != _enemyMgr->getVEnemy()[0]->getPath()->end(); ++iter)
				//{
				//	_myWay.push_front(*iter);
				//}
			}
		}
		

		if (_vEnemy[i]->getState() == E_STATE::MOVE)
		{
			_vEnemy[i]->fixDirection();
			if (_vEnemy[i]->getAniDirection() == E_ANIDIRECTION::LEFT)
			{
				_vEnemy[i]->setAniDirection(E_ANIDIRECTION::LEFT);
				_vEnemy[i]->setState(E_STATE::MOVE);
				_vEnemy[i]->currentEnemyState();
				_vEnemy[i]->setIsAniOnce(true);
				_vEnemy[i]->startAni();
			}
			else if (_vEnemy[i]->getAniDirection() == E_ANIDIRECTION::RIGHT)
			{
				_vEnemy[i]->setAniDirection(E_ANIDIRECTION::RIGHT);
				_vEnemy[i]->setState(E_STATE::MOVE);
				_vEnemy[i]->currentEnemyState();
				_vEnemy[i]->setIsAniOnce(true);
				_vEnemy[i]->startAni();
			}
		}

		// 적 갯수만큼업데이트를 돌린다
		_vEnemy[i]->update();



		//맞았을때
		if (_vEnemy[i]->getState() != E_STATE::DEATH &&IntersectRect(&temp, &_vEnemy[i]->getCollision(), &_player->getCurSkills1()->getCollisionRc()))
		{
			_vEnemy[i]->setCurHP(_vEnemy[i]->getCurHP() - 1);
			_vEnemy[i]->setState(E_STATE::HIT);
			_vEnemy[i]->currentEnemyState();
			_vEnemy[i]->setIsAniOnce(true);
			_vEnemy[i]->setIsHit(true);
		}
		// 피가 0이되어서 죽을떄 애니메이션
		if (_vEnemy[i]->getCurHP() < 0)
		{
			_vEnemy[i]->setState(E_STATE::DEATH);
			_vEnemy[i]->currentEnemyState();
			_vEnemy[i]->setIsAniOnce(true);
			_vEnemy[i]->setIsDead(true);
		}
		//상태가 죽음이고 애니메이션 재생이 끝나면
		if (!_vEnemy[i]->getAni()->isPlay() && _vEnemy[i]->getState() == E_STATE::DEATH)
		{
			_vEnemy.erase(_vEnemy.begin() + i);
			break;
		}
		//나중에 절차적 문제가 생길수도 있음.

		int idX = _vEnemy[i]->getAtkIdX();
		int idY = _vEnemy[i]->getAtkIdY();

		if (_vEnemy[i]->getWhoIM() == GHOUL)
		{
			_vEnemy[i]->setAtkImg(_ghoulEff[idY][idX]);
		}
		else if (_vEnemy[i]->getWhoIM() == KNIGHT)
		{
			_vEnemy[i]->setAtkImg(_knightEff[idY][idX]);
		}
	}
}


void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		int mapPosX = _vEnemy[i]->getPos().x / 32;
		int mapPosY = _vEnemy[i]->getPos().y / 32;

		if (mapPosX < _player->getLeftBottomIndex().x - 30)continue;
		if (mapPosX > _player->getLeftBottomIndex().x + 30)continue;
		if (mapPosY < _player->getLeftBottomIndex().y - 18)continue;
		if (mapPosY > _player->getLeftBottomIndex().y + 18)continue;

		_vEnemy[i]->CamRender();
	}
}

void enemyMgr::makeEnemy(int makeNum, POINTFLOAT enemyPos_LT)
{
	enemy* enemy;
	switch (makeNum)
	{
		case UNIT_GHOUL:
			enemy = new enemy_Ghoul;
			enemy->init();
			enemy->setPlayerAdress(_player);
			enemy->setMapAdress(&_vvMap);
			enemy->setPos(enemyPos_LT);
			_vEnemy.push_back(enemy);
		break;
		case UNIT_KNIGHT:
			enemy = new enemy_Knight;
			enemy->init();
			enemy->setPlayerAdress(_player);
			enemy->setMapAdress(&_vvMap);
			enemy->setPos(enemyPos_LT);
			_vEnemy.push_back(enemy);
		break;
		case UNIT_LANCER:
			//추가시 수정
		break;
		case UNIT_ARCHER:
			//추가시 수정
		break;

	}
}
