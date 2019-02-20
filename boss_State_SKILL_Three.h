#pragma once
#include "bossState.h"
class boss_State_SKILL_Three : public bossState
{
public:
	boss_State_SKILL_Three();
	~boss_State_SKILL_Three();
public:
	virtual void update(boss* boss) override;
};

