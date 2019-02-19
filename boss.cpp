#include "stdafx.h"
#include "boss.h"
#include "player.h"
#include "boss_State_Sleep.h"
#include "boss_State_Idle.h"
#include "boss_State_Spawn.h"
#include "boss_State_Casting.h"
#include "boss_State_Mock.h"
#include "boss_State_Stun.h"
#include "boss_State_Dash.h"
#include "boss_State_SKILL_One.h"
#include "boss_State_SKILL_Two.h"
#include "boss_State_SKILL_Three.h"
#include "boss_State_SKILL_Four.h"
#include "boss_State_SKILL_Five.h"
#include "boss_State_Death_Start.h"
#include "boss_State_Death.h"

boss::boss()
{
}


boss::~boss()
{
}

HRESULT boss::init()
{
	bossKeyAnimationInit();
	bossArrStateInit();

	_img = IMAGEMANAGER->findImage("boss");
	_ani = KEYANIMANAGER->findAnimation("bossSpawn");


	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
}

void boss::render()
{
}

void boss::bossKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("boss", "images/boss/IceBoss.bmp", 1650, 2000, 11, 10, true, 0xff00ff);

	//sleep
	//�̶��� �׳� ���¸��ְ� �̹��� ��������. �� �̹��� ��� ���ϸ��

	//spawn
	int spawn[] = { 62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSpawn", "boss", spawn, 3, 3, false);
	//��� ������ idle�� ������ ->
	//��÷�� ũ����Ż �̶� ���� ����.
	//ũ����Ż �ϼ��Ǹ� �׵ڿ� ��������

	//idle
	int idle[] = { 88,89,90,91,92,93,94,95,96,97 };
	KEYANIMANAGER->addArrayFrameAnimation("bossIdle", "boss", idle, 10, 10, true);
	// �����°� idle�� �Ǹ� ���̾�α� ����(���̾�α� �������ǿ� �� ���� idle ����)
	// ���̾�α׸� �����ϸ� �����¸� ĳ�������� �ٲ���(���̾�α� �����Ҷ� ������ ĳ�������� �ٲ�)

	//casting
	int casting[] = { 52,53 };
	KEYANIMANAGER->addArrayFrameAnimation("bossCasting", "boss", casting, 2, 2, false, skillUse,this);

	//mock
	int mock[] = { 78,79,80,79,80,79,80,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("bossMock", "boss", mock, 9, 9, false, skillUse, this);
	//������ �ʹ� ��ٰų� �ʹ� ª���� �迭�̶� �迭���� �����ϸ��.
	//���� ������ ĳ���� ��

	//stun
	int stun[] = {66,67,68,67,68,67,68};
	KEYANIMANAGER->addArrayFrameAnimation("bossStun", "boss", stun, 7, 7, false, skillUse, this);
	//���ն� ������ ���ϵ�. ���հ� �Ȱ��� �ʹ� ��ų� ª���� �迭�̶� �迭���� ����

	//skill1 - ����� ȸ�� ������
	int skill1[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42};
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill1", "boss", skill1, 31, 31, false, skillUse, this);

	//skill2 - ������ ȸ�� ���� ������
	int skill2[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill2", "boss", skill2, 58, 58, false, skillUse, this);

	//skill3 - â 3�� ������

	//skill4 - ������� ������
	//int dash

	//skill5 - ��帧�� ������

	//death_start

	//death

}

void boss::bossArrStateInit()
{
	//���� �߰�����
	_arrState[static_cast<const int>(B_STATE::SLEEP)] = new boss_State_Sleep;
	_arrState[static_cast<const int>(B_STATE::IDLE)] = new boss_State_Idle;
	_arrState[static_cast<const int>(B_STATE::SPAWN)] = new boss_State_Spawn;
	_arrState[static_cast<const int>(B_STATE::CASTING)] = new boss_State_Casting;
	_arrState[static_cast<const int>(B_STATE::MOCK)] = new boss_State_Mock;
	_arrState[static_cast<const int>(B_STATE::STUN)] = new boss_State_Stun;
	_arrState[static_cast<const int>(B_STATE::DASH)] = new boss_State_Dash;
	_arrState[static_cast<const int>(B_STATE::SKILL_ONE)] = new boss_State_SKILL_One;
	_arrState[static_cast<const int>(B_STATE::SKILL_TWO)] = new boss_State_SKILL_Two;
	_arrState[static_cast<const int>(B_STATE::SKILL_THREE)] = new boss_State_SKILL_Three;
	_arrState[static_cast<const int>(B_STATE::SKILL_FOUR)] = new boss_State_SKILL_Four;
	_arrState[static_cast<const int>(B_STATE::SKILL_FIVE)] = new boss_State_SKILL_Five;
	_arrState[static_cast<const int>(B_STATE::DEATH_START)] = new boss_State_Death_Start;
	_arrState[static_cast<const int>(B_STATE::DEATH)] = new boss_State_Death;

	_bossState = _arrState[static_cast<const int>(B_STATE::IDLE)];
	//���� ->
	//��ó���� ���� -> 
	//�����ִϸ��̼� ������ѵ� IDLE + dialogue -> 
	//dialogue������ 
	// -------------------------------------------------
	// 1. ĳ����(�� �ֵθ���)-> 
	// 2. ��ų 3����(��ų���� ��Ǵٸ�) ->
	// 3. ���� ->
	// 4-1. ���ջ��¿��� ������ ���� �� ĳ���� -> 1������
	// 4-2. �ȸ����� ���սð����� �����ѵ� ĳ���� -> 1������
	// -------------------------------------------------
	// ���� ü�� ��� ������
	// ���� ��ŸƮ(�����ݰ� �ɾƼ� ���̾�α� ���)
	// ���̾�α� ����� ->
	// ���� �ִϸ��̼� ���(���� �ǰ� �����°�)
	// -> ��
}

void boss::bossCurrentState()
{
	switch (_state)
	{
		_bossState->update(this);
		case B_STATE::SLEEP:
			_bossState = _arrState[static_cast<const int>(B_STATE::SLEEP)];
		break;
		case B_STATE::IDLE:
			_bossState = _arrState[static_cast<const int>(B_STATE::IDLE)];
		break;
		case B_STATE::SPAWN:
			_bossState = _arrState[static_cast<const int>(B_STATE::SPAWN)];
		break;
		case B_STATE::CASTING:
			_bossState = _arrState[static_cast<const int>(B_STATE::CASTING)];
		break;
		case B_STATE::MOCK:
			_bossState = _arrState[static_cast<const int>(B_STATE::MOCK)];
		break;
		case B_STATE::STUN:
			_bossState = _arrState[static_cast<const int>(B_STATE::STUN)];
		break;
		case B_STATE::DASH:
			_bossState = _arrState[static_cast<const int>(B_STATE::DASH)];
		break;
		case B_STATE::SKILL_ONE:
			_bossState = _arrState[static_cast<const int>(B_STATE::SKILL_ONE)];
		break;
		case B_STATE::SKILL_TWO:
			_bossState = _arrState[static_cast<const int>(B_STATE::SKILL_TWO)];
		break;
		case B_STATE::SKILL_THREE:
			_bossState = _arrState[static_cast<const int>(B_STATE::SKILL_THREE)];
		break;
		case B_STATE::SKILL_FOUR:
			_bossState = _arrState[static_cast<const int>(B_STATE::SKILL_FOUR)];
		break;
		case B_STATE::SKILL_FIVE:
			_bossState = _arrState[static_cast<const int>(B_STATE::SKILL_FIVE)];
		break;
		case B_STATE::DEATH_START:
			_bossState = _arrState[static_cast<const int>(B_STATE::DEATH_START)];
		break;
		case B_STATE::DEATH:
			_bossState = _arrState[static_cast<const int>(B_STATE::DEATH)];
		break;
	}
}

void boss::startAni()
{
}

void boss::skillUse(void * obj)
{
	boss* _boss = (boss*)obj;

	_boss->useSkill();
	_boss->bossCurrentState();
	_boss->setIsAniOnce(true);
	_boss->startAni();
}

void boss::skillShuffle()
{
	for (int i = 0; i < 5; i++)
	{
		_skillNum[i] = i;
	}

	//shuffle;
	int destNum, sourNum;
	int temp;
	for (int i = 0; i < 30; i++)
	{
		destNum = RND->getInt(5);
		sourNum = RND->getInt(5);

		if (destNum == sourNum) continue;

		temp = _skillNum[destNum];

		_skillNum[destNum] = _skillNum[sourNum];
		_skillNum[sourNum] = temp;
	}
}

void boss::useSkill()
{
	if (_skill_Usage_Count <= 2)
	{
		switch (_skillNum[_skill_Usage_Count])
		{
		case 0: //����� ȸ�� ȸ����
			_state = B_STATE::SKILL_ONE;
			break;
		case 1:	//������ ȸ�� ȸ����
			_state = B_STATE::SKILL_TWO;
			break;
		case 2: //â 3�� ������
			_state = B_STATE::SKILL_THREE;
			break;
		case 3: //����(�����ϸ� ����Į����)
			_state = B_STATE::DASH;
			break;
		case 4: //��帧 �����
			_state = B_STATE::SKILL_FIVE;
			break;
		}

		_skill_Usage_Count += 1;
	}
	else if (_skill_Usage_Count >= 3)
	{
		//��ų �پ��� ����
		_state = B_STATE::MOCK;
		_skill_Usage_Count = 0;
		skillShuffle();
	}
	//_skillNum[_skill_Usage_Count] �� �´� ��ų �������
	


}
