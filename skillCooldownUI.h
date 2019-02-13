#pragma once
#include "gameNode.h"
#include "skillIconList.h"
#include "printNumber.h";

//	�÷��̾ ž���ؼ� ������
//	init / update / render �ɾ������
//	�÷��̾�� ��ų�� �߰��Ǹ� == this->ChangeSkill(int �����(0~5)��ų, string ��ų�̸�, int �ִ���������, float ��ٿ� �ð� �Է�)
//	���� ����ũ�� curTime�� coolDownŸ���� ��. cooldownTime�� �Ѱ� �����Ǳ���� �ɸ��� �ð�, curTime �� 0~cooldownTime ��. (����ó�� ����)

//	*** ����ؼ� ��Ÿ�� ���ư����ִ� ��ų��, this->setCurTime(float ������ �ð�); ���� ���� ������Ʈ �ʿ�. ***		(�����ð���, ��Ÿ�ӽð����� �� ũ�Ե�����, �ڵ����� �����ð�0���� ������ٰ���)
//	***	������ �Ǿ�����,					  this->curReloadNum(int ������ ����); ���� ���� ������Ʈ �ʿ�. ***



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

		int totalReloadNum;		//�� ���� ����
		int curReloadNum;		//���� ���� ����
		float coolDownTime;		//��ٿ�ð� - ������ �ɸ��� �ѽð�
		float curTime;			//�������ۺ��� ���ݱ����� �ð�
		float lastingTime;		//���� �ð� = ��ٿ�ð� - ���ݱ����� �ð�

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

