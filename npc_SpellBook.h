#pragma once
#include "npc.h"

class npc_SpellBook : public npc
{
private:
	bool _saveTalkDirection;

public:
	npc_SpellBook();
	~npc_SpellBook();

	HRESULT init();
	void release();
	void update();
	void render();

	void isOnceAniPlay(stateNpc EnumNumber);

	//콜백함수
	static void idleR(void* obj);
	static void idleL(void* obj);
	static void ui1(void* obj);
};

