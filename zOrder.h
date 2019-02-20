#pragma once
#include "gameNode.h"
#include "enemyMgr.h"
#include "player.h"
#include "objectMgr.h"


class zOrder : public gameNode
{
private:
	vector<image*> _vZorder;


public:
	zOrder();
	~zOrder();

	//bool operator <(image* &object) {
	//	return  
	//}

	void ClearAll() { _vZorder.clear(); }
	void PushBack(image* object) { _vZorder.push_back(object); }
	

};

