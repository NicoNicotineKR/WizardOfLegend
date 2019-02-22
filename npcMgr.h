#pragma once
#include "gameNode.h"
#include "npc_SpellBook.h"
#include "npc_broomStick.h"
#include "npc_wardrobe.h"
#include "npc_mimi.h"
#include "npc_warp.h"



class npcMgr : public gameNode
{
private:
	vector<npc*>					_vNpc;
	vector<npc*>::iterator			_viNpc;

	POINTFLOAT _playerPos;


public:
	npcMgr();
	~npcMgr();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayerPos(POINTFLOAT playerPos) { _playerPos = playerPos; }

	vector<npc*>				getvNpce() { return _vNpc; }
	vector<npc*>::iterator		getviNpce() { return _viNpc; }
	void setvNpc(vector<npc*> vNpc) { _vNpc = vNpc; }
};

