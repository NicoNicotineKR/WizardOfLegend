#pragma once
#include "gameNode.h"
class skillIconList : public gameNode
{
private:
	image* _skillsImg;
	map<string, POINT>			 _mSkillIdxList;
	map<string, POINT>::iterator _miSkillIdxList;

	int _frameWid;
	int _frameHei;

public:
	skillIconList();
	~skillIconList();

	HRESULT init();
	void release();
	void update();
	
	void frameRender(int centerX, int centerY, int idxX, int idxY);
	void frameRender(int centerX, int centerY, string skillName);
	void alphaFrameRender(int centerX, int centerY, int idxX, int idxY, int alpha);

	void	InitSkillList();
	void	AddSkillList(string keyName, int idxX, int idxY);
	POINT	FindSkillIdx(string keyName);

	image*	getIconsImg() { return _skillsImg; }
	
};

