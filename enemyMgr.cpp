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
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->update();
	}
}

void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->render();
	}
}
