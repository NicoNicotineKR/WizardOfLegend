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
	enemy* knight = new enemy_Ghoul;
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
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
		if (IntersectRect(&temp, &_vEnemy[i]->getCollision(), &_player->getCurSkills1()->getCollisionRc()))
		{
			_vEnemy[i]->setCurHP(_vEnemy[i]->getCurHP() - 1);
		}
	}
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (_vEnemy[i]->getCurHP() < 0)
		{
			_vEnemy.erase(_vEnemy.begin() + i);
			break;
		}
	}
}


void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
			_vEnemy[i]->render();
	}
}
