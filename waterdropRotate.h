#pragma once
#include "gameNode.h"

//	������ ��Ŭ����Ѵ�.
//	�ʿ��� ��� : POINTFLOAT���� &bossPos, &playerPos
//	�����
//	�̴��� ���ش�.
//	update(), render()�� �ɾ��ش�.
//	UseSkill();���� �۵��ϰ�, �����ð� �Ŀ� ������ �ʱ�ȭ�ȴ�.
//	��-


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

	float _prepareMissileTimer;		//	�ϳ� �����Ҷ����� �ð����ִ� Ÿ�̸�
	float _shootingMissileTimer;
	float _missleGenTime;			//	�ϳ� �����ϱ���� �ɸ��� �ð�
	float _totalSkillElapsedTime;
	

	int _frameCounter;
	float _rotateAngle;

	bool _isStart;
	bool _isRdyToShot;
	





	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;

	const int WATERDROP_SPD = 40;			//	���ư��� �ӵ�
	const int WATERDROP_WID = 60;			//	�ǵ������ÿ�
	const int JUDGE_RC_WID = 38;			//	������Ʈ ���μ���
	const float PREPARE_TIME = 0.5f;		//	������ �غ�ð�
	const int AUG_ALPHA = 60;				//	���������� ���� 255�Ǿ� ������ ��
	const float ROTATE_RAD = 150.0f;		//	ȸ��������
	const float ROTATE_ANGLE_SPD = PI / 64;		//	������ ���� �۾������� ������
	const float END_SKILTIME = 10.0f;		//	��ų ������ �ʱ�ȭ�Ǵ½ð�.
	const int FRAME_COUNTMAX = 10;		//	����� �̹��� ������ ���ϴ� ī����
	const float SHOOTINGSPD = 0.2f;		//	�߻�ӵ�(���ʸ���?)


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

