#pragma once
#include "bossState.h"
class boss_State_SKILL_Four : public bossState
{
public:
	boss_State_SKILL_Four();
	~boss_State_SKILL_Four();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

