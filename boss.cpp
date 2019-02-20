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

	//������ ������ǥ
	_vec.x = 0;
	_vec.y = 0;
	_pos.x = WINSIZEX /2 - 200;
	_pos.y = WINSIZEY /2 - 200;
	_rc = RectMakeCenter(_pos.x, _pos.y, 150, 200);

	_maxHp = BOSS_HP;
	_curHp = BOSS_HP;

	_speed = 400.f;
	_angle = 0;
	_hitAngle = 0;

	_isAniOnce = false;
	_isArea = false;
	_isStun = false;
	_isDeath = false;

	_state = B_STATE::SLEEP;
	_direction = NULL;

	_skill_Usage_Count = 0;
	skillShuffle();

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	//������������ �÷��̾ �������� ���������� ��ԵǸ� ������ isClose true�������
	if (_isArea)
	{
		_vec.x = 0;
		_vec.y = 0;

		_bossState->update(this);

		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			setBossStateCasting();
		}




		_playerPos.x = _player->getTileCheckRcPos().x + TOP_TILESIZE / 2;
		_playerPos.y = _player->getTileCheckRcPos().y + TOP_TILESIZE / 2;

		_pos.x += _vec.x;
		_pos.y += _vec.y;
	}
}

void boss::render()
{
	if (_isArea)
	{
		_wingImg->aniRender(getMemDC(), (_pos.x - WING_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - WING_SHAVE_Y) - CAMERA2D->getCamPosY(), _wingAni);
		//ũ����Ż �̹����� ���� �������� �������ۿ� �ȳ���
		if (_state == B_STATE::SPAWN || _state == B_STATE::DEATH)
		{
			_crystalImg->aniRender(getMemDC(), (_pos.x - CRYSTAL_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - CRYSTAL_SHAVE_Y) - CAMERA2D->getCamPosY(), _crystalAni);
		}
		_img->aniRender(getMemDC(), (_pos.x - IMG_SHAVE_X) - CAMERA2D->getCamPosX(), (_pos.y - IMG_SHAVE_Y) - CAMERA2D->getCamPosY(), _ani);
	}
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
	KEYANIMANAGER->addArrayFrameAnimation("bossCasting", "boss", casting, 2, 2, false);

	//mock
	int mock[] = { 78,79,80,79,80,79,80,79,80 };
	KEYANIMANAGER->addArrayFrameAnimation("bossMock", "boss", mock, 9, 5, false);
	//������ �ʹ� ��ٰų� �ʹ� ª���� �迭�̶� �迭���� �����ϸ��.
	//���� ������ ĳ���� ��

	//stun
	int stun[] = { 66,67,68,67,68,67,68 };
	KEYANIMANAGER->addArrayFrameAnimation("bossStun", "boss", stun, 7, 7, false);
	//���ն� ������ ���ϵ�. ���հ� �Ȱ��� �ʹ� ��ų� ª���� �迭�̶� �迭���� ����

	//�뽬
	int rightDash[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("bossRightDash", "boss", rightDash, 1, 1, true);

	int leftDash[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bossLeftDash", "boss", leftDash, 1, 1, true);
	//�뽬�� �÷��̾ �ִ� ��ǥ�� �����س��� �پޱ��ؼ� ����ǥ�� �̵��ϰ� �����ϸ� skill4����

	//skill1 - ����� ȸ�� ������
	int skill1[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill1", "boss", skill1, 31, 5, false);

	//skill2 - ������ ȸ�� ���� ������
	int skill2[] = { 22,23,
					24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,24,25,26,27,28,29,30,31,32,
					33,34,35,36,37,38,39,40,41,42,42 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill2", "boss", skill2, 58, 10, false);

	//skill3 - â 3�� ������
	int skill3[] = { 14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill3", "boss", skill3, 4, 4, false);

	//skill4 - ������� ������
	int rightSkill4[] = { 55, // ������ �ʿ�
		56, 57, 58, 59, 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill4_Right", "boss", rightSkill4, 7, 7, false);

	int leftSkill4[] = { 99,
		100, 101, 102, 103, 104, 105 };
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill4_Left", "boss", leftSkill4, 7, 7, false);

	//skill5 - ��帧�� ������
	int skill5[] = { 48,48,48,48,48,		//������ �ִ°� �ʿ�
					49,49,49,49,49, };		//�굵
	KEYANIMANAGER->addArrayFrameAnimation("bossSkill5", "boss", skill5, 10, 2, false);
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

	//���� ��ġ�� ���ڸ� �ξ�
	int idle[] = { 0,1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("wingIdle", "bossWing", idle, 7, 7, true);

	//ū���� - > ���� �۾���
	int decrease[] = { 7,8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("wingDecrease", "bossWing", decrease, 7, 7, false);

	//�������� -> ����Ŀ�� -> ���̵�
	int increase[] = { 14,15,16,17,18,19,20 };
	KEYANIMANAGER->addArrayFrameAnimation("wingIncrease", "bossWing", increase, 7, 7, false, wingIdle, this);
}

void boss::crystalKeyAnimationInit()
{
	IMAGEMANAGER->addFrameImage("bossCrystal", "images/boss/IceCrystals.bmp", 550, 300, 5, 2, true, 0xff00ff);

	int crystal[] = { 0,1,2,3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("crystal", "bossCrystal", crystal, 9, 9, false);
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
				//�ִϸ��̼� ����
				_ani = KEYANIMANAGER->findAnimation("bossLeftDash");
				_ani->start();
				_direction = DIRECTION_LEFT;
			}
			else if (_playerPos.x > _pos.x)
			{
				//�ִϸ��̼� ������
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
		if (_state == B_STATE::SKILL_FOUR)
		{
			//�뽬���� ������ ������ �������̳� �����̳Ŀ� ���� �̹��� �¿찡�ٸ�
			if (_direction == DIRECTION_LEFT)
			{
				_ani = KEYANIMANAGER->findAnimation("bossSkill4_Left");
				_ani->start();
				_direction = NULL;
			}
			else if (_direction == DIRECTION_RIGHT)
			{
				_ani = KEYANIMANAGER->findAnimation("bossSkill4_Right");
				_ani->start();
				_direction = NULL;
			}
		}
		if (_state == B_STATE::SKILL_FIVE)
		{
			_ani = KEYANIMANAGER->findAnimation("bossSkill5");
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

			_wingAni = KEYANIMANAGER->findAnimation("wingDecrease");
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
	for (int i = 0; i < 5; i++)
	{
		_skillNum[i] = i;
	}

	//shuffle;
	int destNum, sourNum;
	int temp;
	for (int i = 0; i < SHUFFLE_NUM; i++)
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

void boss::setBossSpawn()
{
	_isArea = true;
	_state = B_STATE::CASTING;
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
