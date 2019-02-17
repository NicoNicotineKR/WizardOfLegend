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

	float		_totalCoolTime;
	float		_curCoolTime;
	int			_maxReLoad;
	int			_reLoadCount;
	int			_index;

	int			_damage;
	float		_angle;
	float		_speed;
	float		_imgCount;
	
	bool		_isSkill;



public:

	virtual HRESULT init(player* Player)		abstract; 
	virtual void release(player* Player)		abstract;
	virtual void update(player* Player)			abstract;
	virtual void render(player* Player)			abstract;
	virtual void skillPosSet(player* Player)	abstract;

	inline POINTFLOAT getPos() { return _pos;}
	inline string	  getName() { return _name; }


	inline int*		  getMaxReLoadAddress() { return &_maxReLoad; }
	inline int*		  getReLoadCountAddress() { return &_reLoadCount; }
	inline float*	  getTotalCoolTimeAddress() { return &_totalCoolTime; }
	inline float*	  getCurCoolTimeAddress() { return &_curCoolTime; }

	inline bool		  getIsSkill() { return _isSkill; }
	inline void		  setIsSkill(bool isSkill) { _isSkill = isSkill; }

	inline int		  getReLoadCount() { return _reLoadCount; }
	inline int		  getMaxReLoad() { return _maxReLoad; }

	inline void		  setReLoadCount(int reLoadCount) { _reLoadCount = reLoadCount; }
	inline RECT		  getCollisionRc() { return _collisionRc; }
};

