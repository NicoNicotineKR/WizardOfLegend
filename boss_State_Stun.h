#pragma once
#include "bossState.h"
class boss_State_Stun : public bossState
{
public:
	boss_State_Stun();
	~boss_State_Stun();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

