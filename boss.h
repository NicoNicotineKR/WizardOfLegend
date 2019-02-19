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
	SLEEP,			// ���� �߰��ϱ��� 
	IDLE,			// ���̵�...�ε� �ֳ�?
	SPAWN,			// ���� ���̾�α� �������� �����ϴ°�
	CASTING,		// ���� or ������ �����ϵǱ����� ���ֵθ�
	MOCK,			// ��ų �پ��� �����ϴ°� �̋� ������ ���ϵ� (hit ����)
	STUN,			// �����ϴٰ� 1��� ������ ���ϻ��µ�
	DASH,			// ��ų 4 ��� �� �뽬
	SKILL_ONE,		// ����� ȸ��!!!! ȸ����!!!!!
	SKILL_TWO,		// ������ ȸ��!! ȸ����!!!!
	SKILL_THREE,	// â 3�� ������
	SKILL_FOUR,		// ���� ����Į ������
	SKILL_FIVE,		// ��帧��
	DEATH_START,	// ���� ���� -> �����ݰ� ���̾�α� ����
	DEATH,			// �����Ǽ� ����� (���� ���ۿ��� ���� ���̾�α� ���� Ű������ ���̾�α� ����Ǹ� �����ǰ� ����)
	MAX
};

class boss : public gameNode
{
private:    
	// ����
	image*			_img;				//�̹���
	POINTFLOAT		_imgPos;			//�̹��� ��¿� ��ǥ
	animation*		_ani;				//�ִϸ��̼�

	POINTFLOAT		_pos;				//�߽� ��ǥ
	POINTFLOAT		_vec;				//���� ��
	RECT			_rc;				//�߽� ��Ʈ(Ÿ���浹�� ����)

	RECT			_collisionRc;		//��Ʈ ������ ��Ʈ
	POINTFLOAT		_collisionPos;		//��Ʈ ���� ��ǥ

	int				_maxHp;				//�ִ�ü��
	int				_curHp;				//����ü��
	float			_speed;				//���ǵ�
	float			_angle;				//������ �÷��̾������ ����
	float			_hitAngle;			//������ ƨ�ܳ��� ����

	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�
	bool			_isClose;			//�÷��̾ ������ �ֳ�?(������ Ÿ���� �÷��̾ ������ �갡 Ʈ���)
	bool			_isStun;			//���ϻ��´�?
	bool			_isDeath;			//�׾���?

	B_ANIDIRECTION	_aniDirection;		//�ִϸ��̼�
	B_STATE			_state;				//����

	bossState*		_bossState;
	bossState*		_arrState[static_cast<const int>(B_STATE::MAX)];

	//����
	image*			_wingImg;			//���� �̹���
	animation*		_wingAni;			//���� �ִϸ��̼�
	POINTFLOAT		_wingPos;			//���� ��ǥ (���� ���� ��ǥ + �����ѹ� �������)

	//���� and ������ crystal img
	image*			_crystalImg;		//ũ����Ż �̹���
	animation*		_crystalAni;		//ũ����Ż �ִϸ��̼�
	POINTFLOAT		_crystalPos;		//ũ����Ż ��ǥ (���� ���� ��ǥ + �����ѹ� �������)

	// ȥ��

	player* _player;					//�÷��̾� �ּ� ���� ��������
	POINTFLOAT _playerPos;				//�÷��̾� ��ǥ ��������
	vector<vector<tile*>> _vvMap;

	//	�縸 �߰���� ----------------------------
	//	��ų
	vector<skills*> _vSkills;


	// �׋� �׶� �߰��ϴ� ����ε� ���������.
	//---------------------------------------------------------------------------------------------------------------------------------------

	int _skill_Usage_Count;				//��ų ��� Ƚ��((ĳ�����Ҷ� 0�̵ǰ� ��ų�������� +1�ϰ� 3���� 4���ɶ� ���ո�� �鰨)
	int _skillNum[5];					//��ų ��ġ���ʰ� ������ ����(�����ؼ� �տ��� ������)

	//---------------------------------------------------------------------------------------------------------------------------------------

private:
//�ܽ�Ʈ ���� ��������
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

