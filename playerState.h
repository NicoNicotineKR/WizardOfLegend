#pragma once
#include "gameNode.h"
#include "player.h"

class player;

class playerState abstract
{
public:

	virtual void onButtonW(player* Player)  abstract;
	virtual void onButtonS(player* Player)	abstract;
	virtual void onButtonA(player* Player)	abstract;
	virtual void onButtonD(player* Player)	abstract;
	virtual void offButtonW(player* Player)  abstract;
	virtual void offButtonS(player* Player)	abstract;
	virtual void offButtonA(player* Player)	abstract;
	virtual void offButtonD(player* Player)	abstract;

	virtual void onButtonQ(player* Player)	abstract;
	virtual void onButtonE(player* Player)	abstract;
	virtual void onButtonR(player* Player)	abstract;
	virtual void onButtonSpace(player* Player)	abstract;
	virtual void onButtonLB(player* Player)	abstract;
	virtual void onButtonRB(player* Player)	abstract;
	virtual void update(player* Player)	abstract;

};

