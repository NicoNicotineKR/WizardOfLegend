#pragma once
#include "npc.h"

class npc_wardrobe : public npc
{
private:


public:
	npc_wardrobe();
	~npc_wardrobe();

	HRESULT init();
	void release();
	void update();
	void render();

	void isOnceAniPlay(stateNpc EnumNumber);

	static void idle1(void* obj);
	static void idle_ui1_esc1(void* obj);
};

