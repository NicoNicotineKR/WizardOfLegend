#pragma once
#include "gameNode.h"
class boseSkills : public gameNode
{
private:

public:
	boseSkills();
	~boseSkills();

	virtual HRESULT init() abstract;
	virtual void release() abstract;
	virtual void update() abstract;
	virtual void render() abstract;

	virtual void UseSkill() abstract;

};

