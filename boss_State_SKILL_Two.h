#pragma once
#include "bossState.h"
class boss_State_SKILL_Two : public bossState
{
public:
	boss_State_SKILL_Two();
	~boss_State_SKILL_Two();
public:
	virtual void update(boss* boss) override;
};

