#include "stdafx.h"
#include "npcMgr.h"


npcMgr::npcMgr()
{
}


npcMgr::~npcMgr()
{
}

HRESULT npcMgr::init()
{
	npc_SpellBook* _npc_SpellBook = new npc_SpellBook;
	_vNpc.push_back(_npc_SpellBook);

	npc_broomStick* _npc_broomStick = new npc_broomStick;
	_vNpc.push_back(_npc_broomStick);

	npc_wardrobe* _npc_wardrobe = new npc_wardrobe;
	_vNpc.push_back(_npc_wardrobe);

	npc_mimi* _npc_mimi = new npc_mimi;
	_vNpc.push_back(_npc_mimi);

	npc_warp* _npc_warp = new npc_warp;
	_vNpc.push_back(_npc_warp);

	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->init();
	}

	_vNpc[0]->setPos({ 2200 , 1000 });
	_vNpc[1]->setPos({ 1300 , 1000 });
	_vNpc[2]->setPos({ 430 , 750 });
	_vNpc[3]->setPos({ 1400 , 1550 });
	_vNpc[4]->setPos({ 1150 , 50 });
	return S_OK;
}

void npcMgr::release()
{
	for (int i = 0; i < _vNpc.size(); i++) {
		SAFE_RELEASE(_vNpc[i]);
		SAFE_DELETE(_vNpc[i]);
	}
	_vNpc.clear();

}

void npcMgr::update()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->update();
		_vNpc[i]->setPlayerPos(_playerPos);
	}
}

void npcMgr::render()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->render();
	}
}
