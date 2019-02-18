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
	IDLE,			// ���̵�...�ε� �ֳ�?
	SPAWN,			// ���� ���̾�α� �������� �����ϴ°�
	CASTING,		// ���� or ������ �����ϵǱ����� ���ֵθ�
	MOCK,			// ��ų �پ��� �����ϴ°� �̋� ������ ���ϵ� (hit ����)
	STUN,			// �����ϴٰ� 1��� ������ ���ϻ��µ�
	SKILL_ONE,		// ����� ȸ��!!!! ȸ����!!!!!
	SKILL_TWO,		// ������ ȸ��!!!! ȸ����!!!!
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
	animation*		_ani;				//�ִϸ��̼�

	POINTFLOAT		_pos;				//�߽� ��ǥ
	POINTFLOAT		_vec;				//���� ��
	RECT			_rc;				//�߽� ��Ʈ(Ÿ���浹�� ����)

	POINTFLOAT		_imgPos;			//�̹��� ��¿� ��ǥ

	RECT			_collisionRc;		//��Ʈ ������ ��Ʈ
	POINTFLOAT		_collisionPos;		//��Ʈ ���� ��ǥ

	image*			_wingImg;			//���� �̹���
	animation*		_wingAni;			//���� �ִϸ��̼�
	POINTFLOAT		_wingPos;			//���� ��ǥ

	int				_maxHp;				//�ִ�ü��
	int				_curHp;				//����ü��
	float			_speed;				//���ǵ�
	float			_angle;				//������ �÷��̾������ ����
	float			_hitAngle;			//������ ƨ�ܳ��� ����


	B_ANIDIRECTION	_aniDirection;		//�ִϸ��̼�
	B_STATE			_state;				//����

	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�

	bossState*		_bossState;
	bossState*		_arrState[static_cast<const int>(B_STATE::MAX)];

	// ȥ��

	player* _player;					//�÷��̾� �ּ� ���� ��������
//	POINTFLOAT _playerPos;				//�÷��̾� ��ǥ ��������
	vector<vector<tile*>> _vvMap;

//	bool _isClose;						//�÷��̾ ������ �ֳ�?(������ Ÿ���� �÷��̾ ������ �갡 Ʈ���)

//	rotateImgMaker* _rotateMaker;
//	image* _effectImg[3][36];
//	RECT _atkRc;
//	POINTFLOAT _atkPos;
//	int _atkIdX;
//	int _atkIdY;
//	int _countIdY;
//	image* _weaponImg[36];

	//���ϻ��´�?
	bool _isStun;
	//�׾���?
	bool _isDead;

private:
//�ܽ�Ʈ �����͵�
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

