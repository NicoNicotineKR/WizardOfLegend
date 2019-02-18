#pragma once
#include "bossState.h"
class boss_State_Death_Start : public bossState
{
public:
	boss_State_Death_Start();
	~boss_State_Death_Start();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

