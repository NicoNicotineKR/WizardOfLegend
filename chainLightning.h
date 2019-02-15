#pragma once
#include "stdafx.h"
#include "skills.h"

class chainLightning : public skills
{
private:
	int _attackCount;
public:
	chainLightning();
	~chainLightning();
	HRESULT init(player* Player) override;
	void release(player* Player) override;
	void update(player* Player)  override;
	void render(player* Player)  override;


};

