#pragma once
#include "bossState.h"
class boss_State_Idle : public bossState
{
public:
	boss_State_Idle();
	~boss_State_Idle();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

