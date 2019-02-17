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
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	POINTFLOAT		_pos;				//�߽� ��ǥ �갡 ������ �߽���ǥ�� �꺯�ϸ� ������ �ٺ���
	RECT			_rc;				//�߽� ��Ʈ(Ÿ��ũ��)

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	POINTFLOAT		_vec;				//���ʹ� ���� ��
										
	E_ANIDIRECTION	_aniDirection;		//���ʹ� �ִϸ��̼�
	E_STATE			_state;				//���ʹ� ����
										
	bool			_isAniOnce;			//�ִϸ��̼� �ѹ��� ����� �Ұ�(�Ⱦ���������)

	enemyState*		_enemyState;
	enemyState*		_arrState[static_cast<const int>(E_STATE::MAX)];

	RECT			_collisionRc;		//�浹������ ��Ʈ
	POINTFLOAT		_collisionPos;		//�浹���� ��ǥ

	// ��������(���ʹ̿��� �ʿ��ؼ� �����ϴ°͵�)�� �ƴѰ�

	player* _player;					//�÷��̾� �ּ� ���� ��������
	POINTFLOAT _playerPos;				//�÷��̾� ��ǥ ��������

	bool _isClose;						//�÷��̾ ������ �ֳ�?(������ Ÿ���� �÷��̾ ������ �갡 Ʈ���)

	list<POINT>				_listPath;
	list<POINT>::iterator	_listIPath;

	float _curCharge;
	float _maxCharge;

	vector<vector<tile*>> _vvMap;

	//���� �̹���(���¾ֵ��ְ� �ִ¾ֵ����� ���¾ִ� nullptr��������)
	// ���� == 0
	// 1���� 10���� �� 36��
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


	//�ּ� ����
	void setPlayerAdress(player* player) { _player = player; }
	POINTFLOAT getPlayerPos() { return _playerPos; }
	void setMapAdress(vector<vector<tile*>> vvMap) { _vvMap = vvMap; }


	virtual void enemyKeyAnimationInit();
	virtual void enemyArrStateInit();
	virtual void startAni();

	//x�ุ ������ �÷��̾� ������ ������ �ٲ��ִ� �Լ�(������,������ �ƴ�)
	void fixDirection();
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

