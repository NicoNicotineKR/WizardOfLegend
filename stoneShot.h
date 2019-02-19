#pragma once
#include "stdafx.h"
#include "skills.h"
class stoneShot : public skills
{
public:

	bool _isSkillImgRender;
	image* _stoneShotImg[3];
	bool	_isRender[3];
	POINTFLOAT _stoneShotPos[3];
	float	   _stoneShotAngle[3];
	float		_range;
	float		_speed;
	POINTFLOAT _firePos[3];
public:

	virtual HRESULT init(player* Player)		override;
	virtual void release(player* Player)		override;
	virtual void update(player* Player)			override;
	virtual void render(player* Player)			override;
	virtual void skillPosSet(player* Player)	override;
	virtual void destroySkill(int i)			 override;
};

