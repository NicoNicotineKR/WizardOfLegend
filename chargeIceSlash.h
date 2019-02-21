#pragma once
#include "gameNode.h"

//	 보스 이동기
//	플레이어가 있던 자리로 간다아아아아


//	이닛 , 업데이트만 필요.
//	렌더 필요없음
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


	//	slashNum 은 아무의미없다.
	void UseSkill(POINTFLOAT* bossPos, POINTFLOAT* playerPos, int slashNum);

	bool getIsStart() { return _isStart; }


};

