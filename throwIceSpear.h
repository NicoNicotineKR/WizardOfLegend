#pragma once
#include "gameNode.h"
#include "rotateImgMaker.h"
class throwIceSpear :public gameNode
{
private:
	image* _iceSpearDefault;
	image* _iceSpearImg[36];
	
	struct tagIceSpear {
		image* img;					//	쏘기전, 실시간 set
		POINTFLOAT pos;				//	쏘기전, 한번만 set
		POINT adjustPos;		//	보스 머리 위 중심에서 얼마나 떨어져있는가. 보정용 (창이 여러개일경우)
		RECT rc;					//	쏘기전, 한번만 set -> 쏜 후, 계속 갱신
		POINTFLOAT judgePos[2];		//	쏠때 한번만 set, 쏜후, 계속 갱신
		RECT judgeRc[2];			//	쏜 후 계속 갱신
		POINTFLOAT vec;				//	쏠때 한번만 set
		//	POINTFLOAT atkDestPos;		//	쏠때 한번만 set		//안씀
		float angle;				//	쏘기전, 실시간 set
		int alpha;					//	쏘기전, 실시간 set

		
	};
	vector<tagIceSpear*> _iceSpear;
	//	float _spearTipLength;		안씀니다. SPEAR_TIP_LENGTH 로 교체
	POINTFLOAT* _bossPos;
	POINTFLOAT* _playerPos;
	int _spearNum;

	float _prepareShotElapsedTime;
	float _totalSkillElapsedTime;


	bool _isOnceSetSpearPrepareValue;	//	쏘기전, 한번만 초기화해주는거 체크
	bool _isOnceSetSpearShotValue;		//	쏠때, 한번만 초기화해주는거 체크
	bool _isShotPrepareEnd;


	bool _isStart;


	const int SPEAR_NUM = 3;
	const float SPEAR_SPD = 5;
	const float SPEAR_TIP_LENGTH = 17.0f;
	const float PREPARE_SHOTTIME = 3.0f;
	const int JUDGERC_WID = 17;
	const int AUG_ALPHA = 10;

	const float END_SKILLTIME = 10.0f;
	
	//	보스 wid 150 / hei 200.




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

