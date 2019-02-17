#pragma once
#include "gameNode.h"
#include "tile.h"
#include "rotateImgMaker.h"


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
	image*			_img;				//이미지
	POINTFLOAT		_imgPos;			//이미지 출력용 좌표
	animation*		_ani;				//애니메이션용 변수

	int				_maxHp;				//에너미 최대 체력
	int				_curHp;				//에너미 현재 체력
										
	float			_speed;				//에너미 스피드
	float			_angle;				//에너미 각도
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	POINTFLOAT		_pos;				//중심 좌표 얘가 모든것의 중심좌표임 얘변하면 나머지 다변함
	RECT			_rc;				//중심 렉트(타일크기)

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	POINTFLOAT		_vec;				//에너미 벡터 값
										
	E_ANIDIRECTION	_aniDirection;		//에너미 애니메이션
	E_STATE			_state;				//에너미 상태
										
	bool			_isAniOnce;			//애니메이션 한번만 재생할 불값(안쓸수도있음)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];

	RECT			_collisionRc;		//충돌판정용 렉트
	POINTFLOAT		_collisionPos;		//충돌판정 좌표

	// 순수혈통(에너미에게 필요해서 존재하는것들)이 아닌것

	player* _player;					//플레이어 주소 여따 넣을거임
	POINTFLOAT _playerPos;				//플레이어 좌표 박을거임

	bool _isClose;						//플레이어가 근접해 있나?(구역의 타일을 플레이어가 밟으면 얘가 트루됨)

	list<POINT>				_listPath;
	list<POINT>::iterator	_listIPath;

	float _curCharge;
	float _maxCharge;

	vector<vector<tile*>> _vvMap;

	//무기 이미지(없는애도있고 있는애도있음 없는애는 nullptr넣을것임)
	// 원본 == 0
	// 1부터 10도씩 총 36개
	rotateImgMaker* _rotateMaker;
	image* _rotateImg[36];

	image* _destImg[3];
	RECT _atkRc;
	POINTFLOAT _atkPos;
	int _atkIdx;

	image* _weaponImg[36];
	image* _effectImg[3][36];

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	//주소 연결
	void setPlayerAdress(player* player) { _player = player; }
	POINTFLOAT getPlayerPos() { return _playerPos; }
	void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }


	virtual void enemyKeyAnimationInit();
	virtual void enemyArrStateInit();
	virtual void startAni();

	//x축만 가지고 플레이어 쪽으로 방향을 바꿔주는 함수(접근자,설정자 아님)
	void fixDirection();
	void currentEnemyState();
	virtual void move();

	//접근자 설정자

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
	void setPos(POINTFLOAT pos) { _pos = pos; }
	void setPosX(float posX) { _pos.x = posX; }
	void setPosY(float posY) { _pos.y = posY; }

	float getSpeed() { return _speed; }

	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }

	void setCurCharge(float curCharge) { _curCharge = curCharge; }
	float getCurCharge() { return _curCharge; }

	void setMaxCharge(float maxCharge) { _curCharge = maxCharge; }
	float getMaxCharge() { return _maxCharge; }

	list<POINT>* getPath() { return &_listPath; }
	list<POINT>::iterator* getIPath() { return &_listIPath; }

	vector<vector<tile*>> getMap() { return _vvMap; }

	//image* getAtkImg() { return _atkImg; }

	void setAtkIdx(int idx) { _atkIdx = idx; }

	POINTFLOAT getAtkPos() { return _atkPos; }
	void setAtkPos(POINTFLOAT atkPos) { _atkPos = atkPos; }
	void setAtkPosX(float x) { _atkPos.x = x; }
	void setAtkPosY(float y) { _atkPos.y = y; }

	RECT getAtkRc() { return _atkRc; }
	void setAtkRc(POINTFLOAT pos) { _atkRc = RectMakeCenter(pos.x, pos.y, _rotateImg[0]->GetWidth(), _rotateImg[0]->GetHeight()); }
	void setAtkRc() { _atkRc = RectMakeCenter(-1000, -1000, 0, 0); }

	virtual int getAtkRange() abstract;
	virtual int getWeaponRange() abstract;
	
};

