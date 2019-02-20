#pragma once
#include "bossState.h"
class boss_State_Casting : public bossState
{
public:
	boss_State_Casting();
	~boss_State_Casting();
public:
	virtual void update(boss* boss) override;
};

