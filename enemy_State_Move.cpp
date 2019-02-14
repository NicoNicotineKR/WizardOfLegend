#include "stdafx.h"
#include "enemy_State_Move.h"


enemy_State_Move::enemy_State_Move()
{
}


enemy_State_Move::~enemy_State_Move()
{
}

void enemy_State_Move::direction_Left(enemy * enemy)
{
	if (ATTACK_RANGE > getDistance(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y))
	{
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Move::direction_right(enemy * enemy)
{
	if (ATTACK_RANGE > getDistance(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y))
	{
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Move::update(enemy * enemy)
{
	E_ANIDIRECTION save = enemy->getAniDirection();
	enemy->fixDirection();
	if (save != enemy->getAniDirection())
	{
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}


	// 에이스타를 활용해 플레이어를 쫓아가즈아
	if (enemy->getPath()->size() > 0)
	{
		//int x = (enemy->getPos().x * TILE_SIZE) + (TILE_SIZE / 2);
		//int y = (enemy->getPos().y * TILE_SIZE) + (TILE_SIZE / 2);

		float x = enemy->getPos().x;
		float y = enemy->getPos().y;
		
		float tileX = (enemy->getPath()->begin()->x * TILE_SIZE);
		float tileY = (enemy->getPath()->begin()->y * TILE_SIZE);
		//x 
		if (tileX > x)
		{
			enemy->setVecX(enemy->getSpeed() * TIMEMANAGER->getElapsedTime());

			//더하고 바로 비교하게했음
			if (tileX < x + enemy->getVec().x)
			{
				enemy->setPosX(tileX);
			}
		}
		else if (tileX < x)
		{
			enemy->setVecX(-(enemy->getSpeed() * TIMEMANAGER->getElapsedTime()));

			//더하고 바로 비교하게했음
			if (tileX > x + enemy->getVec().x)
			{
				enemy->setPosX(tileX);
			}
		}

		//y
		if (tileY > y)
		{
			enemy->setVecY(enemy->getSpeed() * TIMEMANAGER->getElapsedTime());

			//더하고 바로 비교하게했음
			if (tileY < y + enemy->getVec().y)
			{
				enemy->setPosY(tileY);
			}
		}
		else if (tileY < y)
		{
			enemy->setVecY(-(enemy->getSpeed() * TIMEMANAGER->getElapsedTime()));

			//더하고 바로 비교하게했음
			if (tileY > y + enemy->getVec().y)
			{
				enemy->setPosY(tileY);
			}
		}

		if (tileX == x && tileY == y)
		{
			enemy->getPath()->pop_front();
		}
	}
}
