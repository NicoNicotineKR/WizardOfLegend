#pragma once
#include "bossState.h"
class boss_State_Casting : public bossState
{
public:
	boss_State_Casting();
	~boss_State_Casting();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

