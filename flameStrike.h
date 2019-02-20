#pragma once
#include "stdafx.h"
#include "skills.h"

class flameStrike : public skills
{
private:

	bool _isSkillImgRender;
	image* _img2;
	image* _img3;
	bool	_isRender[3];

	//		=== 재만 추가 ===
	bool _isHit;
	const int ATK_DMG = 10;

public:

	virtual HRESULT init(player* Player)		override;
	virtual void release(player* Player)		override;
	virtual void update(player* Player)			override;
	virtual void render(player* Player)			override;
	virtual void skillPosSet(player* Player)	override;
	virtual void destroySkill(int i)			 override;
};

