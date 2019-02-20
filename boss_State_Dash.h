#pragma once
#include "bossState.h"
class boss_State_Dash : public bossState
{
public:
	boss_State_Dash();
	~boss_State_Dash();
public:
	virtual void update(boss* boss) override;
};

