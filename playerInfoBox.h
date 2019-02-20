#pragma once
#include "gameNode.h"

struct tagBox // 전체적인 큰창
{
	image* img;
	POINT pos;
};
struct tagKeyButton // 상호작용될 키 보여주는 버튼
{
	image* img;
	POINT pos;
	int frameX;
};
struct tagSkillBox // 교환박스
{
	image* img;
	RECT rc;
	POINT pos;
	//깜박거림
	bool isBlink;
	int alpha;
	bool isBlinkUp;

	//박스번호
	int boxNumber;
	int boxFrameX;

	//진짜 바꿀아무거나
	//int idx;
	string skillName;
};
struct tagUI // 테두리
{
	image* image;
	RECT rc;
	POINT pos;
	bool isBlink;
	bool isBlinkUp;
	int FrameX;
	int alpha;
};
class playerInfoBox : public gameNode
{
private:
	bool _isStart;

	tagBox _box;
	tagKeyButton _button[6];

	//교환박스
	tagSkillBox _skillBox[6];

	//테두리
	tagUI _skillBoxEdge;
	tagUI _changeModeImg;

	//====== 교환용
	bool _isChanging;
	//현재 배열번호를 저장해둘 변수
	int _currentboxNumber;
	//idx를 저장해둘 번호
	string _saveSkillName;

	//=======
	int _selectIdx;





	const int BLINK_ALPHA_SPEED = 5;
	const int BLINK_ALPHA_MIN = 100;

public:
	playerInfoBox();
	~playerInfoBox();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsStart(){return _isStart;}
};

