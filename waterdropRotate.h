#pragma once
#include "gameNode.h"

//	보스에 인클루드한다.
//	필요한 재료 : POINTFLOAT형의 &bossPos, &playerPos
//	사용방법
//	이닛을 해준다.
//	update(), render()를 걸어준다.
//	UseSkill();쓰면 작동하고, 일정시간 후에 스스로 초기화된다.
//	끗-


class waterdropRotate :	public gameNode
{
private:

	struct tagWaterDrop {
		image* img;
		POINTFLOAT pos;
		RECT rc;
		//POINTFLOAT judgePos;
		RECT judgeRc;
		POINTFLOAT vec;
		float rotateAngle;
		int alpha;
		bool isShot;
	};


	vector<tagWaterDrop*> _vWaterDrops;
	int _waterDropNum;
	int _preparedWaterdropNum;
	int _shotMissileIdx;

	float _prepareMissileTimer;		//	하나 장전할때까지 시간재주는 타이머
	float _shootingMissileTimer;
	float _missleGenTime;			//	하나 장전하기까지 걸리는 시간
	float _totalSkillElapsedTime;
	

	int _frameCounter;
	float _rotateAngle;

	bool _isStart;
	bool _isRdyToShot;
	





	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;

	const int WATERDROP_SPD = 40;			//	날아가는 속도
	const int WATERDROP_WID = 60;			//	건들지마시오
	const int JUDGE_RC_WID = 38;			//	판정렉트 가로세로
	const float PREPARE_TIME = 0.5f;		//	쏘기까지 준비시간
	const int AUG_ALPHA = 60;				//	마지막놈이 알파 255되야 실제로 쏨
	const float ROTATE_RAD = 150.0f;		//	회전반지름
	const float ROTATE_ANGLE_SPD = PI / 64;		//	나누는 숫자 작아질수록 빨리돔
	const float END_SKILTIME = 10.0f;		//	스킬 끝나서 초기화되는시간.
	const int FRAME_COUNTMAX = 10;		//	물방울 이미지 프레임 변하는 카운터
	const float SHOOTINGSPD = 0.2f;		//	발사속도(몇초마다?)


public:
	waterdropRotate();
	~waterdropRotate();


	HRESULT init();
	void release();
	void update();
	void render();

	void UseSkill(POINTFLOAT* bossPos, POINTFLOAT* playerPos, int missileNum);

	void RotatemissleFunc();
	void RotatemissleFunc(int idx);
	void AlphaIncreaseFunc();
	void FrameIncreaseFunc();
	void FrameIncreaseFunc(int idx);
	void PrepareShotMissile(int idx);
	void MissileMove(int idx);
	void EndSkill();

	vector<tagWaterDrop*> getVMissle() { return _vWaterDrops; }

	void setJudgeRc(int idx, RECT rc) { _vWaterDrops[idx]->rc = rc; }
};

