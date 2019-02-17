#pragma once
#include "gameNode.h"
#include "playerStatusUI.h"
#include "tile.h"
#include "tileNode.h"
#include "skillCooldownUI.h"
#include "skills.h"

class skills;
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
enum class CURRENTSKILL
{
	FLAMESTRIKE,
	CHAINLIGHTNING,
	FROSTFAN,
	REBOUNDINGCICLES,
	SEARINGRUSH,
	SHATTERINGSTRIKE,
	SHOCKNOVA,
	STONESHOT,
	MAX
};
/*
skills _curSkill[0] = FlameStrike;




*/
class player : gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	vvMap* _vvMap;

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

	skills*		_curSkills[5];
	skills*		_arrSkills[static_cast<const int>(CURRENTSKILL::MAX)];

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
	string			 _usingSkillName;
	int _count;
public:
	player();
	~player();

	HRESULT init(vvMap& vvMapLink);
	void release();
	void update();
	void render(HDC hdc);

	void playerKeyAnimationInit();
	void inPutKey();
	void startAni();
	void arrStateInit();

	void currentPlayerState();
	void playerCirclePosition();
	void isMoveOff();
	void vecZero();

	//Ÿ�� �浹 ����ó��
	void tileCheckFunc();

	//�ִϸ��̼� �ݹ��Լ�
	static void playerIdle(void* obj);

	//�ִϸ��̼� ���� getset
	inline ANIDIRECTION getAniDirection() { return _aniDirection; }
	inline void			setAniDirection(ANIDIRECTION aniDirection) { _aniDirection = aniDirection; }
	//���� getset
	inline STATE getState() { return _state; }
	inline void  setState(STATE state) { _state = state; }
	//�̵� ���� getset
	inline MOVEDIRECTION getMoveDirection() { return _moveDirection; }
	inline void			 setMoveDirection(MOVEDIRECTION moveDirection) { _moveDirection = moveDirection; }

	//���� getset
	inline POINTFLOAT getVec() { return _vec; }
	inline void setVec(POINTFLOAT vec) { _vec = vec; }
	inline void setVecX(float vecX) { _vec.x = vecX; }
	inline void setVecY(float vecY) { _vec.y = vecY; }
	//pos getset
	inline POINTFLOAT getPos() { return _pos; }
	inline void setPosX(float posX) { _pos.x = posX; }
	inline void setPosY(float posY) { _pos.y = posY; }
	//image get
	inline image* getImg() { return _img; }

	//�ִϸ��̼� �ѹ� ���� bool getset
	inline void setIsPlayerAniOnce(bool isOnce) { _isPlayerAniOnce = isOnce; }
	inline bool getIsPlayerAniOnce() { return _isPlayerAniOnce; }
	//���ǵ� get
	inline float getSpeed() { return _speed; }
	//Ÿ�� �浹 ��Ʈ get
	inline RECT getPlayerTileCheckRc() { return _tileCheckRc; }

	
	//inline void setBoolMoveDirection(BOOLMOVEDIRECTION boolMoveDirection) {_boolMoveDirection = boolMoveDirection;}
	//inline BOOLMOVEDIRECTION getBoolMoveDirection() { return _boolMoveDirection; }

	//Ÿ�� �浹��Ʈ Ÿ�� �ε���
	inline POINT getLeftTopIndex() { return _tileCheckIndex[0]; }
	inline POINT getRightTopIndex() { return _tileCheckIndex[1]; }
	inline POINT getLeftBottomIndex() { return _tileCheckIndex[2]; }
	inline POINT getRightBottomIndex() { return _tileCheckIndex[3]; }

	//Ÿ�� �浹��Ʈ pos
	inline POINTFLOAT getTileCheckRcPos() { return _tileCheckRcPos; }

	inline float getPlayerAngle() { return _playerCircleDirectionAngle; }
	inline POINTFLOAT getCircleDirectionPos() { return _playerCircleDirectionPos; }
	inline HDC getPlayerMemDC() { return getMemDC(); }

	//��ų ��뿩�� getset
	//inline bool getIsUsingSkill() { return _isUsingSkill; }
	//inline void setIsUsingSkill(bool isUsingSkill) { _isUsingSkill = isUsingSkill; }
	inline skills* getCurSkills1() { return _curSkills[0]; }
	inline skills* getCurSkills2() { return _curSkills[1]; }
	inline vvMap* getVVMapMemoryAddress() { return _vvMap; }
	inline skillCooldownUI* getSkillUI() {return _skillUI;}

	inline void setUsingSkillName(string name) { _usingSkillName = name; }

	inline RECT getCollisionRc() { return _collisionRc; }
};

