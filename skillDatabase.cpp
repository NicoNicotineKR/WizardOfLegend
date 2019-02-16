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
	
	for (int i = 0; i < KINDS_NUMMAX; i++) {
		for (int j = 0; j < ATR_NUMMAX; j++) {
			_vSkillInfo[i][j].clear();
			_skillNum[i][j] = 0;
		}
	}


	AddSkill("FlameStrike", true, FIRE, BASIC);
	AddSkill("stoneShot", true, EARTH, BASIC);
	AddSkill("searingRush", true, FIRE, DASH);
	AddSkill("shatteringStrike", true, EARTH, SIGNITURE);
	AddSkill("shockNova", true, ELECTRO, SIGNITURE);
	AddSkill("frostFan", true, ICE, SIGNITURE);
	AddSkill("reboundingIcicles", true, ICE, SIGNITURE);
	AddSkill("thunderingChain", true, ELECTRO, STANDARD);

	AddSkill("lightningAspect", false, ELECTRO, STANDARD);
	AddSkill("arcSphere", false, ELECTRO, STANDARD);
	AddSkill("magSphere", false, ELECTRO, STANDARD);
	AddSkill("thunderDrop", false, ELECTRO, STANDARD);
	AddSkill("shockAssault", false, ELECTRO, STANDARD);



	
	

	return S_OK;
}

void skillDatabase::release()
{
}

void skillDatabase::AddSkill(string name, bool isGet, int attr, int kinds)
{
	tagSkillInfo tmpSkillInfo;
	tmpSkillInfo.name = name;
	tmpSkillInfo.isGet = true;
	tmpSkillInfo.attr = attr;
	tmpSkillInfo.kinds = kinds;

	_mSkillInfo.insert(make_pair(name, tmpSkillInfo));
	_vSkillInfo[kinds][attr].push_back(tmpSkillInfo);

	_skillNum[kinds][attr]++;

}

bool skillDatabase::getIsGetSkill(string name)
{
	_miSkillInfo = _mSkillInfo.find(name);
	return _miSkillInfo->second.isGet;
}

int skillDatabase::getAttr(string name)
{
	_miSkillInfo = _mSkillInfo.find(name);
	return _miSkillInfo->second.attr;
}

int skillDatabase::getKinds(string name)
{
	_miSkillInfo = _mSkillInfo.find(name);
	return _miSkillInfo->second.kinds;
}

tagSkillInfo skillDatabase::getSkillInfo(string name)
{
	_miSkillInfo = _mSkillInfo.find(name);
	return _miSkillInfo->second;
}
