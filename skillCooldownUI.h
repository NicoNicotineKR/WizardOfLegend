#pragma once
#include "gameNode.h"
#include "skillIconList.h"
#include "printNumber.h";

//	플레이어에 탑재해서 쓰세여
//	init / update / render 걸어줘야함
//	플레이어에게 스킬이 추가되면 == this->ChangeSkill(int 몇번쨰(0~5)스킬, string 스킬이름, int 최대장전갯수, float 쿨다운 시간 입력)
//	검정 마스크는 curTime과 coolDown타임을 비교. cooldownTime은 한개 장전되기까지 걸리는 시간, curTime 은 0~cooldownTime 임. (예외처리 다함)

//	*** 사용해서 쿨타임 돌아가고있는 스킬은, this->setCurTime(float 장전한 시간); 으로 개별 업데이트 필요. ***		(지난시간이, 쿨타임시간보다 더 크게됐으면, 자동으로 남은시간0으로 계산해줄거임)
//	***	장전이 되었으면,					  this->curReloadNum(int 장전한 갯수); 으로 개별 업데이트 필요. ***



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

		int totalReloadNum;		//총 장전 갯수
		int curReloadNum;		//현재 장전 갯수
		float coolDownTime;		//쿨다운시간 - 장전에 걸리는 총시간
		float curTime;			//장전시작부터 지금까지의 시간
		float lastingTime;		//남은 시간 = 쿨다운시간 - 지금까지의 시간

		float curMaskWid;

	};

	skillIconList* _iconList;
	printNumber* _printNum;

	tagSkillUI _skills[6];

	
	const int BORDER_SIZE = 60;
	const int BORDER_ALPHA = 180;
	const int MASK_ALPHA = 150;
	const float MASK_MAX_WID = 60;
	const int ICONSTART_X = 39 + 30;
	const int ICONSTART_Y = 810 + 30;
	const int ICONGAB = 60 + 4;
	

public:
	skillCooldownUI();
	~skillCooldownUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void ChangeSkill(int idx, string name, int totalReloadedNum, float coolDownTime);
	void DropSkill(int idx);
	float CalLastingTime(int idx);
	float CalMaskWid(int idx);


	void setTotalReloadNum(int idx, int num)			{ _skills[idx].totalReloadNum = num; }
	void setCurReloadNum(int idx, int num)				{ _skills[idx].curReloadNum = num; }
	void setCoolDownTime(int idx, float cooldownTime)	{ _skills[idx].coolDownTime = cooldownTime; }
	void setCurTime(int idx, float curTime)				{ _skills[idx].curTime = curTime; }
	
	

};

