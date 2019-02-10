#pragma once
#include "gameNode.h"

class playerState;

//애니메이션용 방향
enum class ANIDIRECTION
{
	NONE,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};
//플레이어 상태
enum class STATE
{
	IDLE,
	MOVE,
	DASH,
	SKILL_ONE,
	SKILL_TWO,
	SKILL_THREE,
	SKILL_FOUR,
	SKILL_FIVE,
	HIT,
	DEAD,
	MAX
};
enum class MOVEDIRECTION
{
	NONE,
	TOP,
	LEFT_TOP,
	RIGHT_TOP,
	BOTTOM,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,
	RIGHT,
	LEFT
};
class player : gameNode
{
private:
	image*			_img;
	animation*		_ani;					//플레이어 애니(만화 영화아님)
	RECT			_collisionRc;			//플레이어 충돌 렉트

	int				_maxHp;					//플레이어 최대 체력
	int				_curHp;					//플레이어 현재 체력

	float			_speed;					//플레이어 스피드
	float			_angle;					//플레이어 각도
	POINTFLOAT		_pos;					//플레이어 좌표
	POINTFLOAT		_vec;					//플레이어 벡터 값

	ANIDIRECTION	_aniDirection;			//애니메이션 용(dragon 아님) 방향
	MOVEDIRECTION	_moveDirection;			//이동용 방향
	STATE			_state;					//플레이어 상태

	bool _isPlayerAniOnce;

	playerState* _playerState;
	playerState* _arrState[static_cast<const int>(STATE::MAX)];

public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void playerKeyAnimationInit();
	void inPutKey();
	void startAni();
	void arrStateInit();

	void currentPlayerState();
	void playerMove();
	void playerDash();

	inline ANIDIRECTION getAniDirection() { return _aniDirection; }
	inline void			setAniDirection(ANIDIRECTION aniDirection) { _aniDirection = aniDirection; }

	inline STATE getState() { return _state; }
	inline void  setState(STATE state) { _state = state; }

	inline MOVEDIRECTION getMoveDirection() { return _moveDirection; }
	inline void			 setMoveDirection(MOVEDIRECTION moveDirection) { _moveDirection = moveDirection; }

	inline POINTFLOAT getVec() { return _vec; }
	inline void setVec(POINTFLOAT vec) { _vec = vec; }
	inline void setVecX(float vecX) { _vec.x = vecX; }
	inline void setVecY(float vecY) { _vec.y = vecY; }

	inline void setIsPlayerAniOnce(bool isOnce) { _isPlayerAniOnce = isOnce; }
	inline bool getIsPlayerAniOnce() { return _isPlayerAniOnce; }

	inline float getSpeed() { return _speed; }

	static void playerIdle(void* obj);
};

