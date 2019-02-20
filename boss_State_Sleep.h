#pragma once
#include "bossState.h"
class boss_State_Sleep : public bossState
{
public:
	boss_State_Sleep();
	~boss_State_Sleep();


public:
	virtual void update(boss* boss) override;
};

