#include "stdafx.h"
#include "boss_State_Idle.h"


boss_State_Idle::boss_State_Idle()
{
}


boss_State_Idle::~boss_State_Idle()
{
}

void boss_State_Idle::update(boss * boss)
{
	//아이들은 초반 다이얼로그 띄울때만있음. 다이얼로그가 끝나면 해당 다이얼로그에서 알아서 casting상태로 변경해줄것임
}
