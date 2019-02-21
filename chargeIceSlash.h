#pragma once
#include "gameNode.h"

//	 ���� �̵���
//	�÷��̾ �ִ� �ڸ��� ���پƾƾƾ�


//	�̴� , ������Ʈ�� �ʿ�.
//	���� �ʿ����
//	



class chargeIceSlash : public gameNode
{
private:

	int _slashNum;
	POINTFLOAT _destPos;
	POINTFLOAT _vec;
	float _angle;

	float _skillTimer;
	bool _isStart;

	float _totalFrameNum;
	
	

	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;

	const float END_TIME = 0.3f;
	//const float MOVESPD = 20.f;

public:
	chargeIceSlash();
	~chargeIceSlash();

	HRESULT init();
	void release();
	void update();
	void render();


	//	slashNum �� �ƹ��ǹ̾���.
	void UseSkill(POINTFLOAT* bossPos, POINTFLOAT* playerPos, int slashNum);

	bool getIsStart() { return _isStart; }


};

