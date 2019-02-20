#pragma once
#include "boss.h"

class bossState abstract
{
public:
	virtual void update(boss* boss) abstract;
};

