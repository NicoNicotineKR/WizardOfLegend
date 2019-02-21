#include "stdafx.h"
#include "waterdropRotate.h"


waterdropRotate::waterdropRotate()
{
}


waterdropRotate::~waterdropRotate()
{
}

HRESULT waterdropRotate::init()
{
	IMAGEMANAGER->addFrameImage("waterDrop", "images/boss/IceBossSkill/waterDrop.bmp", 420, 60, 7, 1, true, 0xFF00FF);
	_waterDropNum = 0;
	_preparedWaterdropNum = 0;
	_shotMissileIdx = 0;

	_prepareMissileTimer = 0.f;
	_shootingMissileTimer = 0.f;
	_missleGenTime = 0.f;
	_totalSkillElapsedTime = 0.f;
	_rotateAngle = 0.f;

	_frameCounter = 0;

	_isStart = false;
	_isRdyToShot = false;
	
	return S_OK;
}

void waterdropRotate::release()
{
	for (int i = 0; i < _vWaterDrops.size(); i++) {
		delete _vWaterDrops[i];
		_vWaterDrops[i] = nullptr;
	}
	_vWaterDrops.clear();

	_waterDropNum = 0;
	_preparedWaterdropNum = 0;
	_shotMissileIdx = 0;

	_prepareMissileTimer = 0.f;		//	�ϳ� �����Ҷ����� �ð����ִ� Ÿ�̸�
	_shootingMissileTimer = 0.f;
	_missleGenTime = 0.f;			//	�ϳ� �����ϱ���� �ɸ��� �ð�
	_totalSkillElapsedTime = 0.f;


	_frameCounter = 0;
	_rotateAngle = 0.f;

	_isStart = false;
	_isRdyToShot = false;
}

void waterdropRotate::update()
{
	if (_isStart) {
		_totalSkillElapsedTime += TIMEMANAGER->getElapsedTime();
		if (_totalSkillElapsedTime > END_SKILTIME) {
			this->release();
			return;
		}
		_frameCounter++;
		FrameIncreaseFunc();
		RotatemissleFunc();

		//	���غ�ȵ����� �غ��ؾ���
		if (!_isRdyToShot) {
			_prepareMissileTimer += TIMEMANAGER->getElapsedTime();
			AlphaIncreaseFunc();
			//	������ �ð��� �Ǿ��
			if (_prepareMissileTimer > _missleGenTime) {
				//	������ġ
				if (_preparedWaterdropNum < _waterDropNum) {
					_prepareMissileTimer = 0.f;
					_preparedWaterdropNum++;
				}
				
			}
			//�������� ���İ� �� �غ�ƴٸ�, �غ�Ϸ᤻
			if (_vWaterDrops[_waterDropNum - 1]->alpha == 255
				|| _totalSkillElapsedTime > PREPARE_TIME) {
				_isRdyToShot = true;
			}
		}

		//	�� �غ�Ϸ�~
		else {
			if (_shootingMissileTimer < SHOOTINGSPD && _shotMissileIdx < _waterDropNum) {
				//	°��°��
				_shootingMissileTimer += TIMEMANAGER->getElapsedTime();
			}

			//	��ð��Ƴ�? -> ����� �ʱ���� ���ְ�!
			else if (_shootingMissileTimer >= SHOOTINGSPD) {
				_shootingMissileTimer = 0.f;
				PrepareShotMissile(_shotMissileIdx);
				_shotMissileIdx++;
			}
			//	�غ�� ����κ��� ��� ����
			for (int i = 0; i < _shotMissileIdx; i++) {
				MissileMove(i);
			}
			////	���غ� �ȵȾֵ��� ���ƶ� + ������ �����ض�
			//for (int i = _shotMissileIdx; i < _waterDropNum; i++) {
			//	RotatemissleFunc(i);
			//	//_frameCounter++;
			//	//
			//}




		}



		
	}
}

void waterdropRotate::render()
{
	if (_isStart) {
		for (int i = 0; i < _waterDropNum; i++) {
			_vWaterDrops[i]->img->alphaFrameRenderFixed(getMemDC(),
				_vWaterDrops[i]->rc.left - CAMERA2D->getCamPosX(), _vWaterDrops[i]->rc.top - CAMERA2D->getCamPosY(),
				_vWaterDrops[i]->img->getFrameX(), _vWaterDrops[i]->img->getFrameY(),
				_vWaterDrops[i]->alpha);

			//Rectangle(getMemDC(), _vWaterDrops[i]->judgeRc);
			


		}

		
		//	�׽�Ʈ��
		//for (int i = 0; i < _waterDropNum; i++) {
		//	Rectangle(getMemDC(), _vWaterDrops[i]->judgeRc);
		//}

		/*
		char str[128];
		sprintf_s(str, "[0]_shotMissleTimer : %f", _shootingMissileTimer);
		TextOut(getMemDC(), 50, 100, str, strlen(str));
		*/
	}
}

void waterdropRotate::UseSkill(POINTFLOAT * bossPos, POINTFLOAT * playerPos, int missileNum)
{
	_prepareMissileTimer = 0.f;
	_totalSkillElapsedTime = 0.f;

	_frameCounter = 0;
	_preparedWaterdropNum = 0;
	_shotMissileIdx = 0;

	_isStart = true;
	_isRdyToShot = false;


	_vWaterDrops.clear();

	_bossPos = bossPos;
	_playerPos = playerPos;
	_waterDropNum = missileNum;

	_missleGenTime = (PREPARE_TIME - 1.0f) / _waterDropNum;		//	1�ʴ� ������ �����ð����� ����

	_vWaterDrops.reserve(missileNum);

	image* waterdropImg = IMAGEMANAGER->findImage("waterDrop");
	float angle = 0.f;
	float augAngle = (PI * 2) / _waterDropNum;

	for (int i = 0; i < _waterDropNum; i++) {
		tagWaterDrop* tmpWaterDrop = new tagWaterDrop;
		tmpWaterDrop->img = waterdropImg;
		tmpWaterDrop->img->SetFrameX(0);
		tmpWaterDrop->img->SetFrameY(0);
		tmpWaterDrop->pos.x = _bossPos->x + cosf(angle)*ROTATE_RAD;
		tmpWaterDrop->pos.y = _bossPos->y + sinf(angle)*ROTATE_RAD;
		tmpWaterDrop->rc = RectMakeCenter(tmpWaterDrop->pos.x, tmpWaterDrop->pos.y, WATERDROP_WID, WATERDROP_WID);
		tmpWaterDrop->judgeRc = RectMakeCenter(tmpWaterDrop->pos.x, tmpWaterDrop->pos.y, JUDGE_RC_WID, JUDGE_RC_WID);
		tmpWaterDrop->vec = { 0, 0 };
		tmpWaterDrop->rotateAngle = angle;
		tmpWaterDrop->alpha = 0;
		tmpWaterDrop->isShot = false;

		_vWaterDrops.push_back(tmpWaterDrop);

		angle -= augAngle;

	}

}

void waterdropRotate::RotatemissleFunc()
{
	


	for (int i = 0; i < _waterDropNum; i++) {
		if (_vWaterDrops[i]->isShot)	continue;
		_vWaterDrops[i]->pos.x = _bossPos->x + cosf(_vWaterDrops[i]->rotateAngle)*ROTATE_RAD;
		_vWaterDrops[i]->pos.y = _bossPos->y + sinf(_vWaterDrops[i]->rotateAngle)*ROTATE_RAD;
		_vWaterDrops[i]->rc = RectMakeCenter(_vWaterDrops[i]->pos.x, _vWaterDrops[i]->pos.y, WATERDROP_WID, WATERDROP_WID);
		_vWaterDrops[i]->judgeRc = RectMakeCenter(_vWaterDrops[i]->pos.x, _vWaterDrops[i]->pos.y, JUDGE_RC_WID, JUDGE_RC_WID);
		_vWaterDrops[i]->rotateAngle += ROTATE_ANGLE_SPD;

		//	�ޱ۰� refresh;
		if (_vWaterDrops[i]->rotateAngle > PI * 2) _vWaterDrops[i]->rotateAngle -= PI * 2;

	}
}

void waterdropRotate::RotatemissleFunc(int idx)
{
	_vWaterDrops[idx]->pos.x = _bossPos->x + cosf(_vWaterDrops[idx]->rotateAngle)*ROTATE_RAD;
	_vWaterDrops[idx]->pos.y = _bossPos->y + sinf(_vWaterDrops[idx]->rotateAngle)*ROTATE_RAD;
	_vWaterDrops[idx]->rc = RectMakeCenter(_vWaterDrops[idx]->pos.x, _vWaterDrops[idx]->pos.y, WATERDROP_WID, WATERDROP_WID);
	_vWaterDrops[idx]->judgeRc = RectMakeCenter(_vWaterDrops[idx]->pos.x, _vWaterDrops[idx]->pos.y, JUDGE_RC_WID, JUDGE_RC_WID);
	_vWaterDrops[idx]->rotateAngle += ROTATE_ANGLE_SPD;

	//	�ޱ۰� refresh;
	if (_vWaterDrops[idx]->rotateAngle > PI * 2) _vWaterDrops[idx]->rotateAngle -= PI * 2;
}

void waterdropRotate::AlphaIncreaseFunc()
{
	for (int i = 0; i < _preparedWaterdropNum; i++) {
		_vWaterDrops[i]->alpha += AUG_ALPHA;
		if (_vWaterDrops[i]->alpha > 255)	_vWaterDrops[i]->alpha = 255;
	}
	
}

void waterdropRotate::FrameIncreaseFunc()
{
	if (_frameCounter > FRAME_COUNTMAX) {
		_frameCounter = 0;
		for (int i = 0; i < _waterDropNum; i++) {
			if (_vWaterDrops[i]->isShot)	continue;
			_vWaterDrops[i]->img->SetFrameX(_vWaterDrops[i]->img->getFrameX() + 1);
			if (_vWaterDrops[i]->img->getFrameX() >= _vWaterDrops[i]->img->getMaxFrameX()) {
				_vWaterDrops[i]->img->SetFrameX(0);
			}
				
		}
	}	
}

void waterdropRotate::FrameIncreaseFunc(int idx)
{
	if (_frameCounter > FRAME_COUNTMAX) {
		if(idx == _waterDropNum - 1)
			_frameCounter = 0;

		_vWaterDrops[idx]->img->SetFrameX(_vWaterDrops[idx]->img->getFrameX() + 1);
		if (_vWaterDrops[idx]->img->getFrameX() >= _vWaterDrops[idx]->img->getMaxFrameX()) {
			_vWaterDrops[idx]->img->SetFrameX(0);
		}

	}
}


void waterdropRotate::PrepareShotMissile(int idx)
{
	float shotAngle = atan2f(_playerPos->y - _vWaterDrops[idx]->pos.y, _playerPos->x - _vWaterDrops[idx]->pos.x);

	_vWaterDrops[idx]->isShot = true;
	_vWaterDrops[idx]->vec.x = WATERDROP_SPD * cosf(shotAngle);
	_vWaterDrops[idx]->vec.y = WATERDROP_SPD * sinf(shotAngle);
	_vWaterDrops[idx]->img->SetFrameX(0);


}

void waterdropRotate::MissileMove(int idx)
{
	_vWaterDrops[idx]->pos.x += _vWaterDrops[idx]->vec.x;
	_vWaterDrops[idx]->pos.y += _vWaterDrops[idx]->vec.y;
	_vWaterDrops[idx]->rc = RectMakeCenter(_vWaterDrops[idx]->pos.x, _vWaterDrops[idx]->pos.y, WATERDROP_WID, WATERDROP_WID);
	_vWaterDrops[idx]->judgeRc = RectMakeCenter(_vWaterDrops[idx]->pos.x, _vWaterDrops[idx]->pos.y, JUDGE_RC_WID, JUDGE_RC_WID);

}

void waterdropRotate::EndSkill()
{
	for (int i = 0; i < _vWaterDrops.size(); i++) {
		delete _vWaterDrops[i];
		_vWaterDrops[i] = nullptr;
	}
	_vWaterDrops.clear();

	_waterDropNum = 0;
	_preparedWaterdropNum = 0;
	_shotMissileIdx = 0;

	_prepareMissileTimer = 0.f;		//	�ϳ� �����Ҷ����� �ð����ִ� Ÿ�̸�
	_shootingMissileTimer = 0.f;
	_missleGenTime = 0.f;			//	�ϳ� �����ϱ���� �ɸ��� �ð�
	_totalSkillElapsedTime = 0.f;


	int _frameCounter = 0;
	float _rotateAngle = 0.f;

	_isStart = false;
	_isRdyToShot = false;
}
