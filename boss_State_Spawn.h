#pragma once
#include "bossState.h"
class boss_State_Spawn : public bossState
{
public:
	boss_State_Spawn();
	~boss_State_Spawn();
public:
	virtual void update(boss* boss) override;
};

