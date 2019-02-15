#include "stdafx.h"
#include "skillCooldownUI.h"


skillCooldownUI::skillCooldownUI()
{
}


skillCooldownUI::~skillCooldownUI()
{
}

HRESULT skillCooldownUI::init()
{
	IMAGEMANAGER->addFrameImage("skillBorder", "images/UIs/skillUI/skillIconFrame.bmp", 120, 60, 2, 1, true, 0xFF00FF);
	IMAGEMANAGER->addImage("skillMask", "images/UIs/skillUI/skillBorderMask.bmp", 60, 60, true, 0xFF00FF);
	IMAGEMANAGER->addImage("quarterMask1", "images/UIs/skillUI/skillBorderMaskQuarter1.bmp", 60, 60, true, 0xFF00FF);
	IMAGEMANAGER->addImage("quarterMask2", "images/UIs/skillUI/skillBorderMaskQuarter2.bmp", 60, 60, true, 0xFF00FF);
	IMAGEMANAGER->addImage("quarterMask3", "images/UIs/skillUI/skillBorderMaskQuarter3.bmp", 60, 60, true, 0xFF00FF);

	_iconList = new skillIconList;
	_iconList->init();
	_printNum = new printNumber;
	_printNum->init();

	for (int i = 0; i < 6; i++)
	{
		_skills[i].name.clear();
		_skills[i].pos = { ICONSTART_X + i * ICONGAB, ICONSTART_Y };

		_skills[i].borderImg = IMAGEMANAGER->findImage("skillBorder");
		_skills[i].borderRc = RectMakeCenter(_skills[i].pos.x, _skills[i].pos.y, 60, 60);
		
		_skills[i].iconImg = nullptr;
		_skills[i].iconRc = RectMakeCenter(_skills[i].pos.x, _skills[i].pos.y, 42, 42);
		
		_skills[i].maskImg = new image;
		_skills[i].maskImg->init("images/UIs/skillUI/skillBorderMask.bmp", 60, 60, true, 0xFF00FF);
		_skills[i].maskImg->setTransColor(true, 0xFF00FF);


		_skills[i].maskImgDefault = IMAGEMANAGER->findImage("skillMask");
		_skills[i].maskImgDefault->setTransColor(true, 0xFF00FF);

		_skills[i].totalReloadNum = nullptr;
		_skills[i].curReloadNum = nullptr;
		_skills[i].coolDownTime = nullptr;
		_skills[i].curTime = nullptr;
		_skills[i].lastingTime = 0;

		_skills[i].curMaskWid = MASK_MAX_WID;
		_skills[i].lastTimeRatio = 0.f;
		_skills[i].curTimeRatio = 0.f;

		_skills[i].angle = PI / 2 * 3;
		_skills[i].preAngle = _skills[i].angle;

		for (int j = 0; j < 3; j++) {
			_skills[i].polygonPos[j] = { 30, 30 };
		}
		_skills[i].isPrepareBlt = false;
		
		_skills[i].maskAlpha = 0;
	}

	//���͸���ũ �̴�
	_maskQuarter[0] = IMAGEMANAGER->findImage("quarterMask1");
	_maskQuarter[1] = IMAGEMANAGER->findImage("quarterMask2");
	_maskQuarter[2] = IMAGEMANAGER->findImage("quarterMask3");
	

	
	//	�׽�Ʈ���ڵ�
	//	===		�÷��̾� ������		=====
	testTotalReloadNum = 4;
	testCurReloadNum = 0;
	testCoolDownTime = 2.0f;
	testTimer = 0;
	testIsUse = false;

	//	===	 �÷��̾� ��뿹(��ų�Է�) 	=====
	ChangeSkill(0, "FlameStrike", &testTotalReloadNum, &testCurReloadNum, &testCoolDownTime, &testTimer);

	return S_OK;
}

void skillCooldownUI::release()
{
}

void skillCooldownUI::update()
{
	//	�׽�Ʈ���ڵ�
	//	=======�÷��̾� �����ϼ��� ==========
	
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) 
	{
		if (testCurReloadNum > 0) {
			testCurReloadNum--;
			testTimer -= testCoolDownTime;
		}

		this->UseIdxSkill(0);
		
	}

	if (_skills[0].isStart) 
	{
		testTimer += TIMEMANAGER->getElapsedTime();
		testCurReloadNum = testTimer / testCoolDownTime;
	}
	

	for (int i = 0; i < 6; i++) {
		//	��ų���¾ִ� ��������
		
		if (_skills[i].iconImg == nullptr) continue;

		if (!_skills[i].isPrepareBlt) {
			float gapEndReload;	//	1�� ������ ��������� �����ð�
			gapEndReload = ((*_skills[i].coolDownTime)*((*_skills[i].curReloadNum)+1)) - *(_skills[i].curTime);	//	(�ѹߴ�ð�*������ ����+1) - ���� �����ؿ� �ð�.
			//	�������� 0.1�� ���Ұ�, && ��������+1 �� �ִ��������� �ƴϸ�, -> ���������̸�
			if (gapEndReload <= 0.05f && ((*_skills[i].curReloadNum) + 1) != *_skills[i].totalReloadNum) {
				_skills[i].isPrepareBlt = true;
				_skills[i].maskAlpha = MASK_ALPHA / (*_skills[i].totalReloadNum)*   ((*_skills[i].totalReloadNum) - ((*_skills[i].curReloadNum)));
			}
		}
		

		//	�����ȵư�, curTime�� 0�̶��, �� ������ �����ϴ� �ܰ���,
		if (_skills[i].isPrepareBlt) {
			//	����ũ�������� �����ؿ���
			_skills[i].isPrepareBlt = false;
			BitBltMask(i);
			//PartialClockwiseFunc(i);
			
		}

		//	�� ä��������,
		if (*(_skills[i].curReloadNum) == *(_skills[i].totalReloadNum))
		{
			_skills[i].isStart = false;
			_skills[i].angle = PI / 2 * 3;
			_skills[i].preAngle = _skills[i].angle;
		}


		//	��ų����� ���۵�����, 
		if (_skills[i].isStart) {

			//	�����ð� �������
			_skills[i].lastingTime = CalLastingTime(i);
			//	���� �������
			_skills[i].lastTimeRatio = CalLastTimeRatio(i);
			_skills[i].curTimeRatio = CalCurTimeRatio(i);
			_skills[i].proceedRatio = CalProceedRatio(i);

			//	�ð�������� ������ ��� (����ũ��ĥ)
			ClockwiseMaskFunc(i);
			//	����ũ ���İ� �� ����

			//	���� ���ι����� ��°��α��� �������
			//_skills[i].curMaskWid = CalMaskWid(i);
			
		}
	}
}

void skillCooldownUI::render()
{
	for (int i = 0; i < 6; i++) {

		//	��ų â �׵θ�
		if (i != 3)
			_skills[i].borderImg->alphaFrameRender(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top, 0, 0, BORDER_ALPHA);
		else
			_skills[i].borderImg->alphaFrameRender(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top, 1, 0, BORDER_ALPHA);

		//	��ų �̹����� �ִٸ�(��ų�� ž�������)
		if (_skills[i].iconImg != nullptr) {
			_skills[i].iconImg->frameRender(getMemDC(), _skills[i].iconRc.left, _skills[i].iconRc.top,
				_skills[i].iconImg->getFrameX(), _skills[i].iconImg->getFrameY());

			//	����ũ
			_skills[i].maskImg->alphaRenderFixed(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top,
				0, 0, _skills[i].borderImg->getFrameWidth(), _skills[i].borderImg->getFrameHeight(),
				_skills[i].maskAlpha);


			//	����ũ ��� & ��ٿ� �����ð� ���� ���
			if (*(_skills[i].curReloadNum) <= 0) {
				//	����ũ

				//	������
				//_skills[i].maskImg->alphaRenderFixed(getMemDC(), _skills[i].borderRc.right - _skills[i].curMaskWid, _skills[i].borderRc.top,
				//	0, 0, _skills[i].curMaskWid, 60, MASK_ALPHA);
				//_skills[i].maskImg->setTransColor(true, 0xFF00FF);

				//	����ũ
				//_skills[i].maskImg->alphaRenderFixed(getMemDC(), _skills[i].borderRc.left, _skills[i].borderRc.top,
				//	0, 0, _skills[i].borderImg->getFrameWidth(), _skills[i].borderImg->getFrameHeight(), 
				//	_skills[i].maskAlpha);

				
				//	��Ÿ�� �����ð� ����
				_printNum->renderNum((int)_skills[i].lastingTime % 10, _skills[i].borderRc.left + 15, _skills[i].borderRc.top + BORDER_SIZE / 2);		//	1���ڸ�
				_printNum->renderNum(11, _skills[i].borderRc.left + BORDER_SIZE / 2, _skills[i].borderRc.top + BORDER_SIZE / 2);						//	.
				_printNum->renderNum((int)(_skills[i].lastingTime * 10) % 10, _skills[i].borderRc.right - 15, _skills[i].borderRc.top + BORDER_SIZE / 2);	//�Ҽ���.1
				
			}

			//	���� ��ų�� ���
			//	���������� 1�̻���,
			if (*(_skills[i].totalReloadNum) > 1 && *(_skills[i].curReloadNum) >= 1) {
				_printNum->renderNum(*(_skills[i].curReloadNum), _skills[i].pos.x, _skills[i].pos.y);
			}

		}

		
		if (_skills[i].iconImg != nullptr) {
			
		}
		
	}

	//char str[128];
	//sprintf_s(str, "testTotalReloadNum : %d", testTotalReloadNum);
	//TextOut(getMemDC(), 50, 300, str, strlen(str));
	//sprintf_s(str, "[0]TotalReloadNum : %d", *_skills[0].totalReloadNum);
	//TextOut(getMemDC(), 50, 320, str, strlen(str));
	//sprintf_s(str, "testTimer : %f", testTimer);
	//TextOut(getMemDC(), 50, 340, str, strlen(str));
	//sprintf_s(str, "[0]curTime : %f", *_skills[0].curTime);
	//TextOut(getMemDC(), 50, 360, str, strlen(str));
	//sprintf_s(str, "testCurReloadNum : %d", testCurReloadNum);
	//TextOut(getMemDC(), 50, 380, str, strlen(str));
	//sprintf_s(str, "[0]curReloadNum : %d", *_skills[0].curReloadNum);
	//TextOut(getMemDC(), 50, 400, str, strlen(str));
	//sprintf_s(str, "[0]curTimeRatio : %f", _skills[0].curTimeRatio);
	//TextOut(getMemDC(), 50, 420, str, strlen(str));
	//sprintf_s(str, "[0]angle : %f", _skills[0].angle);
	//TextOut(getMemDC(), 50, 440, str, strlen(str));
	//sprintf_s(str, "[0]maskAlpha : %d", _skills[0].maskAlpha);
	//TextOut(getMemDC(), 50, 460, str, strlen(str));
}

void skillCooldownUI::ChangeSkill(int idx, string name, int* totalReloadedNum, int* curReloadNum, float* coolDownTime, float* curTimer)
{
	_skills[idx].name = name;
	_skills[idx].iconImg = _iconList->getIconsImg();

	POINT iconFrame = _iconList->FindSkillIdx(name);

	_skills[idx].iconImg->SetFrameX(iconFrame.x);
	_skills[idx].iconImg->SetFrameY(iconFrame.y);

	_skills[idx].totalReloadNum = totalReloadedNum;
	_skills[idx].curReloadNum = curReloadNum;
	_skills[idx].coolDownTime = coolDownTime;
	_skills[idx].curTime = curTimer;
	_skills[idx].lastingTime = CalLastingTime(idx);
	_skills[idx].maskAlpha = MASK_ALPHA;
}

void skillCooldownUI::DropSkill(int idx)
{
	_skills[idx].iconImg = nullptr;
	_skills[idx].totalReloadNum = nullptr;
	_skills[idx].curReloadNum = nullptr;
	_skills[idx].coolDownTime = nullptr;
	_skills[idx].curTime = nullptr;
	_skills[idx].lastingTime = 0;
	_skills[idx].curMaskWid = MASK_MAX_WID;

}

float skillCooldownUI::CalLastingTime(int idx)
{
	
	return *(_skills[idx].coolDownTime) - *(_skills[idx].curTime);
}

float skillCooldownUI::CalLastTimeRatio(int idx)
{
	if (*(_skills[idx].coolDownTime) == 0)
		return 0;
	return _skills[idx].lastingTime / *(_skills[idx].coolDownTime);
}

float skillCooldownUI::CalCurTimeRatio(int idx)
{
	if (*(_skills[idx].coolDownTime) == 0)
		return 0;
	return *(_skills[idx].curTime) / *(_skills[idx].coolDownTime);
}

float skillCooldownUI::CalProceedRatio(int idx)
{
	if (*(_skills[idx].coolDownTime) == 0)
		return 0;

	float tmpRatio = TIMEMANAGER->getElapsedTime() / *(_skills[idx].coolDownTime);
	return tmpRatio;
}

float skillCooldownUI::CalMaskWid(int idx)
{	
	return MASK_MAX_WID * _skills[idx].lastTimeRatio;
}

void skillCooldownUI::BitBltMask(HDC destHDC, HDC sourHDC)
{
	BitBlt(destHDC, 0, 0,
		MASK_MAX_WID, MASK_MAX_WID, 
		sourHDC, 0, 0, SRCCOPY);
}

void skillCooldownUI::BitBltMask(int idx)
{
	BitBlt(_skills[idx].maskImg->getMemDC(), 0, 0,
		MASK_MAX_WID, MASK_MAX_WID,
		_skills[idx].maskImgDefault->getMemDC(), 0, 0, SRCCOPY);
}

void skillCooldownUI::BitBltQuarterMask(int idx, int quarter)
{
	BitBlt(_skills[idx].maskImg->getMemDC(), 0, 0,
		MASK_MAX_WID, MASK_MAX_WID,
		_maskQuarter[quarter-1]->getMemDC(), 0, 0, SRCCOPY);
}

void skillCooldownUI::ClockwiseMaskFunc(int idx)
{
	_skills[idx].preAngle = _skills[idx].angle;						//	�������� ���̺�
	if(_skills[idx].curTimeRatio != 0) {
		_skills[idx].angle = (PI/2*3) + (PI*2 * _skills[idx].curTimeRatio);		//	360�� ��ü����, ������ ������ŭ�� �����ظ�ŭ ���� �����Ѵ�.		//	0���� ������ �˸�è
		//_skills[idx].angle += (PI * 2 * _skills[idx].proceedRatio);		//	�׽�Ʈ��
	}
	
	_skills[idx].angle = getRefreshAngle(_skills[idx].angle);

	_skills[idx].polygonPos[1].x = _skills[idx].polygonPos[0].x + cosf(_skills[idx].preAngle) * MASK_MAX_WID;
	_skills[idx].polygonPos[1].y = _skills[idx].polygonPos[0].y + sinf(_skills[idx].preAngle) * MASK_MAX_WID;

	_skills[idx].polygonPos[2].x = _skills[idx].polygonPos[0].x + cosf(_skills[idx].angle) * MASK_MAX_WID;
	_skills[idx].polygonPos[2].y = _skills[idx].polygonPos[0].y + sinf(_skills[idx].angle) * MASK_MAX_WID;

	//_skills[idx].maskImg->PaintMagentaInPolygon(_skills[idx].polygonPos);		//	�Ⱦ��ϴ�.

	
	HBRUSH brush = CreateSolidBrush(0xFF00FF);
	HBRUSH oBrush = (HBRUSH)SelectObject(_skills[idx].maskImg->getMemDC(), brush);

	HPEN pen = CreatePen(1, 3, 0xFF00FF);
	HPEN oPen = (HPEN)SelectObject(_skills[idx].maskImg->getMemDC(), pen);

	Polygon(_skills[idx].maskImg->getMemDC(), _skills[idx].polygonPos, 3);

	SelectObject(_skills[idx].maskImg->getMemDC(), oBrush);
	DeleteObject(brush);
	SelectObject(_skills[idx].maskImg->getMemDC(), oPen);
	DeleteObject(pen);
	
}

/*
void skillCooldownUI::PartialClockwiseFunc(int idx)
{
	//BitBltMask(idx);

	POINT tmpPt[3];
	float deltaAngle = (PI*2)*_skills[idx].proceedRatio;
	float tmpAngle = PI/2*3;
	float tmpPreAngle = PI / 2 * 3;
	for (int i = 0; i < 3; i++) {
		tmpPt[i] = _skills[idx].polygonPos[i];
	}
	
	while (1) {
		if (_skills[idx].preAngle <= tmpAngle && tmpAngle <= _skills[idx].angle)	break;

		HBRUSH brush = CreateSolidBrush(0xFF00FF);
		HBRUSH oBrush = (HBRUSH)SelectObject(_skills[idx].maskImg->getMemDC(), brush);

		HPEN pen = CreatePen(1, 3, 0xFF00FF);
		HPEN oPen = (HPEN)SelectObject(_skills[idx].maskImg->getMemDC(), pen);

		
		tmpPreAngle = tmpAngle;
		tmpAngle += deltaAngle;
		tmpAngle = getRefreshAngle(tmpAngle);

		tmpPt[1].x = tmpPt[0].x + cosf(tmpPreAngle) * MASK_MAX_WID;
		tmpPt[1].y = tmpPt[0].y + sinf(tmpPreAngle) * MASK_MAX_WID;
					 
		tmpPt[2].x = tmpPt[0].x + cosf(tmpAngle) * MASK_MAX_WID;
		tmpPt[2].y = tmpPt[0].y + sinf(tmpAngle) * MASK_MAX_WID;

		Polygon(_skills[idx].maskImg->getMemDC(), tmpPt, 3);

		SelectObject(_skills[idx].maskImg->getMemDC(), oBrush);
		DeleteObject(brush);
		SelectObject(_skills[idx].maskImg->getMemDC(), oPen);
		DeleteObject(pen);

	}


	
	HBRUSH brush = CreateSolidBrush(0xFF00FF);
	HBRUSH oBrush = (HBRUSH)SelectObject(_skills[idx].maskImg->getMemDC(), brush);

	HPEN pen = CreatePen(1, 3, 0xFF00FF);
	HPEN oPen = (HPEN)SelectObject(_skills[idx].maskImg->getMemDC(), pen);


	
	//	 ���� ������ ����, �̸� ĥ�ص� - ����ó��(�Ѿ�1�����Ҵµ�, �װ� �i����)

	
	float fixedAngle = _skills[idx].angle;
	fixedAngle = getRefreshAngle(fixedAngle);
	//	1��и�
	if (PI/2*3 <= fixedAngle && fixedAngle < PI*2) {
		POINT polyPt[4];
		polyPt[0] = { 30,0 };
		polyPt[1] = { 60,0 };
		polyPt[2] = { 60,30 };
		//polyPt[3] = { 30,30 };
		
		Polygon(_skills[idx].maskImg->getMemDC(), polyPt, 3);
		
		//BitBltQuarterMask(idx, 1);

		tmpPt[1].x = _skills[idx].polygonPos[0].x + BORDER_SIZE * 2;
		tmpPt[1].y = _skills[idx].polygonPos[0].y;
	}
	else if (0 <= fixedAngle && fixedAngle < PI/2) {
		POINT polyPt[4];
		polyPt[0] = { 30,0 };
		polyPt[1] = { 60,0 };
		polyPt[2] = { 60,60 };
		polyPt[3] = { 30,60 };
		
		Polygon(_skills[idx].maskImg->getMemDC(), polyPt, 4);

		//BitBltQuarterMask(idx, 2);

		tmpPt[1].x = _skills[idx].polygonPos[0].x;
		tmpPt[1].y = _skills[idx].polygonPos[0].y + BORDER_SIZE * 2;
	}
	else if (PI / 2 <= fixedAngle && fixedAngle < PI /2*3) {
		POINT polyPt[4];
		polyPt[0] = { 30,0 };
		polyPt[1] = { 60,0 };
		polyPt[2] = { 60,60 };
		polyPt[3] = { 30,60 };
		Polygon(_skills[idx].maskImg->getMemDC(), polyPt, 4);
		
		polyPt[0] = { 0,30 };
		polyPt[1] = { 30,30 };
		polyPt[2] = { 30,60 };
		polyPt[3] = { 0,60 };
		Polygon(_skills[idx].maskImg->getMemDC(), polyPt, 4);

		//BitBltQuarterMask(idx, 3);

		tmpPt[1].x = _skills[idx].polygonPos[0].x - BORDER_SIZE * 2;
		tmpPt[1].y = _skills[idx].polygonPos[0].y;
	}
	

	//	�ӽ÷� �������� pt�� ��������
	Polygon(_skills[idx].maskImg->getMemDC(), tmpPt, 3);

	SelectObject(_skills[idx].maskImg->getMemDC(), oBrush);
	DeleteObject(brush);
	SelectObject(_skills[idx].maskImg->getMemDC(), oPen);
	DeleteObject(pen);

	

}
*/

void skillCooldownUI::UseIdxSkill(int idx)
{
	if (!_skills[idx].isStart) {
		BitBltMask(idx);
	}
	_skills[idx].isStart = true;
}
