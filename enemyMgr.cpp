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
//	enemy* knight = new enemy_Knight;
//	_vEnemy.push_back(knight);


	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->init();
		_vEnemy[i]->setPlayerAdress(_player);
		_vEnemy[i]->setMapAdress(&_vvMap);
	}


	_vvMap.size();
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

		if (mapPosX < _player->getLeftBottomIndex().x - 10)continue;
		if (mapPosX > _player->getLeftBottomIndex().x + 10)continue;
		if (mapPosY < _player->getLeftBottomIndex().y - 10)continue;
		if (mapPosY > _player->getLeftBottomIndex().y + 10)continue;

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
	}
}


void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		int mapPosX = _vEnemy[i]->getPos().x / 32;
		int mapPosY = _vEnemy[i]->getPos().y / 32;

		if (mapPosX < _player->getLeftBottomIndex().x - 10)continue;
		if (mapPosX > _player->getLeftBottomIndex().x + 10)continue;
		if (mapPosY < _player->getLeftBottomIndex().y - 10)continue;
		if (mapPosY > _player->getLeftBottomIndex().y + 10)continue;

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
