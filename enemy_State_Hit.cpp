#include "stdafx.h"
#include "enemy_State_Hit.h"


enemy_State_Hit::enemy_State_Hit()
{
}


enemy_State_Hit::~enemy_State_Hit()
{
}

void enemy_State_Hit::direction_Left(enemy * enemy)
{
	if (!enemy->getAni()->isPlay() && enemy->getState() != E_STATE::DEATH && enemy->getCurHP() > 0)
	{
		enemy->fixDirection();
		enemy->setState(E_STATE::MOVE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Hit::direction_right(enemy * enemy)
{
	if (!enemy->getAni()->isPlay() && enemy->getState() != E_STATE::DEATH && enemy->getCurHP() > 0)
	{
		enemy->fixDirection();
		enemy->setState(E_STATE::MOVE);
		enemy->currentEnemyState();
		enemy->setIsAniOnce(true);
		enemy->startAni();
	}
}

void enemy_State_Hit::update(enemy * enemy)
{
	if (enemy->getPath()->size() > 0)
	{
		enemy->getPath()->clear();
	}
	float vecX = cosf(enemy->getHitAngle() - PI) * 0.7f;
	float vecY = -sinf(enemy->getHitAngle() - PI)* 0.7f;

	enemy->defaultAtkRc();
	enemy->setVecX(vecX);
	enemy->setVecY(vecY);

	int tileX_Pos = enemy->getPos().x;
	int tileY_Pos = enemy->getPos().y;
	
	int x = tileX_Pos / TOP_TILESIZE; 
	int y = tileY_Pos / TOP_TILESIZE;
	int vx = (tileX_Pos + vecX) / TOP_TILESIZE;
	int vy = (tileY_Pos + vecY) / TOP_TILESIZE;
	//벽이면 안밀리게 벡터 0으로
	if (tileY_Pos / TOP_TILESIZE > (*enemy->getMap()).size() - 1 || (tileY_Pos + vecY) / TOP_TILESIZE > (*enemy->getMap()).size() - 1
		|| tileY_Pos / TOP_TILESIZE < 0 || (tileY_Pos + vecY) / TOP_TILESIZE < 0)
	{
		return;
	}
	else if (tileX_Pos / TOP_TILESIZE > (*enemy->getMap())[0].size() -1  || (tileX_Pos + vecX) / TOP_TILESIZE > (*enemy->getMap())[0].size() - 1
		|| tileX_Pos / TOP_TILESIZE < 0 || (tileX_Pos + vecX) / TOP_TILESIZE < 0)
	{
		return;
	}
	else if ((*enemy->getMap())[tileY_Pos / TOP_TILESIZE][(tileX_Pos + vecX) / TOP_TILESIZE]->getIsAvailMove() == false
		|| (*enemy->getMap())[tileY_Pos / TOP_TILESIZE][(tileX_Pos + vecX) / TOP_TILESIZE]->getTopTileAttr() == TILE_HOLE)
	{
		enemy->setVecX(0);
	}
	else if ((*enemy->getMap())[(tileY_Pos + vecY) / TOP_TILESIZE][tileX_Pos / TOP_TILESIZE]->getIsAvailMove() == false
		|| (*enemy->getMap())[(tileY_Pos + vecY) / TOP_TILESIZE][tileX_Pos / TOP_TILESIZE]->getTopTileAttr() == TILE_HOLE)
	{
		enemy->setVecY(0);
	}

}
