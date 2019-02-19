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
	if (enemy->getAtkRange() > getDistance(enemy->getPos().x, enemy->getPos().y - 70, enemy->getPlayerPos().x, enemy->getPlayerPos().y - 50) 
		&& (!enemy->getIsHit() && !enemy->getIsDead()))
	{
		enemy->setAniDirection(E_ANIDIRECTION::LEFT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();

		enemy->setAngle(getAngle(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y));
		enemy->setAtkPosX(enemy->getPos().x + cosf(enemy->getAngle()) * enemy->getWeaponRange());
		enemy->setAtkPosY((enemy->getPos().y - enemy->getEffectShavePosY()) + -sinf(enemy->getAngle()) * enemy->getWeaponRange());

		float angle = enemy->getAngle() + (PI2 / 72);
		int frame = (int)(angle / (PI2 / 36));

		//찾았다... 내 3시간짜리 도둑..
		if (frame == 36)
		{
			frame = 0;
		}
		//어휴 미친럼
		enemy->setAtkIdX(frame);
	}
}

void enemy_State_Move::direction_right(enemy * enemy)
{
	if (enemy->getAtkRange() > getDistance(enemy->getPos().x, enemy->getPos().y - 70, enemy->getPlayerPos().x, enemy->getPlayerPos().y - 50) 
		&& (!enemy->getIsHit() && !enemy->getIsDead()))
	{
		enemy->setAniDirection(E_ANIDIRECTION::RIGHT);
		enemy->setState(E_STATE::CHARGE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();

		enemy->setAngle(getAngle(enemy->getPos().x, enemy->getPos().y, enemy->getPlayerPos().x, enemy->getPlayerPos().y));
		enemy->setAtkPosX(enemy->getPos().x + cosf(enemy->getAngle()) * enemy->getWeaponRange());
		enemy->setAtkPosY((enemy->getPos().y - enemy->getEffectShavePosY()) + -sinf(enemy->getAngle()) * enemy->getWeaponRange());

		float angle = enemy->getAngle() + (PI / 36);
		int frame = (int)(angle / (PI / 18));

		if (frame == 36)
		{
			frame = 0;
		}
		//	360 -> 10 36 2pi
		enemy->setAtkIdX(frame);
	}
}

void enemy_State_Move::update(enemy * enemy)
{
	E_ANIDIRECTION save = enemy->getAniDirection();
	if (enemy->getPath()->size() != 0)
	{
		enemy->moveDirection();
	}
	else if (enemy->getPath()->size() == 0)
	{
		enemy->fixDirection();
	}
	if (save != enemy->getAniDirection())
	{
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
	enemy->defaultAtkRc();

	// 에이스타를 활용해 플레이어를 쫓아가즈아
	if (enemy->getPath()->size() > 0)
	{


		int x = enemy->getPos().x / TILE_SIZE;
		int y = enemy->getPos().y / TILE_SIZE;
		//int x = (enemy->getPos().x * TILE_SIZE) + (TILE_SIZE / 2);
		//int y = (enemy->getPos().y * TILE_SIZE) + (TILE_SIZE / 2);
		
		int posX = enemy->getPos().x;
		int posY = enemy->getPos().y;

		int tileX = enemy->getPath()->begin()->x;
		int tileY = enemy->getPath()->begin()->y;
	//	float tileX = (enemy->getPath()->begin()->x * TILE_SIZE);
	//	float tileY = (enemy->getPath()->begin()->y * TILE_SIZE);

		//x 
		if (tileX > x)
		{
			enemy->setVecX(enemy->getSpeed() * TIMEMANAGER->getElapsedTime());

			//갈곳이 구멍이면 벡터가 0
			if ((*enemy->getMap())[(tileX + enemy->getVec().x) / TOP_TILESIZE][tileY / TOP_TILESIZE]->getTopTileAttr() == TILE_HOLE)
			{
				enemy->setVecX(0);
			}

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

			//갈곳이 구멍이면 벡터가 0
			if ((*enemy->getMap())[(tileX + enemy->getVec().x) / TOP_TILESIZE][tileY / TOP_TILESIZE]->getTopTileAttr() == TILE_HOLE)
			{
				enemy->setVecX(0);
			}

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

			//갈곳이 구멍이면 벡터가 0
			if ((*enemy->getMap())[tileX / TOP_TILESIZE][(tileY + enemy->getVec().y) / TOP_TILESIZE]->getTopTileAttr() == TILE_HOLE)
			{
				enemy->setVecY(0);
			}

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
			
			//갈곳이 구멍이면 벡터가 0
			if ((*enemy->getMap())[tileX / TOP_TILESIZE][(tileY + enemy->getVec().y) / TOP_TILESIZE]->getTopTileAttr() == TILE_HOLE)
			{
				enemy->setVecY(0);
			}

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
