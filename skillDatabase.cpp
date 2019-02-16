#include "stdafx.h"
#include "skillDatabase.h"


skillDatabase::skillDatabase()
{
}


skillDatabase::~skillDatabase()
{
}

HRESULT skillDatabase::init()
{
	AddSkill("FlameStrike", true, FIRE, BASE);
	AddSkill("stoneShot", true, EARTH, BASE);
	AddSkill("searingRush", true, FIRE, DASH);
	AddSkill("shatteringStrike", true, EARTH, SIGNITURE);
	AddSkill("shockNova", true, ELECTRO, SIGNITURE);
	AddSkill("frostFan", true, ICE, SIGNITURE);
	AddSkill("reboundingIcicles", true, ICE, SIGNITURE);
	AddSkill("thunderingChain", true, ELECTRO, STANDARD);
	
	return S_OK;
}

void skillDatabase::AddSkill(string name, bool isGet, int attr, int kinds)
{
	tagSkillInfo tmpSkillInfo;
	tmpSkillInfo.name = name;
	tmpSkillInfo.isGet = true;
	tmpSkillInfo.attr = attr;
	tmpSkillInfo.kinds = kinds;

	_mSkillInfo.insert(make_pair(name, tmpSkillInfo));

}
