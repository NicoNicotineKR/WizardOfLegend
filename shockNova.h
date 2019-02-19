#pragma once
#include "stdafx.h"
#include "skills.h"

class shockNova : public skills
{
private:
	image* _thunderSharftImg;


public:
	shockNova();
	~shockNova();

	HRESULT init(player* Player)		override;
	void release(player* Player)		override;
	void update(player* Player)			override;
	void render(player* Player)			override;
	void skillPosSet(player* Player)	override;
	void destroySkill(int i)			 override;
	//inline image*     getThunderSharftImg() { return _thunderSharftImg; }
};

