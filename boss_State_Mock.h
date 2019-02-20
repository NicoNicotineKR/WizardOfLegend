#pragma once
#include "bossState.h"
class boss_State_Mock : public bossState
{
public:
	boss_State_Mock();
	~boss_State_Mock();
public:
	virtual void update(boss* boss) override;
};

