#pragma once
#include "npc.h"
class npc_broomStick : public npc
{
private:

	bool yameMove1;

	const int STICK_SPEED = 2;
public:
	npc_broomStick();
	~npc_broomStick();

	HRESULT init();
	void release();
	void update();
	void render();

	void isOnceAniPlay(stateNpc EnumNumber);
};

