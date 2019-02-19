#pragma once
#include "npc.h"
class npc_mimi : public npc
{
private:



public:
	npc_mimi();
	~npc_mimi();

	HRESULT init();
	void release();
	void update();
	void render();

	void isOnceAniPlay(stateNpc EnumNumber);
	static void idle2(void* obj);
};

