#pragma once
#include "gameNode.h"
#include "tile.h"
#include "rotateImgMaker.h"

class bossState;
class player;

enum class B_ANIDIRECTION
{
	LEFT,
	RIGHT
};

enum class B_STATE
{
	IDLE,			// 아이들...인데 있나?
	SPAWN,			// 최초 다이얼로그 나오기전 스폰하는거
	CASTING,		// 조롱 or 스턴후 보스턴되기전에 손휘두름
	MOCK,			// 스킬 다쓰고 조롱하는거 이떄 맞으면 스턴됨 (hit 없음)
	STUN,			// 조롱하다가 1대라도 맞으면 스턴상태들어감
	SKILL_ONE,		// 물방울 회전!!!! 회오리!!!!!
	SKILL_TWO,		// 눈송이 회전!!!! 회오리!!!!
	SKILL_THREE,	// 창 3개 날리기
	SKILL_FOUR,		// 돌진 얼음칼 돌리기
	SKILL_FIVE,		// 고드름비
	DEATH_START,	// 죽음 시작 -> 무릎꿇고 다이얼로그 뱉음
	DEATH,			// 얼음되서 사라짐 (죽음 시작에서 나온 다이얼로그 에서 키눌러서 다이얼로그 종료되면 얼음되고 깨짐)
	MAX
};

class boss : public gameNode
{
private:    
	// 순혈
	image*			_img;				//이미지
	animation*		_ani;				//애니메이션

	POINTFLOAT		_pos;				//중심 좌표
	POINTFLOAT		_vec;				//벡터 값
	RECT			_rc;				//중심 렉트(타일충돌에 쓰임)

	POINTFLOAT		_imgPos;			//이미지 출력용 좌표

	RECT			_collisionRc;		//히트 판정용 렉트
	POINTFLOAT		_collisionPos;		//히트 판정 좌표

	image*			_wingImg;			//날개 이미지
	animation*		_wingAni;			//날개 애니메이션
	POINTFLOAT		_wingPos;			//날개 좌표

	int				_maxHp;				//최대체력
	int				_curHp;				//현재체력
	float			_speed;				//스피드
	float			_angle;				//보스와 플레이어사이의 각도
	float			_hitAngle;			//맞을때 튕겨나갈 각도


	B_ANIDIRECTION	_aniDirection;		//애니메이션
	B_STATE			_state;				//상태

	bool			_isAniOnce;			//애니메이션 한번만 재생할 불값

	bossState*		_bossState;
	bossState*		_arrState[static_cast<const int>(B_STATE::MAX)];

	// 혼혈

	player* _player;					//플레이어 주소 여따 넣을거임
//	POINTFLOAT _playerPos;				//플레이어 좌표 박을거임
	vector<vector<tile*>> _vvMap;

//	bool _isClose;						//플레이어가 근접해 있나?(구역의 타일을 플레이어가 밟으면 얘가 트루됨)

//	rotateImgMaker* _rotateMaker;
//	image* _effectImg[3][36];
//	RECT _atkRc;
//	POINTFLOAT _atkPos;
//	int _atkIdX;
//	int _atkIdY;
//	int _countIdY;
//	image* _weaponImg[36];

	//스턴상태니?
	bool _isStun;
	//죽었니?
	bool _isDead;

private:
//콘스트 넣을것들
public:
	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }
	void setPlayerAdress(player* player) { _player = player; }

	//get
	image*			getImg()				{ return _img; }
	animation*		getAni()				{ return _ani; }
	POINTFLOAT		getPos()				{ return _pos; }
	POINTFLOAT		getVec()				{ return _vec; }
	RECT			getRc()					{ return _rc; }
	POINTFLOAT		getImgPos()				{ return _imgPos; }
	RECT			getCollisionRc()		{ return _collisionRc; }
	POINTFLOAT		getCollisionPos()		{ return _collisionPos; }
	image*			getWingImg()			{ return _wingImg; }
	animation*		getWingAni()			{ return _wingAni; }
	POINTFLOAT		getWingPos()			{ return _wingPos; }
	int				getMaxHp()				{ return _maxHp; }
	int				getCurHp()				{ return _curHp; }
	float			getSpeed()				{ return _speed; }
	float			getAngle()				{ return _angle; }
	float			getHitAngle()			{ return _hitAngle; }
	B_ANIDIRECTION	getAniDirection()		{ return _aniDirection; }
	B_STATE			getState()				{ return _state; }
	bool			getIsAniOnce()			{ return _isAniOnce; }
	bossState*		getBossState()			{ return _bossState; }

	//set

	image*			getImg(image* img)							{ _img = img; }
	animation*		getAni(animation* ani)						{ _ani = ani; }
	POINTFLOAT		getPos(POINTFLOAT pos)						{ _pos = pos; }
	POINTFLOAT		getVec(POINTFLOAT vec)						{ _vec = vec; }
	RECT			getRc(RECT rc)								{ _rc = rc; }
	POINTFLOAT		getImgPos(POINTFLOAT imgPos)				{ _imgPos = imgPos; }
	RECT			getCollisionRc(RECT collisionRc)			{ _collisionRc = collisionRc; }
	POINTFLOAT		getCollisionPos(POINTFLOAT collisionPos)	{ _collisionPos = collisionPos; }
	image*			getWingImg(image* wingImg)					{ _wingImg = wingImg; }
	animation*		getWingAni(animation* wingAni)				{ _wingAni = wingAni; }
	POINTFLOAT		getWingPos(POINTFLOAT wingPos)				{ _wingPos = wingPos; }
	int				getMaxHp(int maxHp)							{ _maxHp = maxHp; }
	int				getCurHp(int curHp)							{ _curHp = curHp; }
	float			getSpeed(float speed)						{ _speed = speed; }
	float			getAngle(float angle)						{ _angle = angle; }
	float			getHitAngle(float hitAngle)					{ _hitAngle = hitAngle; }
	B_ANIDIRECTION	getAniDirection(B_ANIDIRECTION aniDirection){ _aniDirection = aniDirection; }
	B_STATE			getState(B_STATE state)						{ _state = state; }
	bool			getIsAniOnce(bool isAniOnce)				{ _isAniOnce = isAniOnce; }
	bossState*		getBossState(bossState* bossState)			{ _bossState = bossState; }
};

