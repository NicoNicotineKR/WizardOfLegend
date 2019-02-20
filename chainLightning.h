#pragma once
#include "stdafx.h"
#include "skills.h"

class chainLightning : public skills
{
private:
	image* _thunderFloorImg;

	// === 재만 추가 ===
	bool _isHit;
	const int ATK_DMG = 10;
public:
	chainLightning();
	~chainLightning();
	HRESULT init(player* Player) override;
	void release(player* Player) override;
	void update(player* Player)  override;
	void render(player* Player)  override;

	void skillPosSet(player* Player) override;
	virtual void destroySkill(int i) override;
};

