#pragma once
#include "gameNode.h"
#include "playerStatusUI.h"
#include "tile.h"
#include "tileNode.h"
#include "skillCooldownUI.h"
#include "skills.h"


class enemyMgr;
class boss;
class skills;
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
	SEARINGRUSH,
	SHOCKNOVA,
	STONESHOT,
	MAX
};
/*
skills _curSkill[0] = FlameStrike;




*/
class player : public gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;

	vvMap* _vvMap;
	enemyMgr* _em;
	boss*	_boss;

	image*			_img;					//플레이어 이미지
	animation*		_ani;					//플레이어 애니(만화 영화아님)
	RECT			_collisionRc;			//플레이어 충돌 렉트
	RECT			_tileCheckRc;
	POINTFLOAT		_tileCheckRcPos;
	//int				_tileCheckIdx[2];

	int				_maxHp;					//플레이어 최대 체력
	int				_curHp;					//플레이어 현재 체력

	float			_speed;					//플레이어 스피드
	float			_angle;					//플레이어 각도
	POINTFLOAT		_pos;					//플레이어 좌표
	POINTFLOAT		_vec;					//플레이어 벡터 값
	POINTFLOAT		_tileCollVec[4];

	ANIDIRECTION	_aniDirection;			//애니메이션 용(dragon 아님) 방향
	MOVEDIRECTION	_moveDirection;			//이동용 방향
	STATE			_state;					//플레이어 상태

	bool _isPlayerAniOnce;

	playerState* _playerState;
	playerState* _arrState[static_cast<const int>(STATE::MAX)];

	skills*		_curSkills[4];
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
	float _hitCount;
	bool _isHit;
	bool _isAlive;
	bool _isFall;
	float _fallVecY;
	POINTFLOAT _dashLastPos;
	image* _tileBlanket[25];
	POINTFLOAT  _tileBlanketPos[25];
	POINT		_tileBlanketIndex[25];

	int			_basicSkillNum;
public:
	player();
	~player();

	HRESULT init(vvMap& vvMapLink);
	void release();
	void update();
	void render(HDC hdc);
	void CamRender(HDC hdc);

	inline void enemyLink(enemyMgr* em) { _em = em; }
	inline void bossLink(boss* boss) { _boss = boss; }

	void playerKeyAnimationInit();
	void inPutKey();
	void startAni();
	void arrStateInit();
	void arrSkillInit();
	void skillIconInit();

	void changeSkillIcon(int index);

	void currentPlayerState();
	void playerCirclePosition();
	void isMoveOff();
	void vecZero();
	void enemyAngleCal(float angle);
	//타일 충돌 예외처리
	void tileCheckFunc();
	virtual void changeCurSkill(int index, string name);

	void hitFunc();

	//애니메이션 콜백함수
	static void playerIdle(void* obj);
	static void playerFall(void* obj);

	//애니메이션 방향 getset
	inline ANIDIRECTION getAniDirection() { return _aniDirection; }
	inline void			setAniDirection(ANIDIRECTION aniDirection) { _aniDirection = aniDirection; }
	//상태 getset
	inline STATE getState() { return _state; }
	inline void  setState(STATE state) { _state = state; }
	//이동 방향 getset
	inline MOVEDIRECTION getMoveDirection() { return _moveDirection; }
	inline void			 setMoveDirection(MOVEDIRECTION moveDirection) { _moveDirection = moveDirection; }

	//벡터 getset
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

	//애니메이션 한번 실행 bool getset
	inline void setIsPlayerAniOnce(bool isOnce) { _isPlayerAniOnce = isOnce; }
	inline bool getIsPlayerAniOnce() { return _isPlayerAniOnce; }
	//스피드 get
	inline float getSpeed() { return _speed; }
	//타일 충돌 렉트 get
	inline RECT getPlayerTileCheckRc() { return _tileCheckRc; }

	
	//inline void setBoolMoveDirection(BOOLMOVEDIRECTION boolMoveDirection) {_boolMoveDirection = boolMoveDirection;}
	//inline BOOLMOVEDIRECTION getBoolMoveDirection() { return _boolMoveDirection; }

	//타일 충돌렉트 타일 인덱스
	inline POINT getLeftTopIndex() { return _tileCheckIndex[0]; }
	inline POINT getRightTopIndex() { return _tileCheckIndex[1]; }
	inline POINT getLeftBottomIndex() { return _tileCheckIndex[2]; }
	inline POINT getRightBottomIndex() { return _tileCheckIndex[3]; }

	//타일 충돌렉트 pos
	inline POINTFLOAT getTileCheckRcPos() { return _tileCheckRcPos; }

	inline float getPlayerAngle() { return _playerCircleDirectionAngle; }
	inline POINTFLOAT getCircleDirectionPos() { return _playerCircleDirectionPos; }
	inline HDC getPlayerMemDC() { return getMemDC(); }

	//스킬 사용여부 getset
	//inline bool getIsUsingSkill() { return _isUsingSkill; }
	//inline void setIsUsingSkill(bool isUsingSkill) { _isUsingSkill = isUsingSkill; }
	inline skills* getCurSkills1() { return _curSkills[0]; }
	inline skills* getCurSkills2() { return _curSkills[1]; }
	inline skills* getCurSkills3() { return _curSkills[2]; }
	inline skills* getCurSkills4() { return _curSkills[3]; }
	inline skills* getArrCurSkills(int index) { return _curSkills[index]; }

	inline vvMap* getVVMapMemoryAddress() { return _vvMap; }
	inline skillCooldownUI* getSkillUI() {return _skillUI;}

	inline void setUsingSkillName(string name) { _usingSkillName = name; }

	inline RECT getCollisionRc() { return _collisionRc; }
	inline bool getIsHit() { return _isHit; }
	inline void setIsHit(bool isHit) { _isHit = isHit; }

	inline bool getIsAlive() { return _isAlive; }
	inline void setIsAlive(bool isAlive) { _isAlive = isAlive; }

	inline POINTFLOAT* getPosAddress() { return &_pos; }
	inline vvMap* getVVMap() { return _vvMap; }

	inline void setTileBlanket(image* img,int i) { _tileBlanket[i] = img; }
	inline image* getTileBlanket(int i) { return _tileBlanket[i]; }

	inline void setTileBlanketPos(POINTFLOAT pos, int i) { _tileBlanketPos[i] = pos; }
	inline POINTFLOAT getTileBlanketPos(int i) { return _tileBlanketPos[i]; }

	inline void setTileBlanketIndex(POINT index, int i) { _tileBlanketIndex[i] = index; }
	inline POINT getTileBlanketIndex(int i) { return _tileBlanketIndex[i]; }

	inline void setFallVecY(float vecY) { _fallVecY = vecY; }
	inline float getFallVecY() { return _fallVecY; }

	inline void setDashLastPos(POINTFLOAT pos) { _dashLastPos = pos; }
	inline POINTFLOAT getDashLastPos() { return _dashLastPos; }

	inline int getCurHp() { return _curHp; }
	inline void setCurHp(int _savePlayerHp){ _curHp = _savePlayerHp;}


	//	재만추가
	inline skills* getSkillsInfo(int skillEnum) { return _arrSkills[skillEnum]; }
	inline void setPlayerSkill(int idx, skills* skill) {_curSkills[idx] = skill; }
	
	inline enemyMgr* getEnemyMgrAddress() { return _em; }
	inline boss* getBossAdresss() { return _boss; }

	inline int getBasicSkillNum() { return _basicSkillNum; }
	inline void setBasicSkillNum(int i) { _basicSkillNum = i; }
};

