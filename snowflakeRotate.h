#pragma once
#include "gameNode.h"
class snowflakeRotate :	public gameNode
{
private:
	struct tagSnowFlake {
		image* img;
		POINTFLOAT pos;
		RECT rc;
		RECT judgeRc;
		POINTFLOAT vec;
		float rotateAngle;
		float augRotateAngleSpd;
		bool isShot;
		int frameX;
	};

	vector<tagSnowFlake*> _vSnowFlakes;
	int _flakeNum;
	float _rotateRad;
	float _augRotateRad;
	float _augAngle;

	int _frameAugCounter;

	bool _isStart;
	bool _isRdyToShot;

	float _shottingTimer;
	int _shotMissileIdx;

	float _totalSkillTimer;


	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;


	const int FRAMECOUNT_MAX = 10;		//	프레임 변하는 속도
	const float ROTATE_RAD_MAX = 150.0f;		//	회전반지름
	const float ROTATE_AUG_RAD = 1.8f;
	const float ROTATE_ANGLE_SPD_MAX = PI / 64;		//	나누는 숫자 작아질수록 빨리돔
	const float ROTATE_AUG_ANGLESPD = PI / 256;		//	

	const float SHOOTING_SPD = 0.08f;			//	쏘는속도
	const float MISSILE_SPD = 35.f;

	const float PREPARE_TIME = 3.0f;
	const float END_TIME = 8.0f;

	const int JUDGERC_WID = 40;
	const int FLAKERC_WID = 50;
	


public:
	snowflakeRotate();
	~snowflakeRotate();

	HRESULT init();
	void release();
	void update();
	void render();

	void UseSkill(POINTFLOAT* bossPos, POINTFLOAT* playerPos, int missileNum);

	void FrameFunc();
	void RotateFlakes(int idx);
	void PrepareShotMissile(int idx);
	void MissileMove(int idx);

	vector<tagSnowFlake*> getVMissle() { return _vSnowFlakes; }
	
	void setJudgeRc(int idx, RECT rc) { _vSnowFlakes[idx]->rc = rc; }

};

