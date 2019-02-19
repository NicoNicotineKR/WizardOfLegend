#pragma once
#include "gameNode.h"
#include "tile.h"
#include "rotateImgMaker.h"
#include "skills.h"

class bossState;
class player;

enum class B_ANIDIRECTION
{
	LEFT,
	RIGHT
};

enum class B_STATE
{
	SLEEP,			// 보스 발견하기전 
	IDLE,			// 아이들...인데 있나?
	SPAWN,			// 최초 다이얼로그 나오기전 스폰하는거
	CASTING,		// 조롱 or 스턴후 보스턴되기전에 손휘두름
	MOCK,			// 스킬 다쓰고 조롱하는거 이떄 맞으면 스턴됨 (hit 없음)
	STUN,			// 조롱하다가 1대라도 맞으면 스턴상태들어감
	DASH,			// 스킬 4 사용 전 대쉬
	SKILL_ONE,		// 물방울 회전!!!! 회오리!!!!!
	SKILL_TWO,		// 눈송이 회전!! 회오리!!!!
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
	POINTFLOAT		_imgPos;			//이미지 출력용 좌표
	animation*		_ani;				//애니메이션

	POINTFLOAT		_pos;				//중심 좌표
	POINTFLOAT		_vec;				//벡터 값
	RECT			_rc;				//중심 렉트(타일충돌에 쓰임)

	RECT			_collisionRc;		//히트 판정용 렉트
	POINTFLOAT		_collisionPos;		//히트 판정 좌표

	int				_maxHp;				//최대체력
	int				_curHp;				//현재체력
	float			_speed;				//스피드
	float			_angle;				//보스와 플레이어사이의 각도
	float			_hitAngle;			//맞을때 튕겨나갈 각도

	bool			_isAniOnce;			//애니메이션 한번만 재생할 불값
	bool			_isClose;			//플레이어가 근접해 있나?(구역의 타일을 플레이어가 밟으면 얘가 트루됨)
	bool			_isStun;			//스턴상태니?
	bool			_isDeath;			//죽었니?

	B_ANIDIRECTION	_aniDirection;		//애니메이션
	B_STATE			_state;				//상태

	bossState*		_bossState;
	bossState*		_arrState[static_cast<const int>(B_STATE::MAX)];

	//날개
	image*			_wingImg;			//날개 이미지
	animation*		_wingAni;			//날개 애니메이션
	POINTFLOAT		_wingPos;			//날개 좌표 (보스 띄우는 좌표 + 매직넘버 해줘야함)

	//등장 and 죽음용 crystal img
	image*			_crystalImg;		//크리스탈 이미지
	animation*		_crystalAni;		//크리스탈 애니메이션
	POINTFLOAT		_crystalPos;		//크리스탈 좌표 (보스 띄우는 좌표 + 매직넘버 해줘야함)

	// 혼혈

	player* _player;					//플레이어 주소 여따 넣을거임
	POINTFLOAT _playerPos;				//플레이어 좌표 박을거임
	vector<vector<tile*>> _vvMap;

	//	재만 추가목록 ----------------------------
	//	스킬
	vector<skills*> _vSkills;


	// 그떄 그때 추가하는 목록인데 더러울것임.
	//---------------------------------------------------------------------------------------------------------------------------------------

	int _skill_Usage_Count;				//스킬 사용 횟수((캐스팅할때 0이되고 스킬쓸때마다 +1하고 3에서 4가될때 조롱모드 들감)
	int _skillNum[5];					//스킬 겹치지않게 쓸려고 만듬(셔플해서 앞에꺼 쓸거임)

	//---------------------------------------------------------------------------------------------------------------------------------------

private:
//콘스트 변수 넣을공간
	const int BOSS_HP = 1000;
public:
	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }
	void setPlayerAdress(player* player) { _player = player; }

	//보스 키 애니메이션 초기화
	void bossKeyAnimationInit();
	//보스 상태 배열 초기화
	void bossArrStateInit();

	//날개 키 애니메이션 초기화
	void wingKeyAnimationInit();
	
	//크리스탈 키 애니메이션초기화
	void crystalKeyAnimationInit();



	//현재 적용된 상태에따라 보스상태 변경해주는 함수
	void bossCurrentState();
	//상태와 방향에따라 애니메이션 시작해주는 함수
	void startAni();

	//필요할거같으면 쓰자
	//void fixDirection();
	//void moveDirection();


	// 그떄 그때 추가하는 목록인데 더러울것임.
	//---------------------------------------------------------------------------------------------------------------------------------------
	static void skillUse(void* obj);

	void skillShuffle();
	void useSkill();

	//---------------------------------------------------------------------------------------------------------------------------------------

	//get
	//---------------------------------------------------------------------------------------------------------------------------------------
	image*					getImg()										{ return _img; }
	POINTFLOAT				getImgPos()										{ return _imgPos; }
	animation*				getAni()										{ return _ani; }

	POINTFLOAT				getPos()										{ return _pos; }
	POINTFLOAT				getVec()										{ return _vec; }
	RECT					getRc()											{ return _rc; }

	RECT					getCollisionRc()								{ return _collisionRc; }
	POINTFLOAT				getCollisionPos()								{ return _collisionPos; }

	int						getMaxHp()										{ return _maxHp; }
	int						getCurHp()										{ return _curHp; }
	float					getSpeed()										{ return _speed; }
	float					getAngle()										{ return _angle; }
	float					getHitAngle()									{ return _hitAngle; }

	bool					getIsAniOnce()									{ return _isAniOnce; }
	bool					getIsClose()									{ return _isClose; }
	bool					getIsStun()										{ return _isStun; }
	bool					getIsDead()										{ return _isDeath; }

	B_ANIDIRECTION			getAniDirection()								{ return _aniDirection; }
	B_STATE					getState()										{ return _state; }
	bossState*				getBossState()									{ return _bossState; }

	image*					getWingImg()									{ return _wingImg; }
	animation*				getWingAni()									{ return _wingAni; }
	POINTFLOAT				getWingPos()									{ return _wingPos; }

	image*					getCrystalImg()									{ return _crystalImg; }
	animation*				getCrystalAni()									{ return _crystalAni; }
	POINTFLOAT				getCrystalPos()									{ return _crystalPos; }

	player*					getPlayer()										{ return _player; }
	POINTFLOAT				getPlayerPos()									{ return _playerPos; }
	vector<vector<tile*>>	getMap()										{ return _vvMap; }
	//---------------------------------------------------------------------------------------------------------------------------------------

	//set
	//---------------------------------------------------------------------------------------------------------------------------------------
	void					setImg(image* img)								{ _img = img; }
	void					setImgPos(POINTFLOAT imgPos)					{ _imgPos = imgPos; }
	void					setAni(animation* ani)							{ _ani = ani; }

	void					setPos(POINTFLOAT pos)							{ _pos = pos; }
	void					setVec(POINTFLOAT vec)							{ _vec = vec; }
	void					setRc(RECT rc)									{ _rc = rc; }

	void					setCollisionRc(RECT collisionRc)				{ _collisionRc = collisionRc; }
	void					setCollisionPos(POINTFLOAT collisionPos)		{ _collisionPos = collisionPos; }

	void					setMaxHp(int maxHp)								{ _maxHp = maxHp; }
	void					setCurHp(int curHp)								{ _curHp = curHp; }
	void					setSpeed(float speed)							{ _speed = speed; }
	void					setAngle(float angle)							{ _angle = angle; }
	void					setHitAngle(float hitAngle)						{ _hitAngle = hitAngle; }

	void					setIsAniOnce(bool isAniOnce)					{ _isAniOnce = isAniOnce; }
	void					setIsClose(bool isClose)						{ _isClose = isClose; }
	void					setIsStun(bool isStun)							{ _isStun = isStun; }
	void					setIsDead(bool isDead)							{ _isDeath = isDead; }

	void					setAniDirection(B_ANIDIRECTION aniDirection)	{ _aniDirection = aniDirection; }
	void					setState(B_STATE state)							{ _state = state; }
	void					setBossState(bossState* bossState)				{ _bossState = bossState; }

	void					setWingImg(image* wingImg)						{ _wingImg = wingImg; }
	void					setWingAni(animation* wingAni)					{ _wingAni = wingAni; }
	void					setWingPos(POINTFLOAT wingPos)					{ _wingPos = wingPos; }

	void					setCrystalImg(image* crystalImg)				{ _crystalImg = crystalImg; }
	void					setCrystalAni(animation* crystalAni)			{ _crystalAni = crystalAni; }
	void					setCrystalPos(POINTFLOAT crystalPOs)			{ _crystalPos = crystalPOs; }

	player*					setPlayer(player* player)						{ _player = player; }
	POINTFLOAT				setPlayerPos(POINTFLOAT playerPos)				{ _playerPos = playerPos; }
	vector<vector<tile*>>	setMap(vector<vector<tile*>> vvMap)				{ _vvMap = vvMap; }
	//---------------------------------------------------------------------------------------------------------------------------------------
};

