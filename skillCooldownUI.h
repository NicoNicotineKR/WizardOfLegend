#pragma once
#include "gameNode.h"
#include "skillIconList.h"
#include "printNumber.h"

//	마스크가 돌아간다아아아아아아 오오오오돈다아아아아
//	플레이어에 탑재해서 쓰세여
//	init / update / render 걸어줘야함
//	플레이어에게 스킬이 추가되면 == this->ChangeSkill(int 몇번쨰(0~5)스킬, string 스킬이름, int 최대장전갯수, float 쿨다운 시간 입력) - 주소넣어주셈
//	ㅁ. cooldownTime은 한개 장전되기까지 걸리는 시간, curTime 은 0~cooldownTime 임. 

//	플레이어의 사용예시는 업데이트 테스트용 코드 num8 눌렀을떄 발생하는걸 보면 됨.



//	1회 이상 장전된 스킬은 장전 갯수를 출력해줌


class skillCooldownUI : public gameNode
{
private:
	struct tagSkillUI {
		string name;
		POINT pos;

		image* borderImg;
		RECT borderRc;
		
		image* iconImg;
		RECT iconRc;
		

		image* maskImg;
		image* maskImgDefault;

		int* totalReloadNum;		//총 장전 갯수
		int* curReloadNum;			//현재 장전 갯수
		float* coolDownTime;		//쿨다운시간 - 장전에 걸리는 총시간
		float* curTime;				//장전시작부터 지금까지의 시간
		float lastingTime;			//남은 시간 = 쿨다운시간 - 지금까지의 시간
		int saveReloadNum;

		bool isStart;
		bool isPrepareBlt;

		float curMaskWid;
		float lastTimeRatio;
		float curTimeRatio;
		float proceedRatio;		//	프레임당 진행된 비율

		

		
		float angle;
		float preAngle;
		POINT polygonPos[3];	//	중점, 이전앵글 좌표, 현재앵글 끝좌표

		int maskAlpha;
		bool _isBasicAtk;

	};

	skillIconList* _iconList;
	printNumber* _printNum;

	tagSkillUI _skills[6];

	image* _maskQuarter[3];

	
	const int BORDER_SIZE = 60;
	const int BORDER_ALPHA = 180;
	const int MASK_ALPHA = 150;
	const float MASK_MAX_WID = 60;
	const int ICONSTART_X = 39 + 30;
	const int ICONSTART_Y = 810 + 30;
	const int ICONGAB = 60 + 4;

	//	테스트용 변수
	/*
	int testTotalReloadNum = 9;
	int testCurReloadNum = 0;
	float testCoolDownTime = 9.0f;
	float testTimer = 0;
	bool testIsUse = false;
	*/
	

public:
	skillCooldownUI();
	~skillCooldownUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void ChangeSkill(int idx, string name, int* totalReloadedNum, int* curReloadNum, float* coolDownTime, float* curTime);
	void DropSkill(int idx);
	float CalLastingTime(int idx);
	float CalLastTimeRatio(int idx);
	float CalCurTimeRatio(int idx);
	float CalProceedRatio(int idx);
	float CalMaskWid(int idx);
	

	void BitBltMask(HDC destHDC, HDC sourHDC);
	void BitBltMask(int idx);
	void BitBltQuarterMask(int idx, int quarter);
	void ClockwiseMaskFunc(int idx);
	//void PartialClockwiseFunc(int idx);

	//	몇번째 스킬, 장전타이머의 주소, 현재 장전된 총알수(사용전)
	void UseIdxSkill(int idx);
	
	


	void setTotalReloadNum(int idx, int num)			{ *(_skills[idx].totalReloadNum) = num; }
	void setCurReloadNum(int idx, int num)				{ *(_skills[idx].curReloadNum) = num; }
	void setCoolDownTime(int idx, float cooldownTime)	{ *(_skills[idx].coolDownTime) = cooldownTime; }
	void setCurTime(int idx, float curTime)				{ *(_skills[idx].curTime) = curTime; }
	void setIsStart(int idx, bool value)				{ _skills[idx].isStart = value; }

	bool getIsStart(int idx) { return _skills[idx].isStart; }

	void setAddressTotalReload(int idx, int* totalReloadAddr) { _skills[idx].totalReloadNum = totalReloadAddr; }
	void setAddressCurReload(int idx, int* curReloadAddr) { _skills[idx].curReloadNum = curReloadAddr; }
	void setAddressCoolDownTime(int idx, float* cooldownTimeAddr) { _skills[idx].coolDownTime = cooldownTimeAddr; }
	void setAddressCurtime(int idx, float* curTimeAddr) { _skills[idx].curTime = curTimeAddr; }
};

