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
	image*			_img;				//이미지
	animation*		_ani;				//적 애니메숑
	RECT			_collisionRc;		//적 충돌 렉트

	int				_maxHp;				//적 최대 체력
	int				_curHp;				//적 현재 체력
										
	float			_speed;				//적 스피드
	float			_angle;				//적 각도
	POINTFLOAT		_pos;				//적 좌표
	POINTFLOAT		_vec;				//적 벡터 값
										
	E_ANIDIRECTION	_aniDirection;		//적 애니메이션
	E_STATE			_state;				//적 상태
	E_MOVEDIRECTION	_moveDirection;		//적 이동 방향
										
	bool			_isAniOnce;			//애니메이션 한번만 재생할 불값(안쓸수도있음)

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

