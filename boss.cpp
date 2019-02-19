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
	wingKeyAnimationInit();
	crystalKeyAnimationInit();

	_img = IMAGEMANAGER->findImage("boss");
	_ani = KEYANIMANAGER->findAnimation("bossSpawn");
	_wingImg = IMAGEMANAGER->findImage("bossWing");
	_wingAni = KEYANIMANAGER->findAnimation("wingDecrease");
	_crystalImg = IMAGEMANAGER->findImage("bossCrystal");
	_crystalAni = KEYANIMANAGER->findAnimation("crystal");

	_maxHp = BOSS_HP;
	_curHp = BOSS_HP;

	_speed = 400.f;
	_angle = 0;

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
	//이때는 그냥 상태만있고 이미지 없게하자. 즉 이미지 출력 안하면됨

	//spawn
	int spawn[] = { 62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSpawn", "boss", spawn, 3, 3, false);
	//출력 다한후 idle로 가야함 ->
	//맨첨에 크리스탈 이랑 날개 생김.
	//크리스탈 완성되면 그뒤에 보스생김

	//idle
	int idle[] = { 88,89,90,91,92,93,94,95,96,97 };
	KEYANIMANAGER->addArrayFrameAnimation("bossIdle", "boss", idle, 10, 10, true);
	// 내상태가 idle이 되면 다이얼로그 시작(다이얼로그 시작조건에 내 상태 idle 넣음)
	// 다이얼로그를 종료하면 내상태를 캐스팅으로 바꿔줌(다이얼로그 종료할때 내상태 캐스팅으로 바꿈)

	//casting
	int casting[] = { 52,53 };
	KEYANIMANAGER->addArrayFrameAnimation("bossCasting", "boss", casting, 2, 2, false, skillUse, this);

	//mock
	int mock[] = { 78,79,80,79,80,79,80,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("bossMock", "boss", mock, 9, 9, false, skillUse, this);
	//조롱이 너무 길다거나 너무 짧으면 배열이랑 배열길이 수정하면됨.
	//조롱 끝나면 캐스팅 ㄱ

	//stun
	int stun[] = { 66,67,68,67,68,67,68 };
	KEYANIMANAGER->addArrayFrameAnimation("bossStun", "boss", stun, 7, 7, false, skillUse, this);
	//조롱때 맞으면 스턴됨. 조롱과 똑같이 너무 길거나 짧으면 배열이랑 배열길이 수정

	//대쉬
	int rightDash[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightDash", "boss", rightDash, 1, 1, true);

	int leftDash[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftDash", "boss", leftDash, 1, 1, true);
	//대쉬는 플레이어가 있던 좌표를 저장해놓고 겟앵글해서 그좌표로 이동하고 도착하면 skill4실행

	//skill1 - 물방울 회전 던지기
	int skill1[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill1", "boss", skill1, 31, 31, false, skillUse, this);

	//skill2 - 눈송이 회전 많이 던지기
	int skill2[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill2", "boss", skill2, 58, 58, false, skillUse, this);

	//skill3 - 창 3개 날리기
	int skill3[] = { 14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill3", "boss", skill3, 4, 4, false, skillUse, this);

	//skill4 - 얼음대거 돌리기
	int rightSkill4[] = { 55, // 딜레이 필요
		56, 57, 58, 59, 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightSkill4", "boss", rightSkill4, 7, 7, false, skillUse, this);

	int leftSkill4[] = { 99,
		100, 101, 102, 103, 104, 105 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftSkill4", "boss", leftSkill4, 7, 7, false, skillUse, this);

	//skill5 - 고드름비 내리기
	int skill5[] = { 48,48,48,48,48,		//딜레이 주는거 필요
					49,49,49,49,49, };		//얘도
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill5", "boss", skill5, 10, 10, false, skillUse, this);
	//death_start 69
	int deathStart[] = { 69 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDeathStart", "boss", deathStart, 1, 1, true);

	//death 87
	int death[] = { 87 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDeath", "boss",death, 1, 1, true);

}

void boss::wingKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("bossWing", "images/boss/IceWings.bmp", 933, 400, 7, 4, true, 0xff00ff);

	//날개 펼치고 제자리 부양
	int idle[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("wingIdle", "bossWing", idle, 7, 7, true);

	int decrease[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("wingDecrease", "bossWing", decrease, 7, 7, false);

	int increase[] = { 14,15,16,17,18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("wingIncrease", "bossWing", increase, 7, 7, false);
}

void boss::crystalKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("bossCrystal", "images/boss/IceCrystal.bmp", 550, 300, 5, 2, true, 0xff00ff);

	int crystal[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("crystal", "bosssCrystal", crystal, 9, 9, false);
}

void boss::bossArrStateInit()
{
	//슬립 추가하자
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
	//슬립 ->
	//근처오면 스폰 -> 
	//스폰애니메이션 다출력한뒤 IDLE + dialogue -> 
	//dialogue끝나면 
	// -------------------------------------------------
	// 1. 캐스팅(손 휘두르기)-> 
	// 2. 스킬 3개씀(스킬마다 모션다름) ->
	// 3. 조롱 ->
	// 4-1. 조롱상태에서 맞으면 스턴 후 캐스팅 -> 1번으로
	// 4-2. 안맞으면 조롱시간동안 조롱한뒤 캐스팅 -> 1번으로
	// -------------------------------------------------
	// 보스 체력 모두 소진시
	// 데스 스타트(무릎꿇고 앉아서 다이얼로그 출력)
	// 다이얼로그 종료시 ->
	// 데스 애니메이션 출력(얼음 되고 깨지는거)
	// -> 끗
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
		case 0: //물방울 회전 회오리
			_state = B_STATE::SKILL_ONE;
			break;
		case 1:	//눈송이 회전 회오리
			_state = B_STATE::SKILL_TWO;
			break;
		case 2: //창 3개 날리기
			_state = B_STATE::SKILL_THREE;
			break;
		case 3: //돌진(도착하면 얼음칼돌림)
			_state = B_STATE::DASH;
			break;
		case 4: //고드름 비오기
			_state = B_STATE::SKILL_FIVE;
			break;
		}

		_skill_Usage_Count += 1;
	}
	else if (_skill_Usage_Count >= 3)
	{
		//스킬 다쓰면 조롱
		_state = B_STATE::MOCK;
		_skill_Usage_Count = 0;
		skillShuffle();
	}
	//_skillNum[_skill_Usage_Count] 에 맞는 스킬 사용하자
	


}
