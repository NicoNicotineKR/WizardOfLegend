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
	//	�����̹��� �־��� ġ��,
	//IMAGEMANAGER->addImage("iceSpearDefault");
	
	_iceSpearDefault = IMAGEMANAGER->findImage("iceSpearDefault");
	_imgMaker = new rotateImgMaker;

	//	ȸ���̹��� ����
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

		//	ù ��°��,
		if (i == 0)
		{
			tmpIceSpear->adjustPos = { 0,0 };
		}
		//	¦����°��,
		else if (i % 2 == 0)
		{
			tmpIceSpear->adjustPos = { 48* (i / 2) ,0 };
		}
		//	Ȧ����°��
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
		//	��� â�鿡 ���Ͽ�,
		for (int i = 0; i < _iceSpear.size(); i++) {

			//	�� �غ����̸�
			if (_prepareShotElapsedTime < PREPARE_SHOTTIME) {
				_prepareShotElapsedTime += TIMEMANAGER->getElapsedTime();

				//	�ѹ��� â�غ��� ���������� ���ٸ�,
				if (!_isOnceSetSpearPrepareValue) {

					_isOnceSetSpearPrepareValue = true;
					//	spear �ʱ���ġ ����
					SetSpearPrepareValueOnce(i, *_bossPos);
				}
				//	�׻� ������Ʈ ����� �ϴ� ���� ����(angle, angle�����̹���)
				SetSpearPrepareValue(i, *_playerPos);


			}	//	�� �غ��� ��

			//	�� �ð� ������!
			else {
				//	�ѹ��� ����ϴ¾ֵ� ��������
				if (!_isOnceSetSpearShotValue) {
					_isOnceSetSpearShotValue = false;
					//	������Ʈ ��ǥ			//	vector ���
					SetSpearShotValueOnce(i);
				}

				//	����! �Կ�����!!! //	������Ʈ�� �̵��ؼ� �ٽñ׸���
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
	_iceSpear[idx]->pos = bossPos;		//	�߽���ǥ�ϰ��
	_iceSpear[idx]->pos.y -= 110;			//	�߽ɿ��� ���� 110��ŭ (���� hei == 200)
	_iceSpear[idx]->pos.x += _iceSpear[idx]->adjustPos.x;
	_iceSpear[idx]->pos.y += _iceSpear[idx]->adjustPos.y;
	_iceSpear[idx]->rc = RectMakeCenter(_iceSpear[idx]->pos.x, _iceSpear[idx]->pos.y, _iceSpearDefault->GetWidth() / 2, _iceSpearDefault->GetHeight() / 2);
}

void throwIceSpear::SetSpearPrepareValue(int idx, POINTFLOAT playerPos)
{
	_iceSpear[idx]->angle = getAngle(_iceSpear[idx]->pos.x, _iceSpear[idx]->pos.y, playerPos.x, playerPos.y);

	//	���� ���� �̹��� ����
	int spearImgIdx = (_iceSpear[idx]->angle + PI / 36) / (PI / 18);
	//		����ó��
	if (spearImgIdx == 36) {
		_iceSpear[idx]->img = _iceSpearImg[0];
	}
	else {
		_iceSpear[idx]->img = _iceSpearImg[spearImgIdx];
	}

	//�����ƾƾƾƾ�
	if (_iceSpear[idx]->alpha > 255) {
		_iceSpear[idx]->alpha = 255;
	}
	else {
		_iceSpear[idx]->alpha += AUG_ALPHA;
	}
}

void throwIceSpear::SetSpearShotValueOnce(int idx)
{
	//	������Ʈ ��ǥ
	_iceSpear[idx]->judgePos[0].x = _iceSpear[idx]->pos.x + (SPEAR_TIP_LENGTH * 3 / 4) * cosf(_iceSpear[idx]->angle);
	_iceSpear[idx]->judgePos[0].y = _iceSpear[idx]->pos.y + (SPEAR_TIP_LENGTH * 3 / 4) * -sinf(_iceSpear[idx]->angle);
											   
	_iceSpear[idx]->judgePos[1].x = _iceSpear[idx]->pos.x + (SPEAR_TIP_LENGTH * 1 / 4) * cosf(_iceSpear[idx]->angle);
	_iceSpear[idx]->judgePos[1].y = _iceSpear[idx]->pos.y + (SPEAR_TIP_LENGTH * 1 / 4) * -sinf(_iceSpear[idx]->angle);


	//	vector ���
	_iceSpear[idx]->vec.x = SPEAR_SPD * cosf(_iceSpear[idx]->angle);
	_iceSpear[idx]->vec.y = SPEAR_SPD * -sinf(_iceSpear[idx]->angle);
}

void throwIceSpear::SetSpearShotValue(int idx)
{
	//	����! �Կ�����!!!
	_iceSpear[idx]->pos.x += _iceSpear[idx]->vec.x;
	_iceSpear[idx]->pos.y += _iceSpear[idx]->vec.y;
	_iceSpear[idx]->rc = RectMakeCenter(_iceSpear[idx]->pos.x, _iceSpear[idx]->pos.y, _iceSpearDefault->GetWidth() / 2, _iceSpearDefault->GetHeight() / 2);

	//	������Ʈ�� �̵��ؼ� �ٽñ׸���
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
		

	



	