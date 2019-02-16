#pragma once
#include "gameNode.h"
#include "skillNode.h"
#include "skillIconList.h"
class skillDatabase : public gameNode
{
private:
	
	skillIconList* _skillIconLst;
	
	struct tagSkillInfo {
		string name;
		bool isGet;
		int attr;		//	불, 땅...속성?
		int kinds;	//	스킬 종류
	};

	
	map<string, tagSkillInfo>			_mSkillInfo;
	map<string, tagSkillInfo>::iterator _miSkillInfo;




public:
	skillDatabase();
	~skillDatabase();

	HRESULT init();
	void AddSkill(string name, bool isGet, int attr, int kinds);
};

