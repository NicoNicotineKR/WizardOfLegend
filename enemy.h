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
	image*			_img;				//이미지
	animation*		_ani;				//에너미 애니메숑
	RECT			_collisionRc;		//에너미 충돌용 렉트
	RECT			_renderRc;			//에너미 렌더용 렉트
	RECT			_moveRc;			//에너미 무브용 렉트

	int				_maxHp;				//에너미 최대 체력
	int				_curHp;				//에너미 현재 체력
										
	float			_speed;				//에너미 스피드
	float			_angle;				//에너미 각도
	POINTFLOAT		_pos;				//에너미 좌표
	POINTFLOAT		_vec;				//에너미 벡터 값
										
	E_ANIDIRECTION	_aniDirection;		//에너미 애니메이션
	E_STATE			_state;				//에너미 상태
	E_MOVEDIRECTION	_moveDirection;		//에너미 이동 방향
										
	bool			_isAniOnce;			//애니메이션 한번만 재생할 불값(안쓸수도있음)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];

	player* _player;					//플레이어 주소 여따 넣을거임

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

