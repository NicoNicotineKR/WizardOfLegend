#pragma once
#include "gameNode.h"
#include "skillIconList.h"
#include "printNumber.h"

//	����ũ�� ���ư��پƾƾƾƾƾ� �����������پƾƾƾ�
//	�÷��̾ ž���ؼ� ������
//	init / update / render �ɾ������
//	�÷��̾�� ��ų�� �߰��Ǹ� == this->ChangeSkill(int �����(0~5)��ų, string ��ų�̸�, int �ִ���������, float ��ٿ� �ð� �Է�) - �ּҳ־��ּ�
//	��. cooldownTime�� �Ѱ� �����Ǳ���� �ɸ��� �ð�, curTime �� 0~cooldownTime ��. 

//	�÷��̾��� ��뿹�ô� ������Ʈ �׽�Ʈ�� �ڵ� num8 �������� �߻��ϴ°� ���� ��.



//	1ȸ �̻� ������ ��ų�� ���� ������ �������


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

		int* totalReloadNum;		//�� ���� ����
		int* curReloadNum;			//���� ���� ����
		float* coolDownTime;		//��ٿ�ð� - ������ �ɸ��� �ѽð�
		float* curTime;				//�������ۺ��� ���ݱ����� �ð�
		float lastingTime;			//���� �ð� = ��ٿ�ð� - ���ݱ����� �ð�
		int saveReloadNum;

		bool isStart;
		bool isPrepareBlt;

		float curMaskWid;
		float lastTimeRatio;
		float curTimeRatio;
		float proceedRatio;		//	�����Ӵ� ����� ����

		

		
		float angle;
		float preAngle;
		POINT polygonPos[3];	//	����, �����ޱ� ��ǥ, ����ޱ� ����ǥ

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

	//	�׽�Ʈ�� ����
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

	//	���° ��ų, ����Ÿ�̸��� �ּ�, ���� ������ �Ѿ˼�(�����)
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

