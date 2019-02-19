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

	//특수상태
	IDLE_ACT1,
	IDLE_ACT2,

	//접근했는데 행동 없는 애도있음. // 책 행동없음
	PLAYER_CLOSE_L,
	PLAYER_CLOSE_R,

	//왼쪽상태에서 말거는지  // 책 해당
	IDLE_L_TALK,
	IDLE_R_TALK,

	//대화상태
	TALK,

	//대화가끝나고 1차 UI상태
	UI1_START_L,
	UI1_START_R,
	UI1_ING,
	UI1_ESC,

	//2차 UI 잇는경우 있음 //책해당
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

	//=== 대화창에 쓸 얼굴Key값
	image* _npcFaceImg;
	string _npcFaceText;



	//가져오는애 
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

