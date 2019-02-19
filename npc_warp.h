#pragma once
#include "npc.h"
class npc_warp :
	public npc
{
private:

public:
	npc_warp();
	~npc_warp();

	HRESULT init();
	void release();
	void update();
	void render();

	void isOnceAniPlay(stateNpc EnumNumber);
	static void idle2(void* obj);
};

