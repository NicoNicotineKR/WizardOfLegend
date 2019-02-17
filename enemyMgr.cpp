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
	//�ϴ� ��� �Ѹ����� �о����
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
		// �� ������ŭ������Ʈ�� ������
		_vEnemy[i]->update();

		//�¾�����
		if (_vEnemy[i]->getState() != E_STATE::DEATH &&IntersectRect(&temp, &_vEnemy[i]->getCollision(), &_player->getCurSkills1()->getCollisionRc()))
		{
			_vEnemy[i]->setCurHP(_vEnemy[i]->getCurHP() - 1);
			_vEnemy[i]->setState(E_STATE::HIT);
			_vEnemy[i]->currentEnemyState();
			_vEnemy[i]->setIsAniOnce(true);
			_vEnemy[i]->setIsHit(true);
		}
		// �ǰ� 0�̵Ǿ ������ �ִϸ��̼�
		if (_vEnemy[i]->getCurHP() < 0)
		{
			_vEnemy[i]->setState(E_STATE::DEATH);
			_vEnemy[i]->currentEnemyState();
			_vEnemy[i]->setIsAniOnce(true);
			_vEnemy[i]->setIsDead(true);
			
		}
		//���°� �����̰� �ִϸ��̼� ����� ������
		if (!_vEnemy[i]->getAni()->isPlay() && _vEnemy[i]->getState() == E_STATE::DEATH)
		{
			_vEnemy.erase(_vEnemy.begin() + i);
		}
		else i++;

		//���߿� ������ ������ ������� ����.
	}
}


void enemyMgr::render()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
			_vEnemy[i]->render();
	}
}
