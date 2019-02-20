#pragma once
#include "gameNode.h"

struct tagBox // ��ü���� ūâ
{
	image* img;
	POINT pos;
};
struct tagKeyButton // ��ȣ�ۿ�� Ű �����ִ� ��ư
{
	image* img;
	POINT pos;
	int frameX;
};
struct tagSkillBox // ��ȯ�ڽ�
{
	image* img;
	RECT rc;
	POINT pos;
	//���ڰŸ�
	bool isBlink;
	int alpha;
	bool isBlinkUp;

	//�ڽ���ȣ
	int boxNumber;
	int boxFrameX;

	//��¥ �ٲܾƹ��ų�
	//int idx;
	string skillName;
};
struct tagUI // �׵θ�
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

	//��ȯ�ڽ�
	tagSkillBox _skillBox[6];

	//�׵θ�
	tagUI _skillBoxEdge;
	tagUI _changeModeImg;

	//====== ��ȯ��
	bool _isChanging;
	//���� �迭��ȣ�� �����ص� ����
	int _currentboxNumber;
	//idx�� �����ص� ��ȣ
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

