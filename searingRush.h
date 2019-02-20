#pragma once
#include "stdafx.h"
#include "skills.h"

class searingRush : public skills
{
private:
	image* _flameImg[5];
	POINTFLOAT _flamePos[5];

	bool _isHit[5];
	const int ATK_DMG = 10;

public:
	searingRush();
	~searingRush();
	HRESULT init(player* Player)		override;
	void release(player* Player)		override;
	void update(player* Player)			override;
	void render(player* Player)			override;
	void skillPosSet(player* Player)	override;
	virtual void destroySkill(int i)			 override;
};

