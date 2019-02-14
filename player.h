#pragma once
#include "gameNode.h"
#include "playerStatusUI.h"
#include "tile.h"
#include "tileNode.h"
#include "skillCooldownUI.h"
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
	FALL,
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
enum class BOOLMOVEDIRECTION
{
	NONE,
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM
};

enum class SKILLNAME
{
	FlameStrike,
	stoneShot,
	searingRush
};
/*
skills _curSkill[0] = FlameStrike;




*/
class player : gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	image*			_img;					//�÷��̾� �̹���
	animation*		_ani;					//�÷��̾� �ִ�(��ȭ ��ȭ�ƴ�)
	RECT			_collisionRc;			//�÷��̾� �浹 ��Ʈ
	RECT			_tileCheckRc;
	POINTFLOAT		_tileCheckRcPos;
	//int				_tileCheckIdx[2];

	int				_maxHp;					//�÷��̾� �ִ� ü��
	int				_curHp;					//�÷��̾� ���� ü��

	float			_speed;					//�÷��̾� ���ǵ�
	float			_angle;					//�÷��̾� ����
	POINTFLOAT		_pos;					//�÷��̾� ��ǥ
	POINTFLOAT		_vec;					//�÷��̾� ���� ��
	POINTFLOAT		_tileCollVec[4];

	ANIDIRECTION	_aniDirection;			//�ִϸ��̼� ��(dragon �ƴ�) ����
	MOVEDIRECTION	_moveDirection;			//�̵��� ����
	STATE			_state;					//�÷��̾� ����

	bool _isPlayerAniOnce;

	playerState* _playerState;
	playerState* _arrState[static_cast<const int>(STATE::MAX)];

	image*			_playerCircleImg;
	image*			_playerCircleDirectionImg;
	float			_playerCircleDirectionAngle;
	float			_playerCircleRadius;
	POINTFLOAT		_playerCirclePos;
	POINTFLOAT		_playerCircleDirectionPos;

	POINT _tileCheckIndex[4];
	bool _isLeftTopCheck;
	bool _isRightTopCheck;
	bool _isLeftBottomCheck;
	bool _isRightBottomCheck;
	BOOLMOVEDIRECTION _boolMoveDirection;

	playerStatusUI* _playerStatusUI;

	skillCooldownUI* _skillUI;

	int _curSkill[5];
	int _count;

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
	void playerCirclePosition();
	void isMoveOn();
	void isMoveOff();
	void vecZero(vvMap& vvMapLink);

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

	inline POINTFLOAT getPos() { return _pos; }
	inline void setPosX(float posX) { _pos.x = posX; }
	inline void setPosY(float posY) { _pos.y = posY; }

	inline image* getImg() { return _img; }

	inline void setIsPlayerAniOnce(bool isOnce) { _isPlayerAniOnce = isOnce; }
	inline bool getIsPlayerAniOnce() { return _isPlayerAniOnce; }

	inline float getSpeed() { return _speed; }

	inline RECT getPlayerTileCheckRc() { return _tileCheckRc; }
	static void playerIdle(void* obj);

	inline void setBoolMoveDirection(BOOLMOVEDIRECTION boolMoveDirection) {_boolMoveDirection = boolMoveDirection;}
	inline BOOLMOVEDIRECTION getBoolMoveDirection() { return _boolMoveDirection; }

	inline POINT getLeftTopIndex() { return _tileCheckIndex[0]; }
	inline POINT getRightTopIndex() { return _tileCheckIndex[1]; }
	inline POINT getLeftBottomIndex() { return _tileCheckIndex[2]; }
	inline POINT getRightBottomIndex() { return _tileCheckIndex[3]; }

	inline POINTFLOAT getTileCheckRcPos() { return _tileCheckRcPos; }

	void tileCheckFunc(vvMap& vvMapLink);
};

