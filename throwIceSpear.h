#pragma once
#include "gameNode.h"
#include "rotateImgMaker.h"

//	��µ��� ������Ʈ �ɾ��� ��.
//	UseSkill(POINTFLOAT* bossPos, POINTFLOAT* playerPos, int spearNum); �� �ѹ��� ������. �������ִ°�
//					������ǥ �ּ�, �÷��̾���ǥ �ּ�, �� ���Ǿ� ����
//	init�� ��÷�� �ѹ� �ɾ��ְ�, update, render�� ��Ӱɾ��ְ�,
//	END_SKILLTIME�� �Ǹ�(����10��) ���� �ʱ�ȭ�ǰ� ���̻� �۵�����(update��, ������)
//	END_SKILLTIME �Ǳ����� ��ų �� ������.


class throwIceSpear :public gameNode
{
private:
	image* _iceSpearDefault;
	image* _iceSpearImg[36];
	
	struct tagIceSpear {
		image* img;					//	�����, �ǽð� set
		POINTFLOAT pos;				//	�����, �ѹ��� set
		POINT adjustPos;		//	���� �Ӹ� �� �߽ɿ��� �󸶳� �������ִ°�. ������ (â�� �������ϰ��)
		RECT rc;					//	�����, �ѹ��� set -> �� ��, ��� ����
		//POINTFLOAT judgePos[2];		//	�� �ѹ��� set, ����, ��� ����
		//RECT judgeRc[2];			//	�� �� ��� ����
		POINTFLOAT judgePos;
		RECT judgeRc;
		POINTFLOAT vec;				//	�� �ѹ��� set
		//	POINTFLOAT atkDestPos;		//	�� �ѹ��� set		//�Ⱦ�
		float angle;				//	�����, �ǽð� set
		int alpha;					//	�����, �ǽð� set
		
		//bool isOnceSetSpearPrepareValue;	//	�����, �ѹ��� �ʱ�ȭ���ִ°� üũ
		bool isOnceSetSpearShotValue;		//	��, �ѹ��� �ʱ�ȭ���ִ°� üũ
		//bool isShotPrepareEnd;
		
	};
	vector<tagIceSpear*> _iceSpear;
	//	float _spearTipLength;		�Ⱦ��ϴ�. SPEAR_TIP_LENGTH �� ��ü
	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;
	int _spearNum;

	float _prepareShotElapsedTime;
	float _totalSkillElapsedTime;


	float _augAlpha;
	

	bool _isStart;
	bool _isRdyToShot;


	const int SPEAR_MAXNUM = 20;			//	�ִ�� �� �� �ִ� â�� ����
	const float SPEAR_SPD = 35;				//	â�� ���󰡴� ���ǵ�
	const float SPEAR_TIP_LENGTH = 17.0f;	//	â���� ����(������Ʈ ������ ���)
	const double PREPARE_SHOTTIME = 1.5;	//	��������� ���ð�
	const int JUDGERC_WID = 25;				//	������Ʈ �Ѻ� ����
	

	const float END_SKILLTIME = 10.0f;		//	�ִ� ���ӽð� ��, �ð��ٵǸ� �ʱ�ȭ
	
	//	���� wid 150 / hei 200.

	rotateImgMaker* _imgMaker;
	
	

public:
	throwIceSpear();
	~throwIceSpear();

	HRESULT init();
	void release();
	void update();
	void render();

	void UseSkill(POINTFLOAT* bossPos, POINTFLOAT* playerPos, int spearNum);
	void SetSpearPrepareValue(int idx, POINTFLOAT playerPos, POINTFLOAT bossPos);
	void SetSpearShotValueOnce(int idx);
	void SetSpearShotValue(int idx);
	void ResetAll();



	void setIsStart(bool value) { _isStart = value; }
	bool getIsStart() { return _isStart; }

	vector<tagIceSpear*> getVMissle() { return _iceSpear; }
	//	set������Ʈ
	void setJudgeRc(int idx, RECT rc) { _iceSpear[idx]->rc = rc; }
	
};

