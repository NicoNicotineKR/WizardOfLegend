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

	//보스의 중점좌표
	_vec.x = 0;
	_vec.y = 0;
	_pos.x = 0;
	_pos.y = 0;
	_rc = RectMakeCenter(_pos.x, _pos.y, COLLISION_WIDTH, COLLISION_HEIGHT);

	_maxHp = BOSS_HP;
	_curHp = BOSS_HP;

	_speed = 400.f;
	_angle = 0;
	_hitAngle = 0;

	_isAniOnce = false;
	_isArea = false;
	_isStun = false;
	_isDeath = false;
	_isSkillEnd = false;

	_state = B_STATE::SLEEP;
	_direction = NULL;

	_skill_Usage_Count = 0;
	skillShuffle();

	//스킬들
	_skill3 = new throwIceSpear;
	_skill3->init();
	_skill1 = new waterdropRotate;
	_skill1->init();
	_skill2 = new snowflakeRotate;
	_skill2->init();
	_skill4 = new chargeIceSlash;
	_skill4->init();

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		setBossSpawn();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		setBossMock();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		setBossDeath();
	}
	//스테이지에서 플레이어가 보스방의 전투구역을 밟게되면 셋으로 isClose true만들어줌
	if (_isArea)
	{
		_vec.x = 0;
		_vec.y = 0;

		_bossState->update(this);

		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			setBossStateCasting();
		}

		
		//스킬들 업데이트
		if (!_isSkillEnd)
		{
			_skill3->update();
			_skill1->update();
			_skill2->update();
			_skill4->update();
		}


		_playerPos.x = _player->getTileCheckRcPos().x + TOP_TILESIZE / 2;
		_playerPos.y = _player->getTileCheckRcPos().y + TOP_TILESIZE / 2;

		_pos.x += _vec.x;
		_pos.y += _vec.y;

		_rc = RectMakeCenter(_pos.x, _pos.y, COLLISION_WIDTH, COLLISION_HEIGHT);
	}
}

void boss::render()
{
	if (_isArea)
	{
		//char str[128];
		//sprintf_s(str, "보스체력 %d", _curHp);
		//TextOut(getMemDC(), 300, 300, str, strlen(str));
		//
		//sprintf_s(str, "보스상태 %d", _state);
		//TextOut(getMemDC(), 300, 350, str, strlen(str));

		_wingImg->aniRender(getMemDC(), (_pos.x - WING_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - WING_SHAVE_Y) - CAMERA2D->getCamPosY(), _wingAni);
		
		//스킬 렌더-------------------------------------------------------------------------------------------------
		
		if (!_isSkillEnd)
		{
			_skill3->render();
			_skill1->render();
			_skill2->render();
			_skill4->render();
		}
		//-------------------------------------------------------------------------------------------------
		
		
		_img->aniRender(getMemDC(), (_pos.x - IMG_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - IMG_SHAVE_Y) - CAMERA2D->getCamPosY(), _ani);
		//크리스탈 이미지는 보스 스폰때랑 죽을때밖에 안나옴
		if (_state == B_STATE::SPAWN || _state == B_STATE::DEATH)
		{
			_crystalImg->aniRender(getMemDC(), (_pos.x - CRYSTAL_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - CRYSTAL_SHAVE_Y) - CAMERA2D->getCamPosY(), _crystalAni);
		}
		//_crystalImg->aniRender(getMemDC(), (_pos.x - CRYSTAL_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - CRYSTAL_SHAVE_Y) - CAMERA2D->getCamPosY(), _crystalAni);
	}
	//쳐맞는 판정 렉트
	//Rectangle(getMemDC(), _rc);
	//중심 좌표 테스트용 출력
	//Rectangle(getMemDC(), _pos.x, _pos.y, _pos.x + 10, _pos.y + 10);
}

void boss::bossKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("boss", "images/boss/IceBoss.bmp", 1650, 2000, 11, 10, true, 0xff00ff);

	//sleep
	//이때는 그냥 상태만있고 이미지 없게하자. 즉 이미지 출력 안하면됨

	//spawn
	int spawn[] = { 85,85,85,85,85,85,85,62,63,64 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSpawn", "boss", spawn, 10, 4, false);
	//출력 다한후 idle로 가야함 ->
	//맨첨에 크리스탈 이랑 날개 생김.
	//크리스탈 완성되면 그뒤에 보스생김

	//idle
	int idle[] = { 88,89,90,91,92,93,94,95,96,97 };
	KEYANIMANAGER->addArrayFrameAnimation("bossIdle", "boss", idle, 10, 10, true);
	// 내상태가 idle이 되면 다이얼로그 시작(다이얼로그 시작조건에 내 상태 idle 넣음)
	// 다이얼로그를 종료하면 내상태를 캐스팅으로 바꿔줌(다이얼로그 종료할때 내상태 캐스팅으로 바꿈)

	//casting
	int casting[] = { 52,52,52,52,53,53,53,53 };
	KEYANIMANAGER->addArrayFrameAnimation("bossCasting", "boss", casting, 8, 4, false);

	//mock
	int mock[] = { 78,79,80,79,80,79,80,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("bossMock", "boss", mock, 9, 5, false);
	//조롱이 너무 길다거나 너무 짧으면 배열이랑 배열길이 수정하면됨.
	//조롱 끝나면 캐스팅 ㄱ

	//stun
	int stun[] = { 66,67,68,67,68,67,68,67,68,67,68,67,68 };
	KEYANIMANAGER->addArrayFrameAnimation("bossStun", "boss", stun, 13, 6, false);
	//조롱때 맞으면 스턴됨. 조롱과 똑같이 너무 길거나 짧으면 배열이랑 배열길이 수정

	//대쉬
	int rightDash[] = { 1,1,1,1,1,1,1,1 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightDash", "boss", rightDash, 8, 1, true);

	int leftDash[] = { 0,0,0,0,0,0,0,0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftDash", "boss", leftDash,81, 1, true);
	//대쉬는 플레이어가 있던 좌표를 저장해놓고 겟앵글해서 그좌표로 이동하고 도착하면 skill4실행

	//skill1 - 물방울 회전 던지기
	int skill1[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill1", "boss", skill1, 31, 5, false);

	//skill2 - 눈송이 회전 많이 던지기
	int skill2[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill2", "boss", skill2, 58, 10, false);

	//skill3 - 창 3개 날리기
	int skill3[] = { 14,14,15,15,16,16,17,17 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill3", "boss", skill3, 8, 4, false);

	//skill4 - 얼음대거 돌리기
	int rightSkill4[] = { 55, // 딜레이 필요
		56, 57, 58, 59, 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill4_Right", "boss", rightSkill4, 7, 7, false);

	int leftSkill4[] = { 99,
		100, 101, 102, 103, 104, 105 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill4_Left", "boss", leftSkill4, 7, 7, false);

	//skill5 - 고드름비 내리기
	int skill5[] = { 48,48,48,48,48,		//딜레이 주는거 필요
					49,49,49,49,49, };		//얘도
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill5", "boss", skill5, 10, 2, false);
	//death_start 69
	int deathStart[] = { 69 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDeathStart", "boss", deathStart, 1, 1, true);

	//death 87
	int death[] = { 87,87,87,87,87,86,86,86,86 };
	KEYANIMANAGER->addArrayFrameAnimation("bossDeath", "boss",death, 9, 3, false);

}

void boss::wingKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("bossWing", "images/boss/IceWings.bmp", 933, 400, 7, 4, true, 0xff00ff);

	//날개 펼치고 제자리 부양
	int idle[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("wingIdle", "bossWing", idle, 7, 7, true);

	//큰상태 - > 점점 작아짐
	int decrease[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("wingDecrease", "bossWing", decrease, 7, 7, false);

	//작은상태 -> 점점커짐 -> 아이들
	int increase[] = { 14,15,16,17,18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("wingIncrease", "bossWing", increase, 7, 7, false, wingIdle, this);

	int disappear[] = { 20,20,20,20,20,25,25,25,25 };
	KEYANIMANAGER->addArrayFrameAnimation("wingDisappear", "bossWing", disappear, 9, 3, false);
}

void boss::crystalKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("bossCrystal", "images/boss/IceCrystals.bmp", 550, 300, 5, 2, true, 0xff00ff);

	int crystal[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("crystal", "bossCrystal", crystal, 9, 3, false);
}

void boss::bossArrStateInit()
{
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

	if (_isAniOnce)
	{
		if (_state == B_STATE::SPAWN)
		{
			_ani = KEYANIMANAGER->findAnimation("bossSpawn");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingDecrease");
			_wingAni->start();

			_crystalAni = KEYANIMANAGER->findAnimation("crystal");
			_crystalAni->start();
		}
		if (_state == B_STATE::IDLE)
		{
			_ani = KEYANIMANAGER->findAnimation("bossIdle");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingIncrease");
			_wingAni->start();
		}
		if (_state == B_STATE::CASTING)
		{
			_ani = KEYANIMANAGER->findAnimation("bossCasting");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingDecrease");
			_wingAni->start();
		}
		if (_state == B_STATE::MOCK)
		{
			_ani = KEYANIMANAGER->findAnimation("bossMock");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingIncrease");
			_wingAni->start();
		}
		if (_state == B_STATE::STUN)
		{
			_ani = KEYANIMANAGER->findAnimation("bossStun");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingIncrease");
			_wingAni->start();
		}
		if (_state == B_STATE::DASH)
		{
			if (_playerPos.x <= _pos.x)
			{
				//애니메이션 왼쪽
				_ani = KEYANIMANAGER->findAnimation("bossLeftDash");
				_ani->start();
				_direction = DIRECTION_LEFT;
			}
			else if (_playerPos.x > _pos.x)
			{
				//애니메이션 오른쪽
				_ani = KEYANIMANAGER->findAnimation("bossRightDash");
				_ani->start();
				_direction = DIRECTION_RIGHT;
			}
		}
		if (_state == B_STATE::SKILL_ONE)
		{
			_ani = KEYANIMANAGER->findAnimation("bossSkill1");
			_ani->start();
		}
		if (_state == B_STATE::SKILL_TWO)
		{
			_ani = KEYANIMANAGER->findAnimation("bossSkill2");
			_ani->start();
		}
		if (_state == B_STATE::SKILL_THREE)
		{
			_ani = KEYANIMANAGER->findAnimation("bossSkill3");
			_ani->start();
		}
		if (_state == B_STATE::DEATH_START)
		{
			_ani = KEYANIMANAGER->findAnimation("bossDeathStart");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingIncrease");
			_wingAni->start();
		}
		if (_state == B_STATE::DEATH)
		{
			_ani = KEYANIMANAGER->findAnimation("bossDeath");
			_ani->start();

			_wingAni = KEYANIMANAGER->findAnimation("wingDisappear");
			_wingAni->start();

			_crystalAni = KEYANIMANAGER->findAnimation("crystal");
			_crystalAni->start();
		}
		_isAniOnce = false;
	}
}

void boss::wingIdle(void * obj)
{
	boss* _boss = (boss*)obj;

	_boss->setWingAniIdle();
	_boss->getWingAni()->start();
}

void boss::skillShuffle()
{
	_skillNum[0] = 3;
	_skillNum[1] = RND->getInt(3);


	//shuffle;
	//int destNum, sourNum;
	//int temp;
	//for (int i = 0; i < SHUFFLE_NUM; i++)
	//{
	//	destNum = RND->getInt(5);
	//	sourNum = RND->getInt(5);
	//
	//	if (destNum == sourNum) continue;
	//
	//	temp = _skillNum[destNum];
	//
	//	_skillNum[destNum] = _skillNum[sourNum];
	//	_skillNum[sourNum] = temp;
	//}
}

void boss::useSkill()
{
	if (_skill_Usage_Count <= 1)
	{
		switch (_skillNum[_skill_Usage_Count])
		{
		case 0: //물방울 회전 회오리
			_state = B_STATE::SKILL_ONE;
			_skill1->UseSkill(&_pos, &_playerPos, 10);
			break;
		case 1:	//눈송이 회전 회오리
			_state = B_STATE::SKILL_TWO;
			_skill2->UseSkill(&_pos, &_playerPos, 20);
			break;
		case 2: //창 3개 날리기
			_state = B_STATE::SKILL_THREE;
			_skill3->UseSkill(&_pos, &_playerPos, 5);
			break;
		case 3: //돌진
			_state = B_STATE::DASH;
			_skill4->UseSkill(&_pos, &_playerPos, 0);
			break;
		}

		_skill_Usage_Count += 1;
	}
	else if (_skill_Usage_Count >= 2)
	{
		//스킬 다쓰면 조롱
		
		SOUNDMANAGER->play("IceBossLaugh", OPTIONMANAGER->getSoundEffectVolume());

		_state = B_STATE::MOCK;
		_skill_Usage_Count = 0;
		skillShuffle();
	}
	//_skillNum[_skill_Usage_Count] 에 맞는 스킬 사용하자
	


}

void boss::setBossSpawn()
{
	_isArea = true;
	_state = B_STATE::SPAWN;
	bossCurrentState();
	_isAniOnce = true;
	startAni();
}

void boss::setBossMock()
{
	_state = B_STATE::MOCK;
	bossCurrentState();
	_isAniOnce = true;
	startAni();
}

void boss::setBossDeath()
{
	_state = B_STATE::DEATH;
	bossCurrentState();
	_isAniOnce = true;
	startAni();
}

void boss::setBossStateCasting()
{
	_state = B_STATE::CASTING;
	bossCurrentState();
	_isAniOnce = true;
	startAni();
}

void boss::RcCollideBySkillFunc(RECT * skillRc, int dmg, bool * isHit)
{
	RECT tmpRc;
	if ((_state != B_STATE::DEATH_START && _state != B_STATE::DEATH) && IntersectRect(&tmpRc, skillRc, &_rc))
	{
		//일단 피까고
		_curHp -= dmg;
		*isHit = true;
		if (!SOUNDMANAGER->isPlaySound("IceBossHurt"))
		{
			SOUNDMANAGER->play("IceBossHurt",OPTIONMANAGER->getSoundEffectVolume());
		}
		//모크 상태였으면
		if (_state == B_STATE::MOCK)
		{
			_isStun = true;
		}

		if (_curHp <= 0)
		{
			_isDeath = true;
			_isSkillEnd = true;
		}
	}
	if (*isHit)
	{
		*skillRc = { 0, 0, 0, 0 };
	}
}

void boss::DistanceBySkillFunc(POINTFLOAT skillPos, float range, int dmg, bool * isHit)
{
	RECT tmpRc;

	if ((_state != B_STATE::DEATH_START && _state != B_STATE::DEATH) && getDistance(_pos.x,_pos.y,skillPos.x,skillPos.y) < range)
	{
		//일단 피까고
		_curHp -= dmg;
		*isHit = true;
		//모크 상태였으면
		if (_state == B_STATE::MOCK)
		{
			_isStun = true;
		}

		if (_curHp <= 0)
		{
			_isDeath = true;
			_isSkillEnd = true;
		}
	}
}
