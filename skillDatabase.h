#pragma once
#include "singletonBase.h"
//#include "image.h"
#include "skillNode.h"
//#include "skillIconList.h"

class skillDatabase : public singletonBase<skillDatabase>
{
private:
	
	//image* _backBuffer2;

	//skillIconList* _skillIconLst;
		
	map<string, tagSkillInfo>			_mSkillInfo;
	map<string, tagSkillInfo>::iterator _miSkillInfo;

	vector<tagSkillInfo> _vSkillInfo[KINDS_NUMMAX][ATR_NUMMAX];
	
	int _skillNum[KINDS_NUMMAX][ATR_NUMMAX];	//	[스킬종류][스킬속성]

	



public:
	skillDatabase();
	~skillDatabase();

	//HDC getMemDC() { _backBuffer2->getMemDC(); }
	//void linkDC(image* backBuffer) { _backBuffer2 = backBuffer; }

	HRESULT init();
	void release();
	void AddSkill(string name, bool isGet, int attr, int kinds);

	bool getIsGetSkill(string name);
	int getAttr(string name);
	int getKinds(string name);
	tagSkillInfo getSkillInfo(string name);
	vector<tagSkillInfo> getvSkillInfo(int kinds, int attr) { return _vSkillInfo[kinds][attr]; }
	int getSkillNum(int kinds, int attr) { return _skillNum[kinds][attr]; }
	


};

