#include "stdafx.h"
#include "state_Fall.h"


state_Fall::state_Fall()
{
}


state_Fall::~state_Fall()
{
}

void state_Fall::onButtonW(player * Player)
{
}

void state_Fall::onButtonS(player * Player)
{
}

void state_Fall::onButtonA(player * Player)
{
}

void state_Fall::onButtonD(player * Player)
{
}

void state_Fall::offButtonW(player * Player)
{
}

void state_Fall::offButtonS(player * Player)
{
}

void state_Fall::offButtonA(player * Player)
{
}

void state_Fall::offButtonD(player * Player)
{
}

void state_Fall::onButtonQ(player * Player)
{
}

void state_Fall::onButtonE(player * Player)
{
}

void state_Fall::onButtonR(player * Player)
{
}

void state_Fall::onButtonSpace(player * Player)
{
}

void state_Fall::onButtonLB(player * Player)
{
}

void state_Fall::onButtonRB(player * Player)
{
}

void state_Fall::update(player * Player)
{
	if (Player->getIsHit())
	{
		Player->setIsHit(false);
		Player->startAni();
	}
	RECT temp;
	if (IntersectRect(&temp, &Player->getCollisionRc(), &(*Player->getVVMap())[Player->getCollisionRc().bottom / 32][Player->getCollisionRc().left / 32]->getTopTileRc()))
	{
		//if ((*Player->getVVMap())[Player->getCollisionRc().bottom / 32][Player->getCollisionRc().left / 32]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
		//{
			for (int i = 0; i < 5; ++i)
			{
				POINTFLOAT pos;
				POINT	   index;
				for (int j = 0; j < 5; ++j)
				{
					if (Player->getTileBlanket((i * 5) + j) != nullptr ) continue;
					//int num = i * 3 + j;

						Player->setTileBlanket((*Player->getVVMap())[Player->getPlayerTileCheckRc().bottom / 32+ i][Player->getPlayerTileCheckRc().left / 32 + j -1]->getTopTileImg(), (i * 5) + j);
						if ((*Player->getVVMap())[Player->getCollisionRc().bottom / 32 + i][Player->getCollisionRc().left / 32 + ( j -1)]->getTopTileAttr() == E_TILE_ATR::TILE_HOLE)
						{
							pos.x = -32;
							pos.y = -32;
						}
						else
						{
							pos.x = (*Player->getVVMap())[Player->getCollisionRc().bottom / 32 + i][Player->getCollisionRc().left / 32 + (j - 1)]->getTopTileRc().left;
							pos.y = (*Player->getVVMap())[Player->getCollisionRc().bottom / 32 + i][Player->getCollisionRc().left / 32 + (j - 1)]->getTopTileRc().top;
						}

						index.x = (*Player->getVVMap())[Player->getCollisionRc().bottom / 32 + i][Player->getCollisionRc().left / 32 + (j - 1)]->getTopTileFrameX();
						index.y = (*Player->getVVMap())[Player->getCollisionRc().bottom / 32 + i][Player->getCollisionRc().left / 32 + (j - 1)]->getTopTileFrameY();
						Player->setTileBlanketPos(pos, (i * 5) + j);
						Player->setTileBlanketIndex(index, (i * 5) + j);

				}
			//}
		}
	}
	Player->setFallVecY(Player->getFallVecY() + 3.0f);
	Player->setVecY(3.0f);
	if (Player->getFallVecY() > 60.0f)
	{
			Player->setState(STATE::IDLE);
			Player->currentPlayerState();
			Player->startAni();
			Player->setPosX(Player->getDashLastPos().x);
			Player->setPosY(Player->getDashLastPos().y);
			for (int i = 0; i < 25; ++i)
			{
				POINTFLOAT pos;
				POINT		index;
				pos.x = pos.y = NULL;
				index.x = index.y = NULL;
				Player->setTileBlanket(nullptr, i);
				Player->setTileBlanketPos(pos, i);
				Player->setTileBlanketIndex(index, i);

			}
			if (Player->getCurHp() <= 0)
			{
				Player->setState(STATE::DEAD);
				Player->currentPlayerState();
				Player->startAni();
			}
		Player->setVecY(0);
	}
}
