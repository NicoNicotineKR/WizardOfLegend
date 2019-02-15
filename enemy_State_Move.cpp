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
	if (ATTACK_RANGE > getDistance(enemy->getPos().x, enemy->getPos().y - 70, enemy->getPlayerPos().x, enemy->getPlayerPos().y - 50))
	{
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();

		enemy->setAngle(getAngle(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y));
		enemy->setAtkPosX(enemy->getPos().x + cosf(enemy->getAngle()) * ATTACK_RANGE2);
		enemy->setAtkPosY((enemy->getPos().y - 70) + -sinf(enemy->getAngle()) * ATTACK_RANGE2); 
		enemy->setAtkRc(enemy->getAtkPos());

		float angle = enemy->getAngle() + (PI2 / 72);
		int frame = (int)(angle / (PI2 / 36));

		enemy->getAtkImg()->SetFrameX(frame);
	}
}

void enemy_State_Move::direction_right(enemy * enemy)
{
	if (ATTACK_RANGE > getDistance(enemy->getPos().x, enemy->getPos().y - 70, enemy->getPlayerPos().x, enemy->getPlayerPos().y - 50))
	{
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();

		enemy->setAngle(getAngle(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y));
		enemy->setAtkPosX(enemy->getPos().x + cosf(enemy->getAngle()) * ATTACK_RANGE2);
		enemy->setAtkPosY((enemy->getPos().y - 70) + -sinf(enemy->getAngle()) * ATTACK_RANGE2);
		enemy->setAtkRc(enemy->getAtkPos());

		float angle = enemy->getAngle() + (PI2 / 72);
		int frame = (int)(angle / (PI2 / 36));

		//	360 -> 10 36 2pi
		enemy->getAtkImg()->SetFrameX(frame);
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

		int x = enemy->getPos().x / TILE_SIZE;
		int y = enemy->getPos().y / TILE_SIZE;
		
		int posX = enemy->getPos().x;
		int posY = enemy->getPos().y;

	//	float tileX = (enemy->getPath()->begin()->x * TILE_SIZE);
	//	float tileY = (enemy->getPath()->begin()->y * TILE_SIZE);

		int tileX = enemy->getPath()->begin()->x;
		int tileY = enemy->getPath()->begin()->y;
		//x 
		if (tileX > x)
		{
			enemy->setVecX(enemy->getSpeed() * TIMEMANAGER->getElapsedTime());

			//enemy->setVecX(3);

		//	if (!(enemy->getMap()[y][(posX + enemy->getVec().x) / TILE_SIZE]->getTopTileAttr()))
		//	{
		//		enemy->setVecX(0);
		//	}

			//더하고 바로 비교하게했음
		//	if (tileX <= (posX + enemy->getVec().x) / TILE_SIZE)
		//	{
		//		enemy->setPosX(tileX);
		//	}
		}
		else if (tileX < x)
		{
			enemy->setVecX(-(enemy->getSpeed() * TIMEMANAGER->getElapsedTime()));

		//	enemy->setVecX(-3);

		//	if (!(enemy->getMap()[y][(posX + enemy->getVec().x) / TILE_SIZE]->getTopTileAttr()))
		//	{
		//		enemy->setVecX(0);
		//	}

			//더하고 바로 비교하게했음
		//	if (tileX >= (posX + enemy->getVec().x) / TILE_SIZE)
		//	{
		//		enemy->setPosX(tileX);
		//	}
		}

		//y
		if (tileY > y)
		{
			enemy->setVecY(enemy->getSpeed() * TIMEMANAGER->getElapsedTime());

		//	enemy->setVecY(3);

			//if (!(enemy->getMap()[(posY + enemy->getVec().y) / TILE_SIZE][x]->getTopTileAttr()))
			//{
			//	enemy->setVecY(0);
			//}

			//더하고 바로 비교하게했음
		//	if (tileY < (y - SHAVE_NUM) + enemy->getVec().y)
		//	{
		//		enemy->setPosY(tileY);
		//	}
		}
		else if (tileY < y)
		{
			enemy->setVecY(-(enemy->getSpeed() * TIMEMANAGER->getElapsedTime()));
			
		//	enemy->setVecY(-3);

			//if (!(enemy->getMap()[(posY + enemy->getVec().y) / TILE_SIZE][x]->getTopTileAttr()))
			//{
			//	enemy->setVecY(0);
			//}

			//더하고 바로 비교하게했음
		//	if (tileY > (y + SHAVE_NUM) + enemy->getVec().y)
		//	{
		//		enemy->setPosY(tileY);
		//	}
		}

	//	if (!(enemy->getMap()[y][(int)((posX + enemy->getVec().x) / TILE_SIZE)]->getIsAvailMove()))
	//	{
	//		enemy->setVecX(0);
	//	}
	//	if (!(enemy->getMap()[(int)((posY + enemy->getVec().y) / TILE_SIZE)][x]->getIsAvailMove()))
	//	{
	//		enemy->setVecY(0);
	//	}

		if (x == tileX && y == tileY)
		{
			enemy->getPath()->pop_front();
		}
	}
}
