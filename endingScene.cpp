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
	AddString("*����             ->       Zeniz");
	AddString("*����            ->       ������");
	AddString("*����            ->       ������");
	AddString("*����            ->       ŷ����");
	AddString("");
	AddString("=================================");

	//	�縸
	AddString("*�� ������          ->      Zeniz");
	AddString("*Ÿ�� / ������Ʈ    ->      Zeniz");
	AddString("*��ų�����ͺ��̽�   ->      Zeniz");
	AddString("*���� ��ų1234     ->      Zeniz");
	AddString("*HP UI             ->      Zeniz");
	AddString("*�̴ϸ� UI         ->      Zeniz");
	AddString("*��ų ��ٿ� UI     ->      Zeniz");
	AddString("*����� ���� UI     ->      Zeniz");
	AddString("*�� �ΰ�           ->      Zeniz");
	AddString("*���� ������ ����   ->      Zeniz");

	//	����===
	AddString("*��Ʈ��            ->     ������");
	AddString("*����Ŀ��          ->     ������");
	AddString("*���θ޴�          ->     ������");
	AddString("*����Ŭ����        ->     ������");
	AddString("*���� ����         ->     ������");
	AddString("*NPC              ->     ������");
	AddString("*DialogueŬ��    ->     ������");
	AddString("*Camera2D         ->     ������");
	AddString("*Tab�κ��丮       ->     ������");
	AddString("*Option           ->     ������");
	AddString("*����            ->     ������");
	
	//	����
	AddString("*�÷��̾�          ->     ������");
	AddString("*FlameSteak       ->     ������");
	AddString("*ChainRightning   ->     ������");
	AddString("*NomoShock        ->     ������");
	AddString("*StoneShot        ->     ������");
	AddString("*SearingRush&Cash ->     ������");
	AddString("*������Ʈ����      ->     ������");
	AddString("*��Ʈ����Ȱ��      ->     ������");
	AddString("*Ÿ���浹          ->     ������");
	

	//	����
	AddString("*Astar(�Ϻ���)     ->     ŷ����");
	AddString("*Enemy(abstract)  ->     ŷ����");
	AddString("*Enemy->Ghoul     ->     ŷ����");
	AddString("*Enemy->Knight    ->     ŷ����");
	AddString("*Enemy->Lancer    ->     ŷ����");
	AddString("*�� ��� ������    ->     ŷ����");
	AddString("*Enemy Effect     ->     ŷ����");
	AddString("*Boss		     ->     ŷ����");
	AddString("*StatePattern     ->     ŷ����");
	AddString("*�̹���ȸ��Ŭ����   ->     ŷ����");

	//	�縸2
	AddString("*�� �ڵ� ���߳�?   ->      Zeniz");
	AddString("*�丮 ���         ->      Zeniz");
	AddString("*������? ���ִٰ� ���� ->  Zeniz");
	AddString("*�п� ��Ʋ         ->      Zeniz");
	AddString("*�����! ���ϰ��ֳ� ->      Zeniz");
	AddString("*�λ��� ���� ���� ->      Zeniz");
	AddString("*�ڵ����� ����ƾ�� ����Ѵ� -> Zeniz");
	AddString("*���� �ٽ� ��      ->      Zeniz");
	
	


	//	����2
	AddString("*NPC : ���ڷ�      ->      ������");
	AddString("*NPC : �̹�        ->     ������");
	AddString("*NPC : �����      ->     ������");
	AddString("*NPC : ����        ->     ������");
	AddString("*NPC : �����Ҿƹ��� ->     ������");
	AddString("*��Ʈ�� ���̵��    ->     ������");
	AddString("*�ʵ����� ����      ->     ������");
	AddString("*���� ��ü ����   ->     ������");
	AddString("*���۷�(��ǵ��ö�) ->     ������");
	AddString("*����Ŀ            ->     ������");

	//	����2
	AddString("*���� �����       ->     ������");
	AddString("*�ʶ���Ʈ 10��     ->     ������");
	AddString("*�� �� 8���� ȥ�ڸ��� ->  ������");
	AddString("*��� 10��         ->     ������");
	AddString("*�ܸ� ������ 3����  ->     ������");
	AddString("*��ħĮ���        ->     ������");
	AddString("*���ø���          ->     ������");
	AddString("*�ֽ��̼�Ʋ        ->     ������");
	

	//	����2
	//AddString("*ȭ��� ����       ->     ŷ����");
	AddString("*���� ����         ->     ŷ����");
	AddString("*���� ����         ->     ŷ����");
	AddString("*�� ������ ����   ->     ŷ����");
	AddString("*�����Ʈ ����  ->     ŷ����");
	AddString("*ġŲ�� �纸�ϴ� ��  ->    ŷ����");

	//	�ܺ�
	AddString("");
	AddString("");
	AddString("*SPECIAL THANKS TO [0] ->    �ε���");
	AddString("*SPECIAL THANKS TO [1] ->    �赵��");
	AddString("*SPECIAL THANKS TO [2] ->    ��ġ��");
	AddString("*SPECIAL THANKS TO [3] ->    ��ȣ���");

	AddString("");
	AddString(" === THANKS FOR WATCHING === ");
	AddString("");
	AddString("");
	AddString("");
	AddString("");


	AddString("=====================================================");
	AddString("<<<<< LOYAL TRIPLE SPECIAL THANKS TO >>>>>>");
	AddString("�١ڡ١ڡ١ڡ١� ��� �١ڡ١ڡ١ڡ١�");
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
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("�޸ձ���"));
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
