#pragma once


struct tagSkillInfo {
	string name;
	bool isGet;
	int attr;		//	��, ��...�Ӽ�?
	int kinds;	//	��ų ����
};

enum E_Skill_ATR {
	FIRE = 0,
	WIND,
	EARTH,
	ELECTRO,
	ICE,
	ATRVOID,
	ATR_NUMMAX,
};

enum E_SKILL_KINDS {
	BASIC,
	DASH,
	STANDARD,
	SIGNITURE,
	KINDS_NUMMAX,
};