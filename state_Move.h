#pragma once
#include "stdafx.h"
#include "playerState.h"

class state_Move : public playerState
{
public:
	state_Move();
	~state_Move();

public:
	virtual void onButtonW(player* Player)		override;
	virtual void onButtonS(player* Player)		override;
	virtual void onButtonA(player* Player)		override;
	virtual void onButtonD(player* Player)		override;
	virtual void offButtonW(player* Player)		override;
	virtual void offButtonS(player* Player)		override;
	virtual void offButtonA(player* Player)		override;
	virtual void offButtonD(player* Player)		override;
	virtual void onButtonQ(player* Player)		override;
	virtual void onButtonE(player* Player)		override;
	virtual void onButtonR(player* Player)		override;
	virtual void onButtonSpace(player* Player)	override;
	virtual void onButtonLB(player* Player)		override;
	virtual void onButtonRB(player* Player)		override;
	virtual void update(player* Player)			override;

};

