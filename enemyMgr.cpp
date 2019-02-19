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
			break;
		}
		//���߿� ������ ������ ������� ����.
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
			//�߰��� ����
		break;
		case UNIT_ARCHER:
			//�߰��� ����
		break;

	}
}
