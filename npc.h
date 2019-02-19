#pragma once
#include "gameNode.h"

enum Direction
{
	LEFT = 0,
	RIGHT,
};
enum class stateNpc
{
	IDLE = 0,
	IDLE_L,
	IDLE_R,

	IDLE_CHANGE_L,
	IDLE_CHANGE_R,

	//Ư������
	IDLE_ACT1,
	IDLE_ACT2,

	//�����ߴµ� �ൿ ���� �ֵ�����. // å �ൿ����
	PLAYER_CLOSE_L,
	PLAYER_CLOSE_R,

	//���ʻ��¿��� ���Ŵ���  // å �ش�
	IDLE_L_TALK,
	IDLE_R_TALK,

	//��ȭ����
	TALK,

	//��ȭ�������� 1�� UI����
	UI1_START_L,
	UI1_START_R,
	UI1_ING,
	UI1_ESC,

	//2�� UI �մ°�� ���� //å�ش�
	UI2_ING,
	UI2_ESC,

	MAX,
};
class npc : public gameNode
{
protected:
	image* _img;
	animation* _ani;
	string _npcName;

	image* _fButton;
	animation* _fButtonAni;
	bool _isOncePop;

	POINT _pos;
	POINT _size;
	RECT _rc;

	stateNpc _state;

	int _distance;
	bool _playerClose;

	float _idleCount;

	//=== ��ȭâ�� �� ��Key��
	image* _npcFaceImg;
	string _npcFaceText;



	//�������¾� 
	POINTFLOAT _playerPos1;

public:
	npc();
	~npc();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setPos(POINT pos);
	virtual void setPlayerPos(POINTFLOAT playerpos) { _playerPos1 = playerpos; }

	virtual string getNpcFaceText() { return _npcFaceText; }
	virtual image* getNpcFaceImg() { return _npcFaceImg; }
	virtual bool getNpcClosePlayer() { return _playerClose; }
	virtual stateNpc getState() { return _state; }
	virtual void setNpcState(stateNpc state) { _state = state; }
	virtual void isOnceAniPlay(stateNpc EnumNumber);
};

