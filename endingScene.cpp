#include "stdafx.h"
#include "endingScene.h"


endingScene::endingScene()
{
}

endingScene::~endingScene()
{
}

HRESULT endingScene::init()
{
	IMAGEMANAGER->addImage("blackWindow", "images/blackBackground.bmp", 1600, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("nikonikotin", "images/introScene/nikonikoteam.bmp", 651, 85, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("niko", "images/introScene/niko.bmp", 651, 323, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smoke", "images/introScene/smoke.bmp", 768, 92, 12, 1, true, RGB(255, 0, 255));

	_nikoImg = IMAGEMANAGER->findImage("niko");
	_teamLogoTxtImg = IMAGEMANAGER->findImage("nikonikotin");
	_smoke = IMAGEMANAGER->findImage("smoke");
	_nikoImgAlpha = 0;
	_teamLogoTxtImgAlpha = 0;
	_smokeImgAlpha = 0;

	_vTxt.clear();
	_moveStrIdx[0] = 0;
	_moveStrIdx[1] = 0;

	_isNikoAlphaFinish = false;
	_isLogoTxtAlphaFinish = false;

	_txtMoveSpd = MOVEUP_SPD_DEFAULT;
	
	AddString("======= < NICO-NICOTEAM > =======");
	AddString("");
	AddString("*팀장             ->       Zeniz");
	AddString("*팀원            ->       유형우");
	AddString("*팀원            ->       박찬희");
	AddString("*팀원            ->       킹도형");
	AddString("");
	AddString("=================================");

	//	재만
	AddString("*맵 에디터          ->      Zeniz");
	AddString("*타일 / 오브젝트    ->      Zeniz");
	AddString("*스킬데이터베이스   ->      Zeniz");
	AddString("*보스 스킬1234     ->      Zeniz");
	AddString("*HP UI             ->      Zeniz");
	AddString("*미니맵 UI         ->      Zeniz");
	AddString("*스킬 쿨다운 UI     ->      Zeniz");
	AddString("*스펠북 내부 UI     ->      Zeniz");
	AddString("*팀 로고           ->      Zeniz");
	AddString("*지금 나오는 엔딩   ->      Zeniz");

	//	형우===
	AddString("*인트로            ->     유형우");
	AddString("*게임커서          ->     유형우");
	AddString("*메인메뉴          ->     유형우");
	AddString("*렌더클리핑        ->     유형우");
	AddString("*맵툴 보조         ->     유형우");
	AddString("*NPC              ->     유형우");
	AddString("*Dialogue클라쓰    ->     유형우");
	AddString("*Camera2D         ->     유형우");
	AddString("*Tab인벤토리       ->     유형우");
	AddString("*Option           ->     유형우");
	AddString("*사운드            ->     유형우");
	
	//	찬희
	AddString("*플레이어          ->     박찬희");
	AddString("*FlameSteak       ->     박찬희");
	AddString("*ChainRightning   ->     박찬희");
	AddString("*NomoShock        ->     박찬희");
	AddString("*StoneShot        ->     박찬희");
	AddString("*SearingRush&Cash ->     박찬희");
	AddString("*스테이트패턴      ->     박찬희");
	AddString("*제트오더활용      ->     박찬희");
	AddString("*타일충돌          ->     박찬희");
	

	//	도형
	AddString("*Astar(완벽쓰)     ->     킹도형");
	AddString("*Enemy(abstract)  ->     킹도형");
	AddString("*Enemy->Ghoul     ->     킹도형");
	AddString("*Enemy->Knight    ->     킹도형");
	AddString("*Enemy->Lancer    ->     킹도형");
	AddString("*는 배양 실패함    ->     킹도형");
	AddString("*Enemy Effect     ->     킹도형");
	AddString("*Boss		     ->     킹도형");
	AddString("*StatePattern     ->     킹도형");
	AddString("*이미지회전클래스   ->     킹도형");

	//	재만2
	AddString("*야 코딩 다했냐?   ->      Zeniz");
	AddString("*요리 담당         ->      Zeniz");
	AddString("*맛있지? 맛있다고 말해 ->  Zeniz");
	AddString("*학원 셔틀         ->      Zeniz");
	AddString("*형우야! 뭐하고있냐 ->      Zeniz");
	AddString("*인생은 담배와 같지 ->      Zeniz");
	AddString("*코딩력은 니코틴과 비례한다 -> Zeniz");
	AddString("*엎고 다시 해      ->      Zeniz");
	
	


	//	형우2
	AddString("*NPC : 빗자루      ->      유형우");
	AddString("*NPC : 미미        ->     유형우");
	AddString("*NPC : 스펠북      ->     유형우");
	AddString("*NPC : 옷장        ->     유형우");
	AddString("*NPC : 여행할아버지 ->     유형우");
	AddString("*인트로 아이디어    ->     유형우");
	AddString("*맵디자인 장인      ->     유형우");
	AddString("*사운드 전체 장인   ->     유형우");
	AddString("*정글러(사실도시락) ->     유형우");
	AddString("*버섯커            ->     유형우");

	//	찬희2
	AddString("*아재 유우머       ->     박찬희");
	AddString("*필라이트 10개     ->     박찬희");
	AddString("*그 중 8개는 혼자마심 ->  박찬희");
	AddString("*사과 10개         ->     박찬희");
	AddString("*꿀맛 장조림 3끼니  ->     박찬희");
	AddString("*아침칼기상        ->     박찬희");
	AddString("*넷플릭스          ->     박찬희");
	AddString("*핫스팟셔틀        ->     박찬희");
	

	//	도형2
	//AddString("*화장실 빌런       ->     킹도형");
	AddString("*휴지 빌런         ->     킹도형");
	AddString("*빵구 빌런         ->     킹도형");
	AddString("*맵 디자인 디렉터   ->     킹도형");
	AddString("*사운드아트 디렉터  ->     킹도형");
	AddString("*치킨을 양보하는 자  ->    킹도형");

	//	외부
	AddString("");
	AddString("");
	AddString("*SPECIAL THANKS TO [0] ->    민동휘");
	AddString("*SPECIAL THANKS TO [1] ->    김도연");
	AddString("*SPECIAL THANKS TO [2] ->    최치영");
	AddString("*SPECIAL THANKS TO [3] ->    수호행님");

	AddString("");
	AddString(" === THANKS FOR WATCHING === ");
	AddString("");
	AddString("");
	AddString("");
	AddString("");


	AddString("=====================================================");
	AddString("<<<<< LOYAL TRIPLE SPECIAL THANKS TO >>>>>>");
	AddString("☆★☆★☆★☆★ 양쌤 ☆★☆★☆★☆★");
	AddString("=====================================================");


	_txtStrNum = _vTxt.size();

	return S_OK;
}

void endingScene::release()
{
	for (int i = 0; i < _vTxt.size(); i++) {
		_vTxt[i]->txt.clear();
	}
	_vTxt.clear();
}

void endingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		SCENEMANAGER->changeScene("mainmenu");
		return;
	}

	AlphaIncreaseFunc();
	SmokeFrameFunc();
	MoveTxts();
	MoveStrIdxCountFunc();
	ChangeMoveSpd();
	EndFunc();

}

void endingScene::render()
{
	_nikoImg->alphaRenderFixed(getMemDC(), WINSIZEX / 3 - 50, WINSIZEY / 3 - 50, 0, 0, 651, 323, _nikoImgAlpha);
	_teamLogoTxtImg->alphaRenderFixed(getMemDC(), WINSIZEX / 3 - 50, WINSIZEY / 3 - 100, 0, 0, 651, 85, _teamLogoTxtImgAlpha);
	_smoke->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 205, WINSIZEY / 2 - 10, _smokeIndex, 0, SMOKE_ALPHA_MAX);

	StringRender();
}

void endingScene::AddString(string str)
{
	tagDrawTxts* tmpTxt = new tagDrawTxts;

	tmpTxt->txt = str;
	tmpTxt->pos.x = TXT_START_X;
	//tmpTxt->pos.y = WINSIZEY + 300 + (_vTxt.size() * TXT_Y_GAP);
	tmpTxt->pos.y = WINSIZEY + 300;
	tmpTxt->rc = RectMake(tmpTxt->pos.x, tmpTxt->pos.y, WINSIZEX - TXT_START_X, TXT_Y_GAP);
	
	_vTxt.push_back(tmpTxt);
}

void endingScene::AlphaIncreaseFunc()
{
	if (!_isNikoAlphaFinish) {
		_nikoImgAlpha += NIKOIMG_ALPHA_AUG;
		if (_nikoImgAlpha > NIKOIMG_ALPHA_MAX) {
			_nikoImgAlpha = NIKOIMG_ALPHA_MAX;
			_isNikoAlphaFinish = true;
		}
	}

	if (!_isLogoTxtAlphaFinish) {
		_teamLogoTxtImgAlpha += TEAMLOGOIMG_ALPHA_AUG;
		if (_teamLogoTxtImgAlpha > TEAMLOGOIMG_ALPHA_MAX) {
			_teamLogoTxtImgAlpha = TEAMLOGOIMG_ALPHA_MAX;
			_isLogoTxtAlphaFinish = true;
		}
			
	}
	
	
}

void endingScene::SmokeFrameFunc()
{
	_smokeImgFrameCount++;
	if (_smokeImgFrameCount > SMOKE_FRAME_SPEED)
	{
		_smokeImgFrameCount = 0;
		_smokeIndex++;

		if (_smokeIndex >= 12)
		{
			_smokeIndex = 0;
		}
	}
}

void endingScene::MoveStrIdxCountFunc()
{
	if (_moveStrIdx[1] < _txtStrNum -1) {
		if (_txtMoveSpd == MOVEUP_SPD_DEFAULT) {
			_startMoveCounter += 1;
		}
		else {
			_startMoveCounter += MOVEUP_SPD_FASTER / MOVEUP_SPD_DEFAULT;
		}
		if (_startMoveCounter > START_MOVE_MAXCOUNT/ MOVEUP_SPD_DEFAULT) {
			_startMoveCounter = 0;
			_moveStrIdx[1]++;
		}
	}

	if (_vTxt[_moveStrIdx[0]]->rc.bottom < -50) {
		_moveStrIdx[0]++;
	}
	
}

void endingScene::MoveTxts()
{
	//for (int i = 0; i < _vTxt.size(); i++) {
	//	//_vTxt[i]->pos.y -= MOVEUP_SPD;
	//	_vTxt[i]->rc.top -= MOVEUP_SPD;
	//	_vTxt[i]->rc.bottom -= MOVEUP_SPD;
	//	//_vTxt[i]->rc = RectMake(_vTxt[i]->pos.x, _vTxt[i]->pos.y, WINSIZEX - TXT_START_X, TXT_Y_GAP);
	//}

	for (int i = _moveStrIdx[0]; i <= _moveStrIdx[1]; i++) {
		_vTxt[i]->rc.top -= _txtMoveSpd;
		_vTxt[i]->rc.bottom -= _txtMoveSpd;
	}


}

void endingScene::ChangeMoveSpd()
{
	if (KEYMANAGER->isStayKeyDown(VK_SPACE) ||
		KEYMANAGER->isStayKeyDown(VK_RETURN) ||
		KEYMANAGER->isStayKeyDown('F')) {
		_txtMoveSpd = MOVEUP_SPD_FASTER;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) ||
		KEYMANAGER->isOnceKeyUp(VK_RETURN) ||
		KEYMANAGER->isOnceKeyUp('F')) {
		_txtMoveSpd = MOVEUP_SPD_DEFAULT;
	}
}

void endingScene::EndFunc()
{
	//if (_vTxt[_vTxt.size() - 1]->rc.bottom < -200) {
	//	SCENEMANAGER->changeScene("introScene");
	//}

	if (_moveStrIdx[0] > _moveStrIdx[1]) {
		SCENEMANAGER->changeScene("introScene");
	}

}

void endingScene::StringRender()
{
	//RECT rcText = RectMake(300, 200, 400, 100);
	//DrawText(getMemDC(), TEXT("Modern Times"), strlen("Modern Times"), &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	HFONT font, oldFont;
	font = CreateFont(60, 0, 0, 0, 1000, 0, 0, 0,
		HANGUL_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("휴먼굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	//for (int i = 0; i < _vTxt.size(); i++) {	
	//	DrawText(getMemDC(), _vTxt[i]->txt.c_str(), strlen(_vTxt[i]->txt.c_str()), &(_vTxt[i]->rc), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//}

	for (int i = _moveStrIdx[0]; i <= _moveStrIdx[1]; i++) {
		DrawText(getMemDC(), _vTxt[i]->txt.c_str(), strlen(_vTxt[i]->txt.c_str()), &(_vTxt[i]->rc), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
