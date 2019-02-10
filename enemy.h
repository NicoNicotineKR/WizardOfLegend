#pragma once
#include "gameNode.h"

class enemyState;

enum class E_ANIDIRECTION
{
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

enum class E_STATE
{
	IDLE,
	SPAWN,
	MOVE,
	CHARGE,
	ATTACK,
	MAX
};

enum class  E_MOVEDIRECTION
{
	LEFT,
	LEFT_TOP,
	LEFT_BOTTOM,
	TOP,
	RIGHT,
	RIGHT_TOP,
	RIGHT_BOTTOM,
	BOTTOM
};

class enemy
{
private:
	image*			_img;				//�̹���
	animation*		_ani;				//�� �ִϸ޼�
	RECT			_collisionRc;		//�� �浹 ��Ʈ

	int				_maxHp;				//�� �ִ� ü��
	int				_curHp;				//�� ���� ü��
										
	float			_speed;				//�� ���ǵ�
	float			_angle;				//�� ����
	POINTFLOAT		_pos;				//�� ��ǥ
	POINTFLOAT		_vec;				//�� ���� ��
										
	E_ANIDIRECTION	_aniDirection;		//�� �ִϸ��̼�
	E_STATE			_state;				//�� ����
	E_MOVEDIRECTION	_moveDirection;		//�� �̵� ����
										
	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�(�Ⱦ���������)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];


public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enemyKeyAnimationInit();
};

