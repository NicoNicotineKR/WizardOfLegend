#pragma once
#include "bossState.h"
class boss_State_SKILL_Five : public bossState
{
public:
	boss_State_SKILL_Five();
	~boss_State_SKILL_Five();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

