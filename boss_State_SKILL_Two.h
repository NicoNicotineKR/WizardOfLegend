#pragma once
#include "bossState.h"
class boss_State_SKILL_Two : public bossState
{
public:
	boss_State_SKILL_Two();
	~boss_State_SKILL_Two();
public:
	virtual void Direction_left(boss* boss) override;
	virtual void Direction_right(boss* boss) override;
	virtual void update(boss* boss) override;
};

