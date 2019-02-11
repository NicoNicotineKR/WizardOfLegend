#pragma once
#include "gameNode.h"


class enemyState;
class player;

enum class E_ANIDIRECTION
{
	LEFT,
	RIGHT
};

enum class E_STATE
{
	IDLE,
	SPAWN,
	MOVESTART,
	MOVE,
	CHARGE,
	ATTACK,
	HIT,
	DEATH,
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
protected:
	image*			_img;				//�̹���
	animation*		_ani;				//���ʹ� �ִϸ޼�
	RECT			_collisionRc;		//���ʹ� �浹�� ��Ʈ
	RECT			_renderRc;			//���ʹ� ������ ��Ʈ
	RECT			_moveRc;			//���ʹ� ����� ��Ʈ

	int				_maxHp;				//���ʹ� �ִ� ü��
	int				_curHp;				//���ʹ� ���� ü��
										
	float			_speed;				//���ʹ� ���ǵ�
	float			_angle;				//���ʹ� ����
	POINTFLOAT		_pos;				//���ʹ� ��ǥ
	POINTFLOAT		_vec;				//���ʹ� ���� ��
										
	E_ANIDIRECTION	_aniDirection;		//���ʹ� �ִϸ��̼�
	E_STATE			_state;				//���ʹ� ����
	E_MOVEDIRECTION	_moveDirection;		//���ʹ� �̵� ����
										
	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�(�Ⱦ���������)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];

	player* _player;					//�÷��̾� �ּ� ���� ��������

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enemyKeyAnimationInit();
	virtual void enemyArrStateInit();

	virtual void setPlayerAdress(player* player) { _player = player; }


};

