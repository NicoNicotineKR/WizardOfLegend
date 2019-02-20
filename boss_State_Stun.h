#pragma once
#include "bossState.h"
class boss_State_Stun : public bossState
{
public:
	boss_State_Stun();
	~boss_State_Stun();
public:
	virtual void update(boss* boss) override;
};

