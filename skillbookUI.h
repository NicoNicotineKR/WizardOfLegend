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

//	==	ui이닛 후, 플레이어는 UI모드인지, 아닌지 체크하는 bool 값 변수 하나를 링크걸어주세여.
//	LinkSkillBookUIMode() 사용!

//	==	UI가 시작될 때, 플레이어는 setCurSkillName으로, 스킬들을 연결시켜주면,
//	UI 바꾼 스킬들 이름이 플레이어가 사용하는 스킬변수에 저장됨(이름들이) ==


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

	string _curSkillName[4];		//플레이어가 가지고 있는 스킬을 직접 주소로 받아옴
	

	tagImgSet _arrowBig[2];		//	left , right
	tagImgSet _arrowSmall[2];	//	up	, down
	tagImgSet _cardAtrTab[6];	//	fire, wind, earth, lightning, ice, void 
	tagImgSet _cardEffect;		//	blingbling Img
	tagImgSet _curSkillCard[4];	//	캐릭터가 들고있는 카드 이미지 (스킬북 열기 전에)
	tagImgSet _skillBookCardImg[5];	//	스킬북에 들어있는 카드이미지	(한번에 최대 5개 보여줌)

	tagImgSet _skillAtrSmallImg;	//	책에 있는 속성이미지 작은거
	tagImgSet _skillbookEmpty;		//	책
	tagImgSet _skillKindsTxt;		//	스킬종류 : 베이직/대시...이미지
	tagImgSet _skillKindsTxtDot[4];	//	책피기전, 글씨이미지들
	tagImgSet _upperWinFrame;		//	책피기전, 테두리
	tagImgSet _upperWinMask;		//	책피기전, 테두리내부 알파먹은 마스크

	int _curSelectSkillAttr;				//	책에서, 현재 속성탭이 몇번?
	int _curSelectSkillKind;		//	책펼치기 전 선택한 스킬종류
	int _curSelectSKillIdx;			//	책에서, 몇번쨰 스킬?
	
	int _bookAniAdjustX;			//	책 애니메이션효과 조정 X
	int _skillSelectAdjustY;		//	스킬선택창 애니메이션효과 조정 Y


	bool* _isStart;
	bool _isOpenBook;				//	책 펼쳤니?
	bool _isBookAniEnd;
	bool _isSkillSelectAniEnd;
	bool _arrowAniStart[4];			//	상하좌우

	bool _isCardRender[5];			//	책 카드 5장에 카드 렌더할지?
	string _cardSkillName[5];		//	책 카드 5장의 카드 이름들

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



	//	테스트용 변수
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

	//	===	스킬선택창 func ===
	void SelectSkillAniFunc();
	void SelectSkillKeyFunc();
	void InitSkillSelectFunc();
	
	//	===	Book Func ===
	void setWhereBookOpen();
	void BookAniFunc();
	void IsCardShowFunc();		//	스킬 수에 따라서 어느 카드를 오픈할지 계산
	void InitBookFunc();

	//	==	arrow Ani Func ==
	void ArrowAniFunc();


	void BookOpenAniFunc();

	//	==	스킬찾아줘서 그걸 쳐먹여주는 함수 ==
	void FindSkillAndAdjustToPlayer(string skillName, int idx);

	//	==게세키
	//	UI시작할떄, 플레이어의 스킬을 연결시켜주세여
	void setCurSkillName(int idx, string* skillName);
	//	플레이어 이닛에서, UI on/off 할 bool 값 하나 연결
	void LinkSkillBookUIMode(bool* isBookMode) { _isStart = isBookMode; }

	void LinkToPlayer(player* player) {_player = player;}
};

