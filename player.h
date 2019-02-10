#pragma once
#include "gameNode.h"

class playerState;

//�ִϸ��̼ǿ� ����
enum class ANIDIRECTION
{
	NONE,
	FRONT,
	BACK,
	LEFT,
	RIGHT
};
//�÷��̾� ����
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
	animation*		_ani;					//�÷��̾� �ִ�(��ȭ ��ȭ�ƴ�)
	RECT			_collisionRc;			//�÷��̾� �浹 ��Ʈ

	int				_maxHp;					//�÷��̾� �ִ� ü��
	int				_curHp;					//�÷��̾� ���� ü��

	float			_speed;					//�÷��̾� ���ǵ�
	float			_angle;					//�÷��̾� ����
	POINTFLOAT		_pos;					//�÷��̾� ��ǥ
	POINTFLOAT		_vec;					//�÷��̾� ���� ��

	ANIDIRECTION	_aniDirection;			//�ִϸ��̼� ��(dragon �ƴ�) ����
	MOVEDIRECTION	_moveDirection;			//�̵��� ����
	STATE			_state;					//�÷��̾� ����

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

