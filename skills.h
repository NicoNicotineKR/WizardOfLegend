#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include "player.h"
#include "enemyMgr.h"
#include "boss.h"

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
	float       _attackCount;

	RECT	_flameRc[5];
	RECT	_stoneShotRc[3];

	//	재만추가 -> 에너미들한테 스킬이 데미지줘야함
	enemyMgr* _em;
	boss* _boss;

public:

	virtual HRESULT init(player* Player)		abstract; 
	virtual void release(player* Player)		abstract;
	virtual void update(player* Player)			abstract;
	virtual void render(player* Player)			abstract;
	virtual void skillPosSet(player* Player)	abstract;
	virtual void destroySkill(int i)		    abstract;
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

	//배열크기 5짜리 렉트 i에 인덱스 번호 집어넣으셈.
	inline RECT		  getSearingRushRc(int i) { return _flameRc[i]; }

	//배열크기 3짜리 렉트 i에 인덱스 번호 집어 넣으셈.
	inline RECT		  getStoneShotRc(int i) { return _stoneShotRc[i]; }


};

