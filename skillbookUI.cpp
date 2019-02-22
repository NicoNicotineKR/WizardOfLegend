#include "stdafx.h"
#include "skillbookUI.h"


skillbookUI::skillbookUI()
{
}


skillbookUI::~skillbookUI()
{
}

HRESULT skillbookUI::init()
{
	IMAGEMANAGER->addFrameImage("skillbookArrowbig", "images/UIs/spellBookUI/arrowBig.bmp", 186, 248, 3, 4, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillbookArrowsmall", "images/UIs/spellBookUI/arrowSmall.bmp", 132, 176, 3, 4, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillbookCardAtrTab", "images/UIs/spellBookUI/cardAtrTab.bmp", 120, 582, 2, 6, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillbookCardEffect", "images/UIs/spellBookUI/cardEffect.bmp", 636, 163, 6, 1, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillbookCardImg", "images/UIs/spellBookUI/cardImg.bmp", 212, 652, 2, 4, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillAtrSmallImg", "images/UIs/spellBookUI/skillAtrSmallImg.bmp", 69, 54, 3, 2, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillbookEmpty", "images/UIs/spellBookUI/skillbookEmpty.bmp", 684, 837, 1, 1, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillKindsTxt", "images/UIs/spellBookUI/skillKindsTxt.bmp", 160, 176, 1, 4, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("skillKindsTxtDot", "images/UIs/spellBookUI/skillKindsTxtDot.bmp", 320, 128, 2, 4, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("upperWinFrame", "images/UIs/spellBookUI/upperWinFrame.bmp", 734, 267, 1, 1, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("upperWinMask", "images/UIs/spellBookUI/upperWinMask.bmp", 721, 253, 1, 1, true, 0xFF00FF);

	//	외부클래스
	_skillIconList = new skillIconList;
	_skillIconList->init();


	//	애니메이션효과를 위한 조절 XY
	_bookAniAdjustX = BOOKANI_ADJUSTX_DEFAULT;
	_skillSelectAdjustY = SKILLSELECTANI_ADJUSTY_DEFAULT;


	//	1.큰 화살표 - 왼쪽
	_arrowBig[0].img = IMAGEMANAGER->findImage("skillbookArrowbig");
	_arrowBig[0].pos = { 143,357 };
	_arrowBig[0].rc = RectMakeCenter(_arrowBig[0].pos.x, _arrowBig[0].pos.y, _arrowBig[0].img->getFrameWidth(), _arrowBig[0].img->getFrameHeight());
	_arrowBig[0].frameX = 0;
	_arrowBig[0].frameY = 2;
	_arrowBig[0].isAct = false;

	//	큰 화살표 - 오른쪽
	_arrowBig[1].img = IMAGEMANAGER->findImage("skillbookArrowbig");
	_arrowBig[1].pos = { 665,357 };
	_arrowBig[1].rc = RectMakeCenter(_arrowBig[1].pos.x, _arrowBig[1].pos.y, _arrowBig[1].img->getFrameWidth(), _arrowBig[1].img->getFrameHeight());
	_arrowBig[1].frameX = 0;
	_arrowBig[1].frameY = 3 ;
	_arrowBig[1].isAct = false;
	
	//	2.작은 화살표 - 위
	_arrowSmall[0].img = IMAGEMANAGER->findImage("skillbookArrowsmall");
	_arrowSmall[0].pos = { 402,158 };
	_arrowSmall[0].rc = RectMakeCenter(_arrowSmall[0].pos.x, _arrowSmall[0].pos.y, _arrowSmall[0].img->getFrameWidth(), _arrowSmall[0].img->getFrameHeight());
	_arrowSmall[0].frameX = 0;
	_arrowSmall[0].frameY = 0;
	_arrowSmall[0].isAct = false;

	//	작은 화살표 - 위
	_arrowSmall[1].img = IMAGEMANAGER->findImage("skillbookArrowsmall");
	_arrowSmall[1].pos = { 402,215 };
	_arrowSmall[1].rc = RectMakeCenter(_arrowSmall[1].pos.x, _arrowSmall[1].pos.y, _arrowSmall[1].img->getFrameWidth(), _arrowSmall[0].img->getFrameHeight());
	_arrowSmall[1].frameX = 0;
	_arrowSmall[1].frameY = 1;
	_arrowSmall[1].isAct = false;


	//	3.스킬북 우측의 속성탭
	for (int i = 0; i < 6; i++) {
		_cardAtrTab[i].img = IMAGEMANAGER->findImage("skillbookCardAtrTab");
		_cardAtrTab[i].pos = { 710 + 30 , 109 + 108 * i };
		_cardAtrTab[i].rc = RectMakeCenter(_cardAtrTab[i].pos.x, _cardAtrTab[i].pos.y, _cardAtrTab[i].img->getFrameWidth(), _cardAtrTab[i].img->getFrameHeight());
		_cardAtrTab[i].frameX = 1;
		_cardAtrTab[i].frameY = i;
		_arrowSmall[i].isAct = false;
	}

	//	4. 카드 반짝효과
	_cardEffect.img = IMAGEMANAGER->findImage("skillbookCardEffect");
	_cardEffect.pos = { 0,0 };
	_cardEffect.rc = { 0,0,0,0 };
	_cardEffect.frameX = 0;
	_cardEffect.frameY = 0;
	_cardEffect.isAct = false;

	//	5. 스킬북 전, 캐릭터가 들고있는 스킬카드
	for (int i = 0; i < 4; i++) {
		_curSkillCard[i].img = IMAGEMANAGER->findImage("skillbookCardImg");
		//	framewid = 106,
		//	framehei = 163,
		//	각 카드 갭 = 166
		_curSkillCard[i].pos = { 97 + CARD_WID/2 + (i * 166),307 + CARD_HEI/2 };
		_curSkillCard[i].rc = RectMakeCenter(_curSkillCard[i].pos.x, _curSkillCard[i].pos.y, _curSkillCard[i].img->getFrameWidth(), _curSkillCard[i].img->getFrameHeight());

		_curSkillCard[i].frameX = 1;
		if (i == 3) {
			_curSkillCard[i].frameY = 3;
		}
		_curSkillCard[i].frameY = 0;
		_curSkillCard[i].isAct = false;
	}

	
	//	6. 스킬북의 카드 5장~
	for (int i = 0; i < 5; i++) {
		_skillBookCardImg[i].img = IMAGEMANAGER->findImage("skillbookCardImg");
		
		switch(i){
		case 0:		//	-180
			_skillBookCardImg[i].pos = { 169 + CARD_WID/2, 282 + CARD_HEI/2 };
			break;
		case 1:		//	-120
			_skillBookCardImg[i].pos = { 229 + CARD_WID/2, 268 + CARD_HEI/2 };
			break;
		case 2:		//	가운데 기준
			_skillBookCardImg[i].pos = { 349 + CARD_WID / 2, 255 + CARD_HEI / 2 };
			break;
		case 3:		//	+120
			_skillBookCardImg[i].pos = { 469 + CARD_WID / 2, 268 + CARD_HEI / 2 };
			break;
		case 4:		//	+180
			_skillBookCardImg[i].pos = { 529 + CARD_WID / 2, 282 + CARD_HEI / 2 };
			break;
		}
		_skillBookCardImg[i].rc = RectMakeCenter(_skillBookCardImg[i].pos.x, _skillBookCardImg[i].pos.y, CARD_WID, CARD_HEI);
		_skillBookCardImg[i].frameX = 0;
		_skillBookCardImg[i].frameY = 0;
		_skillBookCardImg[i].isAct = false;
	}

	//	7. 스킬책의 상단 속성이미지
	_skillAtrSmallImg.img = IMAGEMANAGER->findImage("skillAtrSmallImg");
	_skillAtrSmallImg.pos = { 379 + 23,160 + 27};
	_skillAtrSmallImg.rc = RectMakeCenter(_skillAtrSmallImg.pos.x, _skillAtrSmallImg.pos.y, _skillAtrSmallImg.img->getFrameWidth(), _skillAtrSmallImg.img->getFrameHeight());
	_skillAtrSmallImg.frameX = 0;
	_skillAtrSmallImg.frameY = 0;
	_skillAtrSmallImg.isAct = false;

	//	8. 스킬책이미지
	_skillbookEmpty.img = IMAGEMANAGER->findImage("skillbookEmpty");
	_skillbookEmpty.pos = { 408, 21 + 429 };
	_skillbookEmpty.rc = RectMakeCenter(_skillbookEmpty.pos.x, _skillbookEmpty.pos.y, _skillbookEmpty.img->getFrameWidth(), _skillbookEmpty.img->getFrameHeight());
	_skillbookEmpty.frameX = 0;
	_skillbookEmpty.frameY = 0;
	_skillbookEmpty.isAct = false;

	//	9. 스킬종류 : 베이직/대시...글씨
	_skillKindsTxt.img = IMAGEMANAGER->findImage("skillKindsTxt");
	_skillKindsTxt.pos = { 399,90 };
	_skillKindsTxt.rc = RectMakeCenter(_skillKindsTxt.pos.x, _skillKindsTxt.pos.y, _skillKindsTxt.img->getFrameWidth(), _skillKindsTxt.img->getFrameHeight());
	_skillKindsTxt.frameX = 0;
	_skillKindsTxt.frameY = 0;
	_skillKindsTxt.isAct = false;

	//	10. 책피기전, 글씨이미지들
	for (int i = 0; i < 4; i++) {
		_skillKindsTxtDot[i].img = IMAGEMANAGER->findImage("skillKindsTxtDot");
		_skillKindsTxtDot[i].pos = { _curSkillCard[i].pos.x, 500 };
		_skillKindsTxtDot[i].rc = RectMakeCenter(_skillKindsTxtDot[i].pos.x, _skillKindsTxtDot[i].pos.y,
			_skillKindsTxtDot[i].img->getFrameWidth(), _skillKindsTxtDot[i].img->getFrameHeight());
		_skillKindsTxtDot[i].frameX = 1;
		_skillKindsTxtDot[i].frameY = i;
		_skillKindsTxtDot[i].isAct = false;
	}

	//	11.	책피기전, 테두리
	_upperWinFrame.img = IMAGEMANAGER->findImage("upperWinFrame");
	_upperWinFrame.pos = { 34 + _upperWinFrame.img->getFrameWidth() / 2,264 + _upperWinFrame.img->getFrameHeight() / 2 };
	_upperWinFrame.rc = RectMakeCenter(_upperWinFrame.pos.x, _upperWinFrame.pos.y,
		_upperWinFrame.img->getFrameWidth(), _upperWinFrame.img->getFrameHeight());
	_upperWinFrame.frameX = 0;
	_upperWinFrame.frameY = 0;
	_upperWinFrame.isAct = false;

	//	12.	책피기전, 내부 마스크
	_upperWinMask.img = IMAGEMANAGER->findImage("upperWinMask");
	_upperWinMask.pos = _upperWinFrame.pos;
	_upperWinMask.rc = RectMakeCenter(_upperWinMask.pos.x, _upperWinMask.pos.y,
		_upperWinMask.img->getFrameWidth(), _upperWinMask.img->getFrameHeight());
	_upperWinMask.frameX = 0;
	_upperWinMask.frameY = 0;
	_upperWinMask.isAct = false;

	_curSelectSkillAttr = 0;
	_curSelectSkillKind = 0;


	
	_isOpenBook = false;
	_isBookAniEnd = false;
	_isSkillSelectAniEnd = false;

	for (int i = 0; i < 4; i++) {
		_arrowAniStart[i] = false;
	}

	for (int i = 0; i < 5; i++) {
		_isCardRender[i] = false;
	}


	_curSkillName[0] = (_player->getCurSkills1()->getName());
	_curSkillName[1] = (_player->getCurSkills2()->getName());
	_curSkillName[2] = (_player->getCurSkills3()->getName());
	_curSkillName[3] = (_player->getCurSkills4()->getName());


	//playerSkill[0] = "FlameStrike";
	//playerSkill[1] = "stoneShot";
	//playerSkill[2] = "thunderingChain";
	//playerSkill[3] = "shockNova";

	//	테스트용 코드
	//_curSkillName[0] = &(playerSkill[0]);
	//_curSkillName[1] = &(playerSkill[1]);
	//_curSkillName[2] = &(playerSkill[2]);
	//_curSkillName[3] = &(playerSkill[3]);

	return S_OK;
}

void skillbookUI::release()
{

	IMAGEMANAGER->deleteImage("skillbookArrowbig");
	IMAGEMANAGER->deleteImage("skillbookArrowsmall");
	IMAGEMANAGER->deleteImage("skillbookCardAtrTab");
	IMAGEMANAGER->deleteImage("skillbookCardEffect");
	IMAGEMANAGER->deleteImage("skillbookCardImg");
	IMAGEMANAGER->deleteImage("skillAtrSmallImg");
	IMAGEMANAGER->deleteImage("skillbookEmpty");
	IMAGEMANAGER->deleteImage("skillKindsTxt");
	IMAGEMANAGER->deleteImage("skillKindsTxtDot");
	IMAGEMANAGER->deleteImage("upperWinFrame");
	IMAGEMANAGER->deleteImage("upperWinMask");

	SAFE_RELEASE(_skillIconList);
	SAFE_DELETE(_skillIconList);
	

}

void skillbookUI::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	//{
	//	_isSkillBookUIMode = true;
	//}


	if (*_isStart) {
		if (!_isOpenBook) {
			if (!_isSkillSelectAniEnd) {
				SelectSkillAniFunc();
			}
			else if (_isSkillSelectAniEnd)
			{
				SelectSkillKeyFunc();
			}
		}
		else if (_isOpenBook)
		{
			if (!_isBookAniEnd) {
				BookAniFunc();
			}
			else if (_isBookAniEnd) {
				
				if (KEYMANAGER->isOnceKeyDown('W')) {
					_arrowAniStart[0] = true;
					_curSelectSkillAttr--;
					_curSelectSKillIdx = 0;
					if (_curSelectSkillAttr < 0)
						_curSelectSkillAttr = ATR_NUMMAX - 1;
					IsCardShowFunc();
				}
				if (KEYMANAGER->isOnceKeyDown('S')) {
					_arrowAniStart[1] = true;
					_curSelectSkillAttr++;
					_curSelectSKillIdx = 0;
					if (_curSelectSkillAttr >= ATR_NUMMAX)
						_curSelectSkillAttr = 0;
					IsCardShowFunc();
				}
				
				if (KEYMANAGER->isOnceKeyDown('A')) {
					_arrowAniStart[2] = true;
					if (_curSelectSKillIdx > 0) {
						_curSelectSKillIdx--;
						IsCardShowFunc();
					}
				}
				if (KEYMANAGER->isOnceKeyDown('D')) {
					_arrowAniStart[3] = true;
					if (_curSelectSKillIdx < SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr).size()-1) {
						_curSelectSKillIdx++;
						IsCardShowFunc();
					}
				}
				
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
					if (SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr).size() != 0) {
						_isOpenBook = false;
						//	@@@@@@@@@@@@@@@@@@@@@괄호 어케쳐야대지......돼지....
						(_curSkillName)[_curSelectSkillKind] = SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr)[_curSelectSKillIdx].name;
						//	(_curSkillName)[_curSelectSkillKind] -> 내가 바꾼 스킬의 이름이 들어이따
						//	이놈을 가지고, 내가 원하는 스킬을 직접 찾아서 쳐먹여주면된다 이말이야.
						FindSkillAndAdjustToPlayer((_curSkillName)[_curSelectSkillKind], _curSelectSkillKind);
						_player->changeSkillIcon(_curSelectSkillKind);
					}
					
				}
						
				//	탭은 임시용 코드
				if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
					_isOpenBook = false;
					InitBookFunc();
				}

				ArrowAniFunc();

			}


		}

		//	이미지 프레임 결정해는 함수
		FrameSettingFunc();
	}
}

void skillbookUI::render()
{

	if (*_isStart)
	{
		if (!_isOpenBook)
		{
			//	책 펼치기 전
			{
				_upperWinFrame.img->render(getMemDC(), _upperWinFrame.rc.left, _upperWinFrame.rc.top + _skillSelectAdjustY);
				_upperWinMask.img->alphaRenderFixed(getMemDC(), _upperWinMask.rc.left, _upperWinMask.rc.top + _skillSelectAdjustY,
					0, 0, _upperWinMask.img->getFrameWidth(), _upperWinMask.img->getFrameHeight(), UPPERMASK_ALPHA);
				for (int i = 0; i < 4; i++) {
					//	현재 가지고있는 스킬카드들 렌더
					_curSkillCard[i].img->frameRender(getMemDC(), _curSkillCard[i].rc.left, _curSkillCard[i].rc.top + _skillSelectAdjustY,
						_curSkillCard[i].frameX, _curSkillCard[i].frameY);
					//	도트글씨로 스킬종류 렌더
					_skillKindsTxtDot[i].img->frameRender(getMemDC(), _skillKindsTxtDot[i].rc.left, _skillKindsTxtDot[i].rc.top + _skillSelectAdjustY,
						_skillKindsTxtDot[i].frameX, _skillKindsTxtDot[i].frameY);
					//	스킬 아이콘 이미지
					_skillIconList->frameRender(_curSkillCard[i].pos.x, _curSkillCard[i].pos.y + _skillSelectAdjustY, (_curSkillName[i]));
				}
			}
			
		}
		else if (_isOpenBook)
		{
			//	책 펼치고
			{
				//	스킬북
				_skillbookEmpty.img->render(getMemDC(), _skillbookEmpty.rc.left + _bookAniAdjustX, _skillbookEmpty.rc.top);
				//	화살표 2개씩
				for (int i = 0; i < 2; i++) {
					_arrowBig[i].img->frameRender(getMemDC(), _arrowBig[i].rc.left + _bookAniAdjustX, _arrowBig[i].rc.top, _arrowBig[i].frameX, _arrowBig[i].frameY);
					_arrowSmall[i].img->frameRender(getMemDC(), _arrowSmall[i].rc.left + _bookAniAdjustX, _arrowSmall[i].rc.top, _arrowSmall[i].frameX, _arrowSmall[i].frameY);

				}
				//	책 상단 속성이미지
				_skillAtrSmallImg.img->frameRender(getMemDC(), _skillAtrSmallImg.rc.left + _bookAniAdjustX, _skillAtrSmallImg.rc.top,
					_skillAtrSmallImg.frameX, _skillAtrSmallImg.frameY);

				//	책 상단 스킬종류 글씨
				_skillKindsTxt.img->frameRender(getMemDC(), _skillKindsTxt.rc.left + _bookAniAdjustX, _skillKindsTxt.rc.top,
					_skillKindsTxt.frameX, _skillKindsTxt.frameY);


				//	스킬북 카드들(5개)
				for (int i = 0; i < 5; i++) {

					//	출력해야하는 카드면,
					if (_isCardRender[i]) {
						//	카드이미지 출력하고
						_skillBookCardImg[i].img->frameRender(getMemDC(), _skillBookCardImg[i].rc.left + _bookAniAdjustX, _skillBookCardImg[i].rc.top,
							_skillBookCardImg[i].frameX, _skillBookCardImg[i].frameY);
						//스킬아이콘이미지 == 해야됨 == (i로 그때그떄 해줘야 겹치는 상태가 맞음)
						_skillIconList->frameRender(_skillBookCardImg[i].pos.x, _skillBookCardImg[i].pos.y, _cardSkillName[i]);

					}
					
					//Rectangle(getMemDC(), _skillBookCardImg[4].rc);
					


				}

				for (int i = 0; i < 6; i++) {
					_cardAtrTab[i].img->frameRender(getMemDC(), _cardAtrTab[i].rc.left + _bookAniAdjustX, _cardAtrTab[i].rc.top,
						_cardAtrTab[i].frameX, _cardAtrTab[i].frameY);
				}


			}
		}
	}

	
	
	
}

void skillbookUI::FrameSettingFunc()
{
	if (!_isOpenBook)
	{
		for (int i = 0; i < 4; i++) {
			_skillKindsTxtDot[i].frameX = 1;
			_curSkillCard[i].frameX = 1;
		}
		_skillKindsTxtDot[_curSelectSkillKind].frameX = 0;
		_curSkillCard[_curSelectSkillKind].frameX = 0;
	}
	else if (_isOpenBook)
	{
		//	다 비선택 프레임
		for (int i = 0; i < 6; i++) {
			_cardAtrTab[i].frameX = 1;
		}
		//	FIRE = 0,	WIND,	EARTH,		ELECTRO,	ICE,	ATRVOID,

		//	선택한 것으로 프레임으로 설정
		_cardAtrTab[_curSelectSkillAttr].frameX = 0;

		switch (_curSelectSkillKind) {
		case BASIC:
			_skillKindsTxt.frameY = 0;

			break;
		case DASH:
			_skillKindsTxt.frameY = 1;

			break;
		case STANDARD:
			_skillKindsTxt.frameY = 2;

			break;
		case SIGNITURE:
			_skillKindsTxt.frameY = 3;

			break;

		}
		switch (_curSelectSkillAttr) {
		case FIRE:
			_skillAtrSmallImg.frameX = 0;
			_skillAtrSmallImg.frameY = 0;
			
			break;
		case WIND:
			_skillAtrSmallImg.frameX = 1;
			_skillAtrSmallImg.frameY = 0;

			break;
		case EARTH:
			_skillAtrSmallImg.frameX = 1;
			_skillAtrSmallImg.frameY = 1;

			break;
		case ELECTRO:
			_skillAtrSmallImg.frameX = 2;
			_skillAtrSmallImg.frameY = 0;

			break;
		case ICE:
			_skillAtrSmallImg.frameX = 0;
			_skillAtrSmallImg.frameY = 1;

			break;
		case ATRVOID:
			_skillAtrSmallImg.frameX = 2;
			_skillAtrSmallImg.frameY = 1;

			break;
		}

		


	}

}

void skillbookUI::SelectSkillAniFunc()
{
	_skillSelectAdjustY -= SKILLSELECTANI_ADJUSTY_MOVESPD;
	if (_skillSelectAdjustY <= SKILLSELECTANI_ADJUSTY_MAX)
		_isSkillSelectAniEnd = true;
	
	
}

void skillbookUI::SelectSkillKeyFunc()
{
	if (KEYMANAGER->isOnceKeyDown('A')) {
		_curSelectSkillKind--;
		if (_curSelectSkillKind < 0)	_curSelectSkillKind = 3;
	}
	if (KEYMANAGER->isOnceKeyDown('D')) {

		_curSelectSkillKind++;
		if (_curSelectSkillKind > 3)	_curSelectSkillKind = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) || KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
		_curSelectSKillIdx = 0;
		_isOpenBook = true;
		InitSkillSelectFunc();
		setWhereBookOpen();
		IsCardShowFunc();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		*(_isStart) = false;
		
	}
}

void skillbookUI::BookOpenAniFunc()
{

}

void skillbookUI::FindSkillAndAdjustToPlayer(string skillName, int idx)
{
	//"FlameStrike";
	//"stoneShot";
	//"thunderingChain";
	//"shockNova";
	//"searingRush";
	skills* tmpSkill;
	if (skillName == "FlameStrike") {
		tmpSkill = _player->getSkillsInfo(FLAMESTRIKE);
	}
	else if (skillName == "stoneShot") {
		tmpSkill = _player->getSkillsInfo(STONESHOT);
	}
	else if (skillName == "thunderingChain") {
		tmpSkill = _player->getSkillsInfo(CHAINLIGHTNING);
	}
	else if (skillName == "shockNova") {
		tmpSkill = _player->getSkillsInfo(SHOCKNOVA);
	}
	else if (skillName == "searingRush") {
		tmpSkill = _player->getSkillsInfo(SEARINGRUSH);
	}
	else {
		tmpSkill = nullptr;
	}

	_player->setPlayerSkill(idx, tmpSkill);

}


void skillbookUI::InitSkillSelectFunc()
{
	_skillSelectAdjustY = SKILLSELECTANI_ADJUSTY_DEFAULT;
	_isSkillSelectAniEnd = false;
}

void skillbookUI::setWhereBookOpen()
{
	string selectSkillName = (_curSkillName[_curSelectSkillKind]);
	_curSelectSkillAttr = SKILLDATABASE->getAttr(selectSkillName);

}

void skillbookUI::BookAniFunc()
{
	_bookAniAdjustX += BOOKANI_ADJUSTX_MOVESPD;
	if (_bookAniAdjustX >= BOOKANI_ADJUSTX_MAX) {
		_isBookAniEnd = true;
	}
}

void skillbookUI::IsCardShowFunc()
{
	// 현재 속성과 종류에 카드 몇장있니
	int cardNum = SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr).size();
	//	5장 중에, 2번째(idx+1) 보고있으면, 전카드  1장
	int beforeCardNum = _curSelectSKillIdx;
	//	5장 중에, 2번째(idx+1) 보고있으면, 후카드 5-2 = 3장
	int afterCardNum = cardNum - (_curSelectSKillIdx + 1);
	

	for (int i = 0; i < 5; i++) {
		_isCardRender[i] = false;
	}

	

	if (cardNum != 0) {
		for (int i = 0; i < 5; i++) {
			int testNum = _curSelectSKillIdx + (i - 2);
			//	0	1	2	3	4
			//	1	2	3	4	5
			if (i < 2) {
				if (i < beforeCardNum) {			//	i == 0  1
					_isCardRender[1-i] = true;
					
					if ( 0 <= _curSelectSKillIdx - (i + 1) && _curSelectSKillIdx - (i+1) <= SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr).size()-1) {
						_cardSkillName[1 - i] = SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr)[_curSelectSKillIdx - (i + 1)].name;
					}
					
				}
			}
			else if (i > 2) {
				if (i-3 < afterCardNum) {			//	i = 3 4  / i-3 -> 0 1
					_isCardRender[i] = true;
					if (0 <= _curSelectSKillIdx + (i - 2) && _curSelectSKillIdx + (i - 2) <= SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr).size() - 1) {
						_cardSkillName[i] = SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr)[_curSelectSKillIdx + (i - 2)].name;
					}
					
				}
			}
			
			else if (i == 2) {
				_isCardRender[2] = true;
				if (SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr).size() != 0) {
					_cardSkillName[i] = SKILLDATABASE->getvSkillInfo(_curSelectSkillKind, _curSelectSkillAttr)[_curSelectSKillIdx + (i - 2)].name;
				}
				
			}
		}
		
	}


}

void skillbookUI::InitBookFunc()
{
	_bookAniAdjustX = BOOKANI_ADJUSTX_DEFAULT;
	_isBookAniEnd = false;
}

void skillbookUI::ArrowAniFunc()
{
	//	상
	if (_arrowAniStart[0]) {
		_arrowSmall[0].frameX++;
		if (_arrowSmall[0].frameX == 3) {
			_arrowAniStart[0] = false;
			_arrowSmall[0].frameX = 0;
		}
	}
	//	하
	if (_arrowAniStart[1]) {
		_arrowSmall[1].frameX++;
		if (_arrowSmall[1].frameX == 3) {
			_arrowAniStart[1] = false;
			_arrowSmall[1].frameX = 0;
		}
	}
	//	좌
	if (_arrowAniStart[2]) {
		_arrowBig[0].frameX++;
		if (_arrowBig[0].frameX == 3) {
			_arrowAniStart[2] = false;
			_arrowBig[0].frameX = 0;
		}
	}
	//	우
	if (_arrowAniStart[3]) {
		_arrowBig[1].frameX++;
		if (_arrowBig[1].frameX == 3) {
			_arrowAniStart[3] = false;
			_arrowBig[1].frameX = 0;
		}
	}
}


void skillbookUI::setCurSkillName(int idx, string* skillName)
{
	_curSkillName[idx] = *skillName;
}