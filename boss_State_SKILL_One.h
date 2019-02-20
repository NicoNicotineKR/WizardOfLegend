#pragma once
#include "bossState.h"
class boss_State_SKILL_One : public bossState
{
public:
	boss_State_SKILL_One();
	~boss_State_SKILL_One();
public:
	virtual void update(boss* boss) override;
};

