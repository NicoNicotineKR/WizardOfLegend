#pragma once
#include "bossState.h"
class boss_State_Death : public bossState
{
public:
	boss_State_Death();
	~boss_State_Death();
public:
	virtual void update(boss* boss) override;
};

