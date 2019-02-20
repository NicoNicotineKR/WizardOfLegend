#pragma once
#include "bossState.h"
class boss_State_Idle : public bossState
{
public:
	boss_State_Idle();
	~boss_State_Idle();
public:
	virtual void update(boss* boss) override;
};

