#pragma once
#include "gameNode.h"

class skills : public gameNode
{
private:
	image*		_image;
	POINTFLOAT	_pos;
	RECT		_collisionRc;
	string		_name;
	float		_coolDown;
	int			_damage;
	float		_angle;
	float		_speed;





public:
	skills();
	~skills();

	
};

