#pragma once
#include "gameNode.h"
enum IconList
{
	TAP = 0,
	MAP,

	ICONMAX,

};
struct tagIcon
{
	image* img;
	int x;
	int y;
};
class playerInfoBoxUI : public gameNode
{
	//�����ܵΰ�
	tagIcon _icon[2];

	tagIcon _icon2[2];

public:
	playerInfoBoxUI();
	~playerInfoBoxUI();

	HRESULT init();
	void release();
	void update();
	void render();
};

