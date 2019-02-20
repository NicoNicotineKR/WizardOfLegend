#include "stdafx.h"
#include "npc_SpellBook.h"


npc_SpellBook::npc_SpellBook()
{
}


npc_SpellBook::~npc_SpellBook()
{
}

HRESULT npc_SpellBook::init()
{
	npc::init();
	//ù����

	/*
	0.���ʰ�����								y�� = 1 // 3											( 8 )
	1.�����ʰ�����							y�� = 0 // 0											( 0 )

	2.���ʿ��� ���� �Թ����� ����				y�� = 1 // 3 2 , y�� = 2 // 0 , y�� = 1 // 2 3		( 8 , 10 , 7 , 8 )
	3.�����ʿ��� �����ι� ��ڰŸ��� ����		y�� = 0 // 0 1 2 3 2 1 2 3 2 1 0						( 0 , 1 , 2 , 3 , 2 , 1 , 2 , 3 , 2 , 1 , 0 )
	4.���ʿ��� ���������� ���� �ٲٴ� ����     y�� = 1 // 0 1 2 3									( 5 , 6 , 7 , 8 )
	5.�����ʿ��� �������� ���� �ٲٴ� ����		y�� = 1 // 2 1 0 , y�� = 0 // 0						( 7 , 6 , 5 , 0 )

	6.���ʿ��� å�� ��ġ����������				y�� = 1 // 3, y�� = 2 // 1 2 3 4, y�� = 3 // 0		( 8 , 11 , 12 , 13 , 14 , 15 )
	7.�����ʿ��� ��ġ����������				y�� = 0 // 0 , y�� = 2 // 1 2 3 4 , y�� = 3 // 0		( 0 , 11 , 12 , 13 , 14 , 15 )

	8.��ҽ� �������ڼ��� ���ư�				y�� 3 // 0 , y�� = 2 // 4 3 2 1 , y�� = 0 // 0		( 15 , 14 , 13 , 12 , 11 , 0 )

	9.å������								y�� = 3 // 0 1 2 3,	y�� = 4 // 0						( 15 , 16 , 17 , 18, 20 )
	*/

	IMAGEMANAGER->addFrameImage("spellBook", "images/npc/spellBook.bmp", 640, 640, 5, 5, true, 0xff00ff);

	_img = IMAGEMANAGER->findImage("spellBook");

	IMAGEMANAGER->addImage("speelBookFace", "images/npc/speelBookFace.bmp", 188, 189, true, 0xff00ff);
	_npcFaceImg = IMAGEMANAGER->findImage("speelBookFace");
	_npcFaceText = "�÷ѷѷѷηѤ�";

	int idle_L[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_Idle_L", "spellBook", idle_L, 1, 10, false);

	int idle_R[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_Idle_R", "spellBook", idle_R, 1, 10, false);

	int idle_Change_L[] = { 0 , 6 , 8 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_idle_Change_L", "spellBook", idle_Change_L, 3, 10, false, idleL, this);

	int idle_Change_R[] = { 8 , 6 , 0 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_idle_Change_R", "spellBook", idle_Change_R, 3, 10, false, idleR, this);

	int idle_Act1[] = { 8 , 10 , 7 , 8 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_Idle_Act1", "spellBook", idle_Act1, 4, 10, false, idleL, this);

	int idle_Act2[] = { 0 , 1 , 2 , 3 , 2 , 1 , 2 , 3 , 2 , 1 , 0 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_Idle_Act2", "spellBook", idle_Act2, 10, 10, false, idleR, this);

	int idle_L_ui1Start[] = { 8 , 6 , 11 , 12 , 13 , 14 , 15 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_Idle_L_Talk", "spellBook", idle_L_ui1Start, 7, 10, false, ui1, this);

	int idle_R_ui1Start[] = { 0 , 6 , 11 , 12 , 13 , 14 , 15 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_Idle_R_Talk", "spellBook", idle_R_ui1Start, 7, 10, false, ui1, this);

	int ui1_Esc[] = { 15 , 14 , 13 , 12 ,6 , 0 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_ui1_Esc", "spellBook", ui1_Esc, 5, 10, false, idleR, this);

	int ui2_Start[] = { 15 , 16 , 17 , 18 , 20 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_ui2_Start", "spellBook", ui2_Start, 5, 10, false);

	int ui2_Esc[] = { 20 , 18 , 17 , 16 , 15 };
	KEYANIMANAGER->addArrayFrameAnimation("spellBook_ui2_Esc", "spellBook", ui2_Esc, 5, 10, false, ui1, this);

	_state = stateNpc::IDLE_L;
	_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_L");

	_pos.x = 200;
	_pos.y = 200;




	return S_OK;
}

void npc_SpellBook::release()
{
}

void npc_SpellBook::update()
{
	npc::update();

	//1. �������ִ� ���� �����϶�
	if (_state == stateNpc::IDLE_L)
	{
		_idleCount += TIMEMANAGER->getElapsedTime();

		//1�ʸ���
		if (_idleCount >= 2)
		{
			_idleCount = 0;

			int RndNumber;
			RndNumber = RND->getFromIntTo(0, 2);

			if (RndNumber == 0)
			{
				_state = stateNpc::IDLE_CHANGE_R;
				isOnceAniPlay(_state);
			}
			if (RndNumber == 1)
			{
				_state = stateNpc::IDLE_ACT1;
				isOnceAniPlay(_state);
			}
		}
	}

	//2. �������ִ� ������ �����϶�
	if (_state == stateNpc::IDLE_R)
	{
		_idleCount += TIMEMANAGER->getElapsedTime();
		//100�ʸ���
		if (_idleCount >= 1)
		{
			_idleCount = 0;

			int RndNumber;
			RndNumber = RND->getFromIntTo(0, 2);

			if (RndNumber == 0)
			{
				_state = stateNpc::IDLE_CHANGE_L;
				isOnceAniPlay(_state);
			}
			if (RndNumber == 1)
			{
				_state = stateNpc::IDLE_ACT2;
				isOnceAniPlay(_state);
			}
		}
	}

	//�÷��̾� ���ٽ�
	if (_playerClose == true)
	{
		if (_state == stateNpc::IDLE_L || _state == stateNpc::IDLE_R)
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{
				if (_state == stateNpc::IDLE_L)
				{
					_state = stateNpc::TALK;
					_saveTalkDirection = LEFT;
				}
				else if (_state == stateNpc::IDLE_R)
				{
					_state = stateNpc::TALK;
					_saveTalkDirection = RIGHT;
				}
			}
		}
	}

	//��ȭ��
	//if (_state == stateNpc::TALK)
	//{
	//}

	//==========================================================

	//UI1��
	//if (_state == stateNpc::UI1_ING)
	//{
	//	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	//	{
	//		_state = stateNpc::UI1_ESC;
	//		isOnceAniPlay(_state);
	//	}
	//
	//	if (KEYMANAGER->isOnceKeyDown('F'))
	//	{
	//		_state = stateNpc::UI2_ING;
	//		isOnceAniPlay(_state);
	//	}
	//
	//
	//}
	//
	////UI2��
	//if (_state == stateNpc::UI2_ING)
	//{
	//	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	//	{
	//		_state = stateNpc::UI2_ESC;
	//		isOnceAniPlay(_state);
	//	}
	//}

	//==========================================================




}

void npc_SpellBook::render()
{
	npc::render();

	_img->aniRender(getMemDC(), _pos.x - CAMERA2D->getCamPosX(), _pos.y - CAMERA2D->getCamPosY(), _ani);
}

void npc_SpellBook::isOnceAniPlay(stateNpc EnumNumber)
{
	switch (EnumNumber)
	{
	case stateNpc::IDLE_L:
		_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_L");
		_ani->start();
		break;
	case stateNpc::IDLE_R:
		_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_R");
		_ani->start();
		break;
	case stateNpc::IDLE_CHANGE_L:
		_ani = KEYANIMANAGER->findAnimation("spellBook_idle_Change_L");
		_ani->start();
		break;
	case stateNpc::IDLE_CHANGE_R:
		_ani = KEYANIMANAGER->findAnimation("spellBook_idle_Change_R");
		_ani->start();
		break;
	case stateNpc::IDLE_ACT1:
		_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_Act1");
		_ani->start();
		break;
	case stateNpc::IDLE_ACT2:
		_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_Act2");
		_ani->start();
		break;
	case stateNpc::UI1_START_L:
		_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_L_Talk");
		_ani->start();
		break;
	case stateNpc::UI1_START_R:
		_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_R_Talk");
		_ani->start();
		break;
	case stateNpc::UI1_ING:
		if (_saveTalkDirection == LEFT)
		{
			_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_L_Talk");
		}
		else if (_saveTalkDirection == RIGHT)
		{
			_ani = KEYANIMANAGER->findAnimation("spellBook_Idle_R_Talk");
		}
		_ani->start();
		break;
	case stateNpc::UI1_ESC:
		_ani = KEYANIMANAGER->findAnimation("spellBook_ui1_Esc");
		_ani->start();
		break;
	case stateNpc::UI2_ING:
		_ani = KEYANIMANAGER->findAnimation("spellBook_ui2_Start");
		_ani->start();
		break;
	case stateNpc::UI2_ESC:
		_ani = KEYANIMANAGER->findAnimation("spellBook_ui2_Esc");
		_ani->start();
		break;
	default:
		break;
	}
}

void npc_SpellBook::idleR(void* obj)
{
	npc_SpellBook* book = (npc_SpellBook*)obj;

	book->_state = stateNpc::IDLE_R;
	book->isOnceAniPlay(book->_state);
}

void npc_SpellBook::idleL(void * obj)
{
	npc_SpellBook* book = (npc_SpellBook*)obj;

	book->_state = stateNpc::IDLE_L;
	book->isOnceAniPlay(book->_state);
}

void npc_SpellBook::ui1(void * obj)
{
	npc_SpellBook* book = (npc_SpellBook*)obj;

	book->_state = stateNpc::UI1_ING;
}
