#pragma once
#include "gameNode.h"
#include "tile.h"
#include "rotateImgMaker.h"
#include "throwIceSpear.h"

class bossState;
class player;

//���� ������ Ʈ���.Ʈ�� �������ִ°�(���������� ����) ���� ���� ���� spawn���� �����ϰ� �ִϸ��̼� �� ��������
//
//spawn�� Ű�ִϸ��̼� ������ idle�� ����.idle�� �Ǹ鼭 ���̾�α׵� ���
//
//���̾�α׸� �����ϸ� casting��
//
//casting �� ��ųuse�Լ��� ��ų �� 3����
//
//��ų 3���پ��� mock
//
//->mock���� �ȸ����� casting �� �ݺ�
//
//->mock���� ������ stun->stun�ð����� ������ casting �� �ݺ�
//
//
//�� �ݺ��ϴٰ� ü�� �ٴ�� ���� ��ŸƮ->���̾�α� ���
//
//���̾�α� �����ϸ� death�ϰ� ����


enum class B_STATE
{
	SLEEP = 0,			// ���� �߰��ϱ���																				// o			// ���� ����
	SPAWN = 1,			// ���� ���̾�α� �������� �����ϴ°�																// o		    // ���� �۾���
	IDLE = 2,			// ���̵�...�ε� �ֳ�?																			// o		    // ���� Ŀ�� -> ���̵�����
	CASTING = 3,		// ���� or ������ �����ϵǱ����� ���ֵθ�															// o			// ���� �۾���
	MOCK = 4,			// ��ų �پ��� �����ϴ°� �̋� ������ ���ϵ� (hit ����)												// x			// ���� Ŀ��
	STUN = 5,			// �����ϴٰ� 1��� ������ ���ϻ��µ�															// x			// ���� Ŀ��
	DASH = 6,			// ��ų 4 ��� �� �뽬																			// x			// ������ ����
	SKILL_ONE = 7,		// ����� ȸ��!!!! ȸ����!!!!!																	// x			// ������ ����
	SKILL_TWO = 8,		// ������ ȸ��!! ȸ����!!!!																		// x			// ������ ����
	SKILL_THREE = 9,	// â 3�� ������																					// o 			// ������ ����
	SKILL_FOUR = 10,	// ���� ����Į ������																				// x			// ������ ����
	SKILL_FIVE = 11,	// ��帧��																						// x			// ������ ����
	DEATH_START = 12,	// ���� ���� -> �����ݰ� ���̾�α� ����															// x			// ���� Ŀ��
	DEATH = 13,			// �����Ǽ� ����� (���� ���ۿ��� ���� ���̾�α� ���� Ű������ ���̾�α� ����Ǹ� �����ǰ� ����)		// x			// ���� �۾���
	MAX
};
//�������͵�
//	POINTFLOAT		_imgPos;			//�̹��� ��¿� ��ǥ
//	RECT			_collisionRc;		//��Ʈ ������ ��Ʈ
//	POINTFLOAT		_collisionPos;		//��Ʈ ���� ��ǥ
//	B_ANIDIRECTION	_aniDirection;		//�ִϸ��̼�
//	POINTFLOAT		_wingPos;			//���� ��ǥ (���� ���� ��ǥ + �����ѹ� �������)
//	POINTFLOAT		_crystalPos;		//ũ����Ż ��ǥ (���� ���� ��ǥ + �����ѹ� �������)

//	vector<vector<tile*>> _vvMap;
//	void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }

class boss : public gameNode
{
private:    
	// ����
	image*			_img;				//�̹���
	animation*		_ani;				//�ִϸ��̼�

	POINTFLOAT		_vec;				//���� ��
	POINTFLOAT		_pos;				//�߽� ��ǥ
	RECT			_rc;				//�߽� ��Ʈ(�´�����������)

	int				_maxHp;				//�ִ�ü��
	int				_curHp;				//����ü��
	float			_speed;				//���ǵ�
	float			_angle;				//������ �÷��̾������ ����
	float			_hitAngle;			//������ ƨ�ܳ��� ����

	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�
	bool			_isArea;			//�÷��̾ ������ �ֳ�?(������ Ÿ���� �÷��̾ ������ �갡 Ʈ���)
//	bool			_isHit;				//�¾Ҵ�?			-> mock ���¿��� isHit�� Ʈ�簡�Ǹ� stun���·� ������. isHit�ɶ����� 
	bool			_isStun;			//���ϻ��´�?
	bool			_isDeath;			//�׾���?

	B_STATE			_state;				//����
	int				_direction;			//�뽬������ �� ����

	bossState*		_bossState;
	bossState*		_arrState[static_cast<const int>(B_STATE::MAX)];

	//����
	image*			_wingImg;			//���� �̹���
	animation*		_wingAni;			//���� �ִϸ��̼�

	//���� and ������ crystal img
	image*			_crystalImg;		//ũ����Ż �̹���
	animation*		_crystalAni;		//ũ����Ż �ִϸ��̼�

	


	// ȥ��
	player* _player;					//�÷��̾� �ּ� ���� ��������
	POINTFLOAT _playerPos;				//�÷��̾� ��ǥ ��������

	//	�縸 �߰���� ----------------------------
	//	��ų
	//vector<skills*> _vSkills;
	throwIceSpear* _skill3;

	// �׋� �׶� �߰��ϴ� ����ε� ���������.
	//---------------------------------------------------------------------------------------------------------------------------------------

	int _skill_Usage_Count;				//��ų ��� Ƚ��((ĳ�����Ҷ� 0�̵ǰ� ��ų�������� +1�ϰ� 3���� 4���ɶ� ���ո�� �鰨)
	int _skillNum[5];					//��ų ��ġ���ʰ� ������ ����(�����ؼ� �տ��� ������)
	
	bool _isNeedCal;					//��� �ʿ��ϴ�?



	//---------------------------------------------------------------------------------------------------------------------------------------

private:
//�ܽ�Ʈ ���� ��������
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

	//���� Ű �ִϸ��̼� �ʱ�ȭ
	void bossKeyAnimationInit();
	//���� ���� �迭 �ʱ�ȭ
	void bossArrStateInit();

	//���� Ű �ִϸ��̼� �ʱ�ȭ
	void wingKeyAnimationInit();
	
	//ũ����Ż Ű �ִϸ��̼��ʱ�ȭ
	void crystalKeyAnimationInit();



	//���� ����� ���¿����� �������� �������ִ� �Լ�
	void bossCurrentState();
	//���¿� ���⿡���� �ִϸ��̼� �������ִ� �Լ�
	void startAni();

	//�ʿ��ҰŰ����� ����
	//void fixDirection();
	//void moveDirection();


	// �׋� �׶� �߰��ϴ� ����ε� ���������.
	//---------------------------------------------------------------------------------------------------------------------------------------
	static void wingIdle(void* obj);

	void skillShuffle();
	void useSkill();

	//���� �߰� or ������ ����� ���Լ� �����
	void setBossSpawn();

	//���̾�α� ������ ĳ���ø�� ���°� - �������� ������
	void setBossStateCasting();

	void RcCollideBySkillFunc(RECT* skillRc, int dmg, bool* isHit);
	void DistanceBySkillFunc(POINTFLOAT skillPos, float range, int dmg, bool* isHit);

	//---------------------------------------------------------------------------------------------------------------------------------------
	
	//get
	//�������� or �Ｎ���� �߰��Ǵ°͵�
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

	//�������� or �Ｎ���� �߰��Ǵ°͵�
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

