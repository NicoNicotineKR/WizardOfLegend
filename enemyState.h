#pragma once
//#include "gameNode.h"
#include "enemy.h"

//class enemy;

class enemyState abstract
{
public:
	virtual void direction_Left (enemy* enemy) abstract;
	virtual void direction_right(enemy* enemy) abstract;
	virtual void update(enemy* enemy) abstract;
};

