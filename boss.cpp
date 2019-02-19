#include "stdafx.h"
#include "boss.h"
#include "player.h"
#include "boss_State_Sleep.h"
#include "boss_State_Idle.h"
#include "boss_State_Spawn.h"
#include "boss_State_Casting.h"
#include "boss_State_Mock.h"
#include "boss_State_Stun.h"
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
	KEYANIMANAGER->addArrayFrameAnimation("bossCasting", "boss", casting, 2, 2, false);

	//mock
	int mock[] = { 78,79,80,79,80,79,80,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("bossMock", "boss", mock, 9, 9, false);
	//조롱이 너무 길다거나 너무 짧으면 배열이랑 배열길이 수정하면됨.
	//조롱 끝나면 캐스팅 ㄱ

	//stun
	int stun[] = {66,67,68,67,68,67,68};
	KEYANIMANAGER->addArrayFrameAnimation("bossStun", "boss", stun, 7, 7, false);
	//조롱때 맞으면 스턴됨. 조롱과 똑같이 너무 길거나 짧으면 배열이랑 배열길이 수정

	//skill1 - 물방울 회전 던지기
	int skill1[] = { 22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill1", "boss", skill1, 21, 21, false);

	//skill2 - 눈송이 회전 많이 던지기

	//skill3 - 창 3개 날리기

	//skill4 - 돌진 얼음대거 돌리기

	//skill5 - 고드름비 내리기

	//death_start

	//death

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
	//_skillNum[_skill_Usage_Count] 에 맞는 스킬 사용하자

	_skill_Usage_Count += 1;
}
