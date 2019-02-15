#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "player.h"

class player;

class skills : public gameNode
{
protected:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	vvMap* _vvMap;

	image*		_img;
	POINTFLOAT	_pos;
	RECT		_collisionRc;
	string		_name;
	float		_coolDown;
	float		_reLoadCurTime;
	int			_reLoadCount;
	int			_damage;
	float		_angle;
	float		_speed;
	float		_imgCount;
	



public:

	virtual HRESULT init(player* Player); 
	virtual void release(player* Player);
	virtual void update(player* Player);
	virtual void render(player* Player);
	
	inline POINTFLOAT getPos() { return _pos;}
};

