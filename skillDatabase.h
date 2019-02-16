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
		int attr;		//	��, ��...�Ӽ�?
		int kinds;	//	��ų ����
	};

	
	map<string, tagSkillInfo>			_mSkillInfo;
	map<string, tagSkillInfo>::iterator _miSkillInfo;




public:
	skillDatabase();
	~skillDatabase();

	HRESULT init();
	void AddSkill(string name, bool isGet, int attr, int kinds);
};

