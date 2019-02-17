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
	//일단 기사 한마리만 밀어놓고
	enemy* knight = new enemy_Knight;
	_vEnemy.push_back(knight);

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->init();
		_vEnemy[i]->setPlayerAdress(_player);
		_vEnemy[i]->setMapAdress(_vvMap);
	}

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
	for (int i = 0; i < _vEnemy.size();)
	{
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
		}
		else i++;

		//나중에 절차적 문제가 생길수도 있음.
	}
}


void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
			_vEnemy[i]->render();
	}
}
