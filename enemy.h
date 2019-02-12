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
	MOVE,
	CHARGE,
	ATTACK,
	HIT,
	DEATH,
	MAX
};

class enemy : public gameNode
{
protected:
	image*			_img;				//�̹���
	animation*		_ani;				//���ʹ� �ִϸ޼�
	RECT			_collisionRc;		//���ʹ� �浹 ��Ʈ

	int				_maxHp;				//���ʹ� �ִ� ü��
	int				_curHp;				//���ʹ� ���� ü��
										
	float			_speed;				//���ʹ� ���ǵ�
	float			_angle;				//���ʹ� ����
	POINTFLOAT		_pos;				//���ʹ� ��ǥ
	POINTFLOAT		_vec;				//���ʹ� ���� ��
										
	E_ANIDIRECTION	_aniDirection;		//���ʹ� �ִϸ��̼�
	E_STATE			_state;				//���ʹ� ����
										
	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�(�Ⱦ���������)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];

	RECT			_tileCheckRc;		//Ÿ���浹�� ��Ʈ
	POINTFLOAT		_tileCheckPos;		//Ÿ���浹�� ��ǥ
	int				_tileCheckIdx[2];	//Ÿ���浹�� �ε���

	// ��������(���ʹ̿��� �ʿ��ؼ� �����ϴ°͵�)�� �ƴѰ�

	player* _player;					//�÷��̾� �ּ� ���� ��������
	POINTFLOAT _playerPos;				//�÷��̾� ��ǥ ��������

	bool _isClose;						//�÷��̾ ������ �ֳ�?(������ Ÿ���� �÷��̾ ������ �갡 Ʈ���)

	list<POINT>				_listPath;
	list<POINT>::iterator	_listIPath;

	float _curCharge;
	float _maxCharge;

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void enemyKeyAnimationInit();
	virtual void enemyArrStateInit();
	virtual void startAni();

	//x�ุ ������ �÷��̾� ������ ������ �ٲ��ִ� �Լ�(������,������ �ƴ�)
	void fixDirection();
	void currentEnemyState();
	virtual void move();


	void setPlayerAdress(player* player) { _player = player; }
	POINTFLOAT getPlayerPos() { return _playerPos; }
	//������ ������

	bool getIsAniOnce() { return _isAniOnce; }
	void setIsAniOnce(bool isAniOnce) { _isAniOnce = isAniOnce; }

	E_ANIDIRECTION getAniDirection() { return _aniDirection; }
	void setAniDirection(E_ANIDIRECTION aniDirection) { _aniDirection = aniDirection; }

	E_STATE getState() { return _state; }
	void setState(E_STATE state) { _state = state; }

	POINTFLOAT getVec() { return _vec; }
	void setVec(POINTFLOAT vec) { _vec = vec; }
	void setVecX(float vecX) { _vec.x = vecX; }
	void setVecY(float vecY) { _vec.y = vecY; }

	POINTFLOAT getPos() { return _pos; }
	image* getImg() { return _img; }
	animation* getAni() { return _ani; }

	float getSpeed() { return _speed; }

	RECT getTileCheckRc() { return _tileCheckRc; }

	void setCurCharge(float curCharge) { _curCharge = curCharge; }
	float getCurCharge() { return _curCharge; }

	void setMaxCharge(float maxCharge) { _curCharge = maxCharge; }
	float getMaxCharge() { return _maxCharge; }
};

