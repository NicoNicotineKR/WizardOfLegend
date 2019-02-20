#pragma once
#include "bossState.h"
class boss_State_Death_Start : public bossState
{
public:
	boss_State_Death_Start();
	~boss_State_Death_Start();
public:
	virtual void update(boss* boss) override;
};

