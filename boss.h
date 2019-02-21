#pragma once
#include "gameNode.h"
#include "tile.h"
#include "rotateImgMaker.h"
#include "throwIceSpear.h"

class bossState;
class player;

//구역 밟으면 트루됨.트루 설정해주는곳(스테이지든 어디든) 에서 보스 상태 spawn으로 설정하고 애니메이션 등등도 설정해줌
//
//spawn의 키애니메이션 끝나면 idle로 변경.idle이 되면서 다이얼로그도 출력
//
//다이얼로그를 종료하면 casting됨
//
//casting 후 스킬use함수로 스킬 총 3번씀
//
//스킬 3번다쓰면 mock
//
//->mock에서 안맞으면 casting 후 반복
//
//->mock에서 맞으면 stun->stun시간동안 스턴후 casting 후 반복
//
//
//위 반복하다가 체력 다닳면 데스 스타트->다이얼로그 출력
//
//다이얼로그 종료하면 death하고 엔딩


enum class B_STATE
{
	SLEEP = 0,			// 보스 발견하기전																				// o			// 날개 없슴
	SPAWN = 1,			// 최초 다이얼로그 나오기전 스폰하는거																// o		    // 날개 작아짐
	IDLE = 2,			// 아이들...인데 있나?																			// o		    // 날개 커짐 -> 아이들유지
	CASTING = 3,		// 조롱 or 스턴후 보스턴되기전에 손휘두름															// o			// 날개 작아짐
	MOCK = 4,			// 스킬 다쓰고 조롱하는거 이떄 맞으면 스턴됨 (hit 없음)												// x			// 날개 커짐
	STUN = 5,			// 조롱하다가 1대라도 맞으면 스턴상태들어감															// x			// 날개 커짐
	DASH = 6,			// 스킬 4 사용 전 대쉬																			// x			// 이전꺼 유지
	SKILL_ONE = 7,		// 물방울 회전!!!! 회오리!!!!!																	// x			// 이전꺼 유지
	SKILL_TWO = 8,		// 눈송이 회전!! 회오리!!!!																		// x			// 이전꺼 유지
	SKILL_THREE = 9,	// 창 3개 날리기																					// o 			// 이전꺼 유지
	SKILL_FOUR = 10,	// 돌진 얼음칼 돌리기																				// x			// 이전꺼 유지
	SKILL_FIVE = 11,	// 고드름비																						// x			// 이전꺼 유지
	DEATH_START = 12,	// 죽음 시작 -> 무릎꿇고 다이얼로그 뱉음															// x			// 날개 커짐
	DEATH = 13,			// 얼음되서 사라짐 (죽음 시작에서 나온 다이얼로그 에서 키눌러서 다이얼로그 종료되면 얼음되고 깨짐)		// x			// 날개 작아짐
	MAX
};
//버려진것들
//	POINTFLOAT		_imgPos;			//이미지 출력용 좌표
//	RECT			_collisionRc;		//히트 판정용 렉트
//	POINTFLOAT		_collisionPos;		//히트 판정 좌표
//	B_ANIDIRECTION	_aniDirection;		//애니메이션
//	POINTFLOAT		_wingPos;			//날개 좌표 (보스 띄우는 좌표 + 매직넘버 해줘야함)
//	POINTFLOAT		_crystalPos;		//크리스탈 좌표 (보스 띄우는 좌표 + 매직넘버 해줘야함)

//	vector<vector<tile*>> _vvMap;
//	void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }

class boss : public gameNode
{
private:    
	// 순혈
	image*			_img;				//이미지
	animation*		_ani;				//애니메이션

	POINTFLOAT		_vec;				//벡터 값
	POINTFLOAT		_pos;				//중심 좌표
	RECT			_rc;				//중심 렉트(맞는판정에쓰임)

	int				_maxHp;				//최대체력
	int				_curHp;				//현재체력
	float			_speed;				//스피드
	float			_angle;				//보스와 플레이어사이의 각도
	float			_hitAngle;			//맞을때 튕겨나갈 각도

	bool			_isAniOnce;			//애니메이션 한번만 재생할 불값
	bool			_isArea;			//플레이어가 근접해 있나?(구역의 타일을 플레이어가 밟으면 얘가 트루됨)
//	bool			_isHit;				//맞았니?			-> mock 상태에서 isHit가 트루가되면 stun상태로 변경함. isHit될때마다 
	bool			_isStun;			//스턴상태니?
	bool			_isDeath;			//죽었니?

	B_STATE			_state;				//상태
	int				_direction;			//대쉬에서만 쓸 방향

	bossState*		_bossState;
	bossState*		_arrState[static_cast<const int>(B_STATE::MAX)];

	//날개
	image*			_wingImg;			//날개 이미지
	animation*		_wingAni;			//날개 애니메이션

	//등장 and 죽음용 crystal img
	image*			_crystalImg;		//크리스탈 이미지
	animation*		_crystalAni;		//크리스탈 애니메이션

	


	// 혼혈
	player* _player;					//플레이어 주소 여따 넣을거임
	POINTFLOAT _playerPos;				//플레이어 좌표 박을거임

	//	재만 추가목록 ----------------------------
	//	스킬
	//vector<skills*> _vSkills;
	throwIceSpear* _skill3;

	// 그떄 그때 추가하는 목록인데 더러울것임.
	//---------------------------------------------------------------------------------------------------------------------------------------

	int _skill_Usage_Count;				//스킬 사용 횟수((캐스팅할때 0이되고 스킬쓸때마다 +1하고 3에서 4가될때 조롱모드 들감)
	int _skillNum[5];					//스킬 겹치지않게 쓸려고 만듬(셔플해서 앞에꺼 쓸거임)
	
	bool _isNeedCal;					//계산 필요하니?



	//---------------------------------------------------------------------------------------------------------------------------------------

private:
//콘스트 변수 넣을공간
	const int BOSS_HP = 1000;
	const int IMG_SHAVE_X = 75;
	const int IMG_SHAVE_Y = 100;
	const int COLLISION_SHAVE_X = 75;
	const int COLLISION_SHAVE_Y = 100;
	const int COLLISION_WIDTH = 50;
	const int COLLISION_HEIGHT = 100;
	const int WING_SHAVE_X = 65;
	const int WING_SHAVE_Y = 60;
	const int CRYSTAL_SHAVE_X = 50;
	const int CRYSTAL_SHAVE_Y = 80;
	const int SHUFFLE_NUM = 30;
	const int DIRECTION_LEFT = -1;
	const int DIRECTION_RIGHT = 1;
public:
	boss();
	~boss();

	HRESULT init();
	void release();
	void update();
	void render();

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
	static void wingIdle(void* obj);

	void skillShuffle();
	void useSkill();

	//보스 발견 or 보스룸 입장시 이함수 쓰면됌
	void setBossSpawn();

	//다이얼로그 끝나면 캐스팅모드 들어가는거 - 형우형이 쓸예정
	void setBossStateCasting();

	void RcCollideBySkillFunc(RECT* skillRc, int dmg, bool* isHit);
	void DistanceBySkillFunc(POINTFLOAT skillPos, float range, int dmg, bool* isHit);

	//---------------------------------------------------------------------------------------------------------------------------------------
	
	//get
	//버려진것 or 즉석으로 추가되는것들
//	POINTFLOAT				getImgPos()										{ return _imgPos; }
//	RECT					getCollisionRc()								{ return _collisionRc; }
//	POINTFLOAT				getCollisionPos()								{ return _collisionPos; }
//	B_ANIDIRECTION			getAniDirection()								{ return _aniDirection; }
//	POINTFLOAT				getWingPos()									{ return _wingPos; }
//	POINTFLOAT				getCrystalPos()									{ return _crystalPos; }
//	vector<vector<tile*>>	getMap()										{ return _vvMap; }

	bool					getIsNeedCal()									{ return _isNeedCal; }
	throwIceSpear*			getSKill3()										{ return _skill3; }
	//---------------------------------------------------------------------------------------------------------------------------------------
	image*					getImg()										{ return _img; }
	animation*				getAni()										{ return _ani; }

	POINTFLOAT				getPos()										{ return _pos; }
	POINTFLOAT				getVec()										{ return _vec; }
	RECT					getRc()											{ return _rc; }


	int						getMaxHp()										{ return _maxHp; }
	int						getCurHp()										{ return _curHp; }
	float					getSpeed()										{ return _speed; }
	float					getAngle()										{ return _angle; }
	float					getHitAngle()									{ return _hitAngle; }

	bool					getIsAniOnce()									{ return _isAniOnce; }
	bool					getIsArea()										{ return _isArea; }
	bool					getIsStun()										{ return _isStun; }
	bool					getIsDead()										{ return _isDeath; }

	B_STATE					getState()										{ return _state; }
	bossState*				getBossState()									{ return _bossState; }

	image*					getWingImg()									{ return _wingImg; }
	animation*				getWingAni()									{ return _wingAni; }

	image*					getCrystalImg()									{ return _crystalImg; }
	animation*				getCrystalAni()									{ return _crystalAni; }

	player*					getPlayer()										{ return _player; }
	POINTFLOAT				getPlayerPos()									{ return _playerPos; }
	//---------------------------------------------------------------------------------------------------------------------------------------

	//set

	//버려진것 or 즉석으로 추가되는것들
//	void					setCollisionRc(RECT collisionRc)				{ _collisionRc = collisionRc; }
//	void					setCollisionPos(POINTFLOAT collisionPos)		{ _collisionPos = collisionPos; }
//	void					setAniDirection(B_ANIDIRECTION aniDirection)	{ _aniDirection = aniDirection; }
//	void					setWingPos(POINTFLOAT wingPos)					{ _wingPos = wingPos; }
//	void					setCrystalPos(POINTFLOAT crystalPOs)			{ _crystalPos = crystalPOs; }
//	vector<vector<tile*>>	setMap(vector<vector<tile*>> vvMap)				{ _vvMap = vvMap; }
//	void					setImgPos(POINTFLOAT imgPos)					{ _imgPos = imgPos; }

	void					setWingAniIdle() { _wingAni = KEYANIMANAGER->findAnimation("wingIdle"); }
	void					setIsNeedCal(bool isNeedCal)					{ _isNeedCal = isNeedCal; }
	//---------------------------------------------------------------------------------------------------------------------------------------
	void					setImg(image* img)								{ _img = img; }
	void					setAni(animation* ani)							{ _ani = ani; }

	void					setPos(POINTFLOAT pos)							{ _pos = pos; }
	void					setVec(POINTFLOAT vec)							{ _vec = vec; }
	void					setRc(RECT rc)									{ _rc = rc; }


	void					setMaxHp(int maxHp)								{ _maxHp = maxHp; }
	void					setCurHp(int curHp)								{ _curHp = curHp; }
	void					setSpeed(float speed)							{ _speed = speed; }
	void					setAngle(float angle)							{ _angle = angle; }
	void					setHitAngle(float hitAngle)						{ _hitAngle = hitAngle; }

	void					setIsAniOnce(bool isAniOnce)					{ _isAniOnce = isAniOnce; }
	void					setIsArea(bool isClose)							{ _isArea = isClose; }
	void					setIsStun(bool isStun)							{ _isStun = isStun; }
	void					setIsDead(bool isDead)							{ _isDeath = isDead; }

	void					setState(B_STATE state)							{ _state = state; }
	void					setBossState(bossState* bossState)				{ _bossState = bossState; }

	void					setWingImg(image* wingImg)						{ _wingImg = wingImg; }
	void					setWingAni(animation* wingAni)					{ _wingAni = wingAni; }

	void					setCrystalImg(image* crystalImg)				{ _crystalImg = crystalImg; }
	void					setCrystalAni(animation* crystalAni)			{ _crystalAni = crystalAni; }

	player*					setPlayer(player* player)						{ _player = player; }
	POINTFLOAT				setPlayerPos(POINTFLOAT playerPos)				{ _playerPos = playerPos; }
	//---------------------------------------------------------------------------------------------------------------------------------------
};

