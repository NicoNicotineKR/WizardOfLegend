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
	image*			_img;				//�̹���
	POINTFLOAT		_imgPos;			//�̹��� ��¿� ��ǥ
	animation*		_ani;				//�ִϸ��̼ǿ� ����

	int				_maxHp;				//���ʹ� �ִ� ü��
	int				_curHp;				//���ʹ� ���� ü��
										
	float			_speed;				//���ʹ� ���ǵ�
	float			_angle;				//���ʹ� ����
	float			_hitAngle;			//������ ƨ�ܳ��� ����
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	POINTFLOAT		_pos;				//�߽� ��ǥ
	RECT			_rc;				//�߽� ��Ʈ(Ÿ��ũ�� , Ÿ���浹������)

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	POINTFLOAT		_vec;				//���ʹ� ���� ��
										
	E_ANIDIRECTION	_aniDirection;		//���ʹ� �ִϸ��̼�
	E_STATE			_state;				//���ʹ� ����
										
	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�(�Ⱦ���������)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];

	RECT			_collisionRc;		//�´� ���� ��Ʈ
	POINTFLOAT		_collisionPos;		//�´� ���� ��ǥ

	// ��������(���ʹ̿��� �ʿ��ؼ� �����ϴ°͵�)�� �ƴѰ�

	player* _player;					//�÷��̾� �ּ� ���� ��������
	POINTFLOAT _playerPos;				//�÷��̾� ��ǥ ��������

	bool _isClose;						//�÷��̾ ������ �ֳ�?(������ Ÿ���� �÷��̾ ������ �갡 Ʈ���)

	list<POINT>				_listPath;
	list<POINT>::iterator	_listIPath;

	float _curCharge;
	float _maxCharge;

	vector<vector<tile*>>* _vvMap;

	//���� �̹���(���¾ֵ��ְ� �ִ¾ֵ����� ���¾ִ� nullptr��������)
	// ���� == 0
	// 1���� 10���� �� 36��
	rotateImgMaker* _rotateMaker;
	image* _effectImg[3][36];
	RECT _atkRc;
	POINTFLOAT _atkPos;
	int _atkIdX;
	int _atkIdY;
	int _countIdY;
	//image* _weaponImg[36];

	//�������´�?
	bool _isHit;
	//�׾���?
	bool _isDead;

	// ����Ʈ�� ����
	int _effectTime;
	int _effect_Shave_PosY;
public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void CamRender();


	//�ּ� ����
	void setPlayerAdress(player* player) { _player = player; }
	POINTFLOAT getPlayerPos() { return _playerPos; }
	void setMapAdress(vector<vector<tile*>>* vvMap) { _vvMap = vvMap; }


	virtual void enemyKeyAnimationInit();
	virtual void enemyArrStateInit();
	virtual void startAni();

	//x�ุ ������ �÷��̾� ������ ������ �ٲ��ִ� �Լ�(������,������ �ƴ�)
	void fixDirection();
	void moveDirection();
	void currentEnemyState();
	virtual void move();

	//������ ������

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

	float getHitAngle() { return _hitAngle; }
	void setHitAngle(float hitAngle) { _hitAngle = hitAngle; }

	void setCurCharge(float curCharge) { _curCharge = curCharge; }
	float getCurCharge() { return _curCharge; }

	void setMaxCharge(float maxCharge) { _curCharge = maxCharge; }
	float getMaxCharge() { return _maxCharge; }

	list<POINT>* getPath() { return &_listPath; }
	list<POINT>::iterator* getIPath() { return &_listIPath; }

	vector<vector<tile*>>* getMap() { return _vvMap; }

	//image* getAtkImg() { return _atkImg; }

	void setAtkIdX(int idx) { _atkIdX = idx; }
	void setAtkIdY(int idy) { _atkIdY = idy; }
	int getCountIdY() { return _countIdY; }
	void setCountIdY(int count) { _countIdY = count; }
	int getEffectTime() { return _effectTime; }
	int getEffectShavePosY() { return _effect_Shave_PosY; }

	POINTFLOAT getAtkPos() { return _atkPos; }
	void setAtkPos(POINTFLOAT atkPos) { _atkPos = atkPos; }
	void setAtkPosX(float x) { _atkPos.x = x; }
	void setAtkPosY(float y) { _atkPos.y = y; }

	RECT getAtkRc() { return _atkRc; }
	void setAtkRc(POINTFLOAT pos) { _atkRc = RectMakeCenter(pos.x, pos.y, _effectImg[0][0]->GetWidth(), _effectImg[0][0]->GetHeight()); }
	void defaultAtkRc() { _atkRc = RectMakeCenter(-1000, -1000, 0, 0); }

	virtual int getAtkRange() abstract;
	virtual int getWeaponRange() abstract;

	inline RECT getCollision() { return _collisionRc; }
	int getCurHP() { return _curHp; }
	void setCurHP(int curHp) { _curHp = curHp; }

	void setIsHit(bool isHit) { _isHit = isHit; }
	bool getIsHit() { return _isHit; }
	void setIsDead(bool isDead) { _isDead = isDead; }
	bool getIsDead() { return _isDead; }
	
};

