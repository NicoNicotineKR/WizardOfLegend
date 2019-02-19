#include "stdafx.h"
#include "throwIceSpear.h"


throwIceSpear::throwIceSpear()
{
}


throwIceSpear::~throwIceSpear()
{
}

HRESULT throwIceSpear::init()
{
	//	원본이미지 넣었다 치고,
	//IMAGEMANAGER->addImage("iceSpearDefault");
	
	_iceSpearDefault = IMAGEMANAGER->findImage("iceSpearDefault");
	_imgMaker = new rotateImgMaker;

	//	회전이미지 생성
	float angle = 0;
	float augAngle = PI * 2 / 36;

	for (int i = 0; i < 36; i++) {
		_iceSpearImg[i] = _imgMaker->MakeRotateImg(_iceSpearDefault, 0, 0,
			_iceSpearDefault->GetWidth(), _iceSpearDefault->GetHeight(),
			angle, true, 0xFF00FF);
		angle += augAngle;

	}
	delete _imgMaker;
	_imgMaker = nullptr;

	_prepareShotElapsedTime = 0.f;
	_totalSkillElapsedTime = 0.f;
	
	for (int i = 0; i < SPEAR_NUM; i++) {
		tagIceSpear* tmpIceSpear = new tagIceSpear;
		tmpIceSpear->alpha = 0;

		//	첫 번째면,
		if (i == 0)
		{
			tmpIceSpear->adjustPos = { 0,0 };
		}
		//	짝수번째면,
		else if (i % 2 == 0)
		{
			tmpIceSpear->adjustPos = { 48* (i / 2) ,0 };
		}
		//	홀수번째면
		else
		{
			tmpIceSpear->adjustPos = { -48 * (i / 2), 0 };
		}
		
		_iceSpear.push_back(tmpIceSpear);
	}
	
	_isOnceSetSpearPrepareValue = false;
	_isOnceSetSpearShotValue = false;
	_isStart = false;
	//_spearTipLength = _iceSpearDefault->GetHeight() / 2;

	return S_OK;
}

void throwIceSpear::release()
{
}

void throwIceSpear::update()
{
	if (_isStart) {
		//	모든 창들에 대하여,
		for (int i = 0; i < _iceSpear.size(); i++) {

			//	쏠 준비중이면
			if (_prepareShotElapsedTime < PREPARE_SHOTTIME) {
				_prepareShotElapsedTime += TIMEMANAGER->getElapsedTime();

				//	한번도 창준비값을 설정한적이 없다면,
				if (!_isOnceSetSpearPrepareValue) {

					_isOnceSetSpearPrepareValue = true;
					//	spear 초기위치 세팅
					SetSpearPrepareValueOnce(i, *_bossPos);
				}
				//	항상 업데이트 해줘야 하는 값들 세팅(angle, angle적용이미지)
				SetSpearPrepareValue(i, *_playerPos);


			}	//	쏠 준비중 끝

			//	쏠 시간 됐으면!
			else {
				//	한번만 계산하는애들 계산하즈아
				if (!_isOnceSetSpearShotValue) {
					_isOnceSetSpearShotValue = false;
					//	판정렉트 좌표			//	vector 계산
					SetSpearShotValueOnce(i);
				}

				//	가랏! 게오볼그!!! //	판정렉트도 이동해서 다시그리기
				SetSpearShotValue(i);

			}

		}
		_totalSkillElapsedTime += TIMEMANAGER->getElapsedTime();

		if (_totalSkillElapsedTime > END_SKILLTIME) {
			ResetAll();
		}
	}
}

void throwIceSpear::render()
{
}

void throwIceSpear::UseSkill(POINTFLOAT * bossPos, POINTFLOAT * playerPos, int spearNum)
{
	_bossPos = bossPos;
	_playerPos = playerPos;
	_spearNum = spearNum;
	
	_isStart = true;
	
}

void throwIceSpear::SetSpearPrepareValueOnce(int idx, POINTFLOAT bossPos)
{
	_iceSpear[idx]->pos = bossPos;		//	중심좌표일경우
	_iceSpear[idx]->pos.y -= 110;			//	중심에서 위로 110만큼 (보스 hei == 200)
	_iceSpear[idx]->pos.x += _iceSpear[idx]->adjustPos.x;
	_iceSpear[idx]->pos.y += _iceSpear[idx]->adjustPos.y;
	_iceSpear[idx]->rc = RectMakeCenter(_iceSpear[idx]->pos.x, _iceSpear[idx]->pos.y, _iceSpearDefault->GetWidth() / 2, _iceSpearDefault->GetHeight() / 2);
}

void throwIceSpear::SetSpearPrepareValue(int idx, POINTFLOAT playerPos)
{
	_iceSpear[idx]->angle = getAngle(_iceSpear[idx]->pos.x, _iceSpear[idx]->pos.y, playerPos.x, playerPos.y);

	//	각에 따른 이미지 세팅
	int spearImgIdx = (_iceSpear[idx]->angle + PI / 36) / (PI / 18);
	//		예외처리
	if (spearImgIdx == 36) {
		_iceSpear[idx]->img = _iceSpearImg[0];
	}
	else {
		_iceSpear[idx]->img = _iceSpearImg[spearImgIdx];
	}

	//알프아아아아아
	if (_iceSpear[idx]->alpha > 255) {
		_iceSpear[idx]->alpha = 255;
	}
	else {
		_iceSpear[idx]->alpha += AUG_ALPHA;
	}
}

void throwIceSpear::SetSpearShotValueOnce(int idx)
{
	//	판정렉트 좌표
	_iceSpear[idx]->judgePos[0].x = _iceSpear[idx]->pos.x + (SPEAR_TIP_LENGTH * 3 / 4) * cosf(_iceSpear[idx]->angle);
	_iceSpear[idx]->judgePos[0].y = _iceSpear[idx]->pos.y + (SPEAR_TIP_LENGTH * 3 / 4) * -sinf(_iceSpear[idx]->angle);
											   
	_iceSpear[idx]->judgePos[1].x = _iceSpear[idx]->pos.x + (SPEAR_TIP_LENGTH * 1 / 4) * cosf(_iceSpear[idx]->angle);
	_iceSpear[idx]->judgePos[1].y = _iceSpear[idx]->pos.y + (SPEAR_TIP_LENGTH * 1 / 4) * -sinf(_iceSpear[idx]->angle);


	//	vector 계산
	_iceSpear[idx]->vec.x = SPEAR_SPD * cosf(_iceSpear[idx]->angle);
	_iceSpear[idx]->vec.y = SPEAR_SPD * -sinf(_iceSpear[idx]->angle);
}

void throwIceSpear::SetSpearShotValue(int idx)
{
	//	가랏! 게오볼그!!!
	_iceSpear[idx]->pos.x += _iceSpear[idx]->vec.x;
	_iceSpear[idx]->pos.y += _iceSpear[idx]->vec.y;
	_iceSpear[idx]->rc = RectMakeCenter(_iceSpear[idx]->pos.x, _iceSpear[idx]->pos.y, _iceSpearDefault->GetWidth() / 2, _iceSpearDefault->GetHeight() / 2);

	//	판정렉트도 이동해서 다시그리기
	_iceSpear[idx]->judgePos[0].x += _iceSpear[idx]->vec.x;
	_iceSpear[idx]->judgePos[0].x += _iceSpear[idx]->vec.y;
	_iceSpear[idx]->judgePos[1].x += _iceSpear[idx]->vec.x;
	_iceSpear[idx]->judgePos[1].x += _iceSpear[idx]->vec.y;
	_iceSpear[idx]->judgeRc[0] = RectMakeCenter(_iceSpear[idx]->judgePos[0].x, _iceSpear[idx]->judgePos[0].y, JUDGERC_WID, JUDGERC_WID);
	_iceSpear[idx]->judgeRc[1] = RectMakeCenter(_iceSpear[idx]->judgePos[1].x, _iceSpear[idx]->judgePos[1].y, JUDGERC_WID, JUDGERC_WID);
}

void throwIceSpear::ResetAll()
{
	_isOnceSetSpearPrepareValue = false;
	_isOnceSetSpearShotValue = false;
	_isShotPrepareEnd = false;
	_prepareShotElapsedTime = 0;
	_totalSkillElapsedTime = 0;

	for (int i = 0; i < _iceSpear.size(); i++) {
		delete _iceSpear[i];
		_iceSpear[i] = nullptr;
	}
	_iceSpear.clear();


}
		

	



	