#pragma once
#include "gameNode.h"
#include "rotateImgMaker.h"
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
		POINTFLOAT judgePos[2];		//	�� �ѹ��� set, ����, ��� ����
		RECT judgeRc[2];			//	�� �� ��� ����
		POINTFLOAT vec;				//	�� �ѹ��� set
		//	POINTFLOAT atkDestPos;		//	�� �ѹ��� set		//�Ⱦ�
		float angle;				//	�����, �ǽð� set
		int alpha;					//	�����, �ǽð� set

		
	};
	vector<tagIceSpear*> _iceSpear;
	//	float _spearTipLength;		�Ⱦ��ϴ�. SPEAR_TIP_LENGTH �� ��ü
	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;
	int _spearNum;

	float _prepareShotElapsedTime;
	float _totalSkillElapsedTime;


	bool _isOnceSetSpearPrepareValue;	//	�����, �ѹ��� �ʱ�ȭ���ִ°� üũ
	bool _isOnceSetSpearShotValue;		//	��, �ѹ��� �ʱ�ȭ���ִ°� üũ
	bool _isShotPrepareEnd;


	bool _isStart;


	const int SPEAR_NUM = 3;
	const float SPEAR_SPD = 5;
	const float SPEAR_TIP_LENGTH = 17.0f;
	const float PREPARE_SHOTTIME = 3.0f;
	const int JUDGERC_WID = 17;
	const int AUG_ALPHA = 10;

	const float END_SKILLTIME = 10.0f;
	
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
	void SetSpearPrepareValueOnce(int idx, POINTFLOAT bossPos);
	void SetSpearPrepareValue(int idx, POINTFLOAT playerPos);
	void SetSpearShotValueOnce(int idx);
	void SetSpearShotValue(int idx);
	void ResetAll();



	void setIsStart(bool value) { _isStart = value; }
	bool getIsStart() { return _isStart; }

	
};

