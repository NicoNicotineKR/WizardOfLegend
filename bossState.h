#pragma once
#include "boss.h"

class bossState abstract
{
public:
	virtual void Direction_left(boss* boss) abstract;
	virtual void Direction_right(boss* boss) abstract;
	virtual void update(boss* boss) abstract;
};

