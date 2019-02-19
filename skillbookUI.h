#pragma once
#include "gameNode.h"
#include "skillIconList.h"
#include "skillNode.h"
#include "skills.h"
#include "shockNova.h"
#include "stoneShot.h"
#include "chainLightning.h"
#include "flameStrike.h"
#include "searingRush.h"
#include "player.h"

//	==	ui�̴� ��, �÷��̾�� UI�������, �ƴ��� üũ�ϴ� bool �� ���� �ϳ��� ��ũ�ɾ��ּ���.
//	LinkSkillBookUIMode() ���!

//	==	UI�� ���۵� ��, �÷��̾�� setCurSkillName����, ��ų���� ��������ָ�,
//	UI �ٲ� ��ų�� �̸��� �÷��̾ ����ϴ� ��ų������ �����(�̸�����) ==


class skillbookUI : public gameNode
{
private:
	enum CURRENTSKILL
	{
		FLAMESTRIKE,
		CHAINLIGHTNING,
		FROSTFAN,
		REBOUNDINGCICLES,
		SEARINGRUSH,
		SHATTERINGSTRIKE,
		SHOCKNOVA,
		STONESHOT,
		MAX
	};
	skillIconList* _skillIconList;

	struct tagImgSet {
		image* img;
		POINT pos;
		RECT rc;
		int frameX;
		int frameY;
		bool isAct;
	};

	string _curSkillName[4];		//�÷��̾ ������ �ִ� ��ų�� ���� �ּҷ� �޾ƿ�
	

	tagImgSet _arrowBig[2];		//	left , right
	tagImgSet _arrowSmall[2];	//	up	, down
	tagImgSet _cardAtrTab[6];	//	fire, wind, earth, lightning, ice, void 
	tagImgSet _cardEffect;		//	blingbling Img
	tagImgSet _curSkillCard[4];	//	ĳ���Ͱ� ����ִ� ī�� �̹��� (��ų�� ���� ����)
	tagImgSet _skillBookCardImg[5];	//	��ų�Ͽ� ����ִ� ī���̹���	(�ѹ��� �ִ� 5�� ������)

	tagImgSet _skillAtrSmallImg;	//	å�� �ִ� �Ӽ��̹��� ������
	tagImgSet _skillbookEmpty;		//	å
	tagImgSet _skillKindsTxt;		//	��ų���� : ������/���...�̹���
	tagImgSet _skillKindsTxtDot[4];	//	å�Ǳ���, �۾��̹�����
	tagImgSet _upperWinFrame;		//	å�Ǳ���, �׵θ�
	tagImgSet _upperWinMask;		//	å�Ǳ���, �׵θ����� ���ĸ��� ����ũ

	int _curSelectSkillAttr;				//	å����, ���� �Ӽ����� ���?
	int _curSelectSkillKind;		//	å��ġ�� �� ������ ��ų����
	int _curSelectSKillIdx;			//	å����, ����� ��ų?
	
	int _bookAniAdjustX;			//	å �ִϸ��̼�ȿ�� ���� X
	int _skillSelectAdjustY;		//	��ų����â �ִϸ��̼�ȿ�� ���� Y


	bool* _isStart;
	bool _isOpenBook;				//	å ���ƴ�?
	bool _isBookAniEnd;
	bool _isSkillSelectAniEnd;
	bool _arrowAniStart[4];			//	�����¿�

	bool _isCardRender[5];			//	å ī�� 5�忡 ī�� ��������?
	string _cardSkillName[5];		//	å ī�� 5���� ī�� �̸���

	player* _player;



	const int CARD_WID = 106;
	const int CARD_HEI = 163;
	const int UPPERMASK_ALPHA = 150;
	
	const int BOOKANI_ADJUSTX_DEFAULT = -800;
	const int SKILLSELECTANI_ADJUSTY_DEFAULT = 500;
	const int BOOKANI_ADJUSTX_MAX = 0;
	const int SKILLSELECTANI_ADJUSTY_MAX = 0;

	const int BOOKANI_ADJUSTX_MOVESPD = 100;
	const int SKILLSELECTANI_ADJUSTY_MOVESPD = 100;



	//	�׽�Ʈ�� ����
	//string playerSkill[4];
	//bool _isSkillBookUIMode = false;


public:
	skillbookUI();
	~skillbookUI();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void FrameSettingFunc();

	//	===	��ų����â func ===
	void SelectSkillAniFunc();
	void SelectSkillKeyFunc();
	void InitSkillSelectFunc();
	
	//	===	Book Func ===
	void setWhereBookOpen();
	void BookAniFunc();
	void IsCardShowFunc();		//	��ų ���� ���� ��� ī�带 �������� ���
	void InitBookFunc();

	//	==	arrow Ani Func ==
	void ArrowAniFunc();


	void BookOpenAniFunc();

	//	==	��ųã���༭ �װ� �ĸԿ��ִ� �Լ� ==
	void FindSkillAndAdjustToPlayer(string skillName, int idx);

	//	==�Լ�Ű
	//	UI�����ҋ�, �÷��̾��� ��ų�� ��������ּ���
	void setCurSkillName(int idx, string* skillName);
	//	�÷��̾� �̴ֿ���, UI on/off �� bool �� �ϳ� ����
	void LinkSkillBookUIMode(bool* isBookMode) { _isStart = isBookMode; }

	void LinkToPlayer(player* player) {_player = player;}
};

