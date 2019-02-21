#include "stdafx.h"
#include "snowflakeRotate.h"


snowflakeRotate::snowflakeRotate()
{
}


snowflakeRotate::~snowflakeRotate()
{
}

HRESULT snowflakeRotate::init()
{
	IMAGEMANAGER->addFrameImage("iceFlake", "images/boss/IceBossSkill/iceFlake.bmp", 300, 50, 6, 1, true, 0xFF00FF);
	_vSnowFlakes.clear();
	_flakeNum = 0;
	_rotateRad = 0;
	_frameAugCounter = 0;

	_isStart = false;
	_isRdyToShot = false;

	_shottingTimer = 0.f;
	_shotMissileIdx = 0;
	
	_totalSkillTimer = 0.f;

	return S_OK;
}

void snowflakeRotate::release()
{
	_flakeNum = 0;
	_rotateRad = 0.f;
	_augRotateRad = 0.f;
	_augAngle = 0.f;

	_frameAugCounter = 0;

	_isStart = false;
	_isRdyToShot = false;
	
	_shottingTimer = 0.f;
	_shotMissileIdx = 0;

	_totalSkillTimer = 0.f;

	for (int i = 0; i < _vSnowFlakes.size(); i++) {
		_vSnowFlakes[i]->img = nullptr;
		delete _vSnowFlakes[i];
		_vSnowFlakes[i] = nullptr;
	}
	_vSnowFlakes.clear();
}

void snowflakeRotate::update()
{
	if (_isStart) {
		_totalSkillTimer += TIMEMANAGER->getElapsedTime();
		if (_totalSkillTimer > END_TIME) {
			this->release();
			return;

		}
		FrameFunc();
		


		if (_augAngle < ROTATE_ANGLE_SPD_MAX) {
			_augAngle += ROTATE_AUG_ANGLESPD;
		}
		for (int i = 0; i < _vSnowFlakes.size(); i++) {
			RotateFlakes(i);

		}
		//	½òÁØºñ ¾ÈµÆÀ¸¸é,
		if (!_isRdyToShot) {
			if (_rotateRad < ROTATE_RAD_MAX)
				_rotateRad += _augRotateRad;
			else if (_rotateRad >= ROTATE_RAD_MAX) {
				_rotateRad = ROTATE_RAD_MAX;
				_isRdyToShot = true;
			}
		}
		//	½òÁØºñµÆÀ¸¸é,
		else {
			//Â±±ïÂ±±ð
			if (_shottingTimer < SHOOTING_SPD && _shotMissileIdx < _flakeNum) {
				_shottingTimer += TIMEMANAGER->getElapsedTime();
			}
			//	¤¨¸®¸®¸®¸®¸®¤¨¸±¶ì¸®¸®¸®
			else if (_shottingTimer >= SHOOTING_SPD) {
				_shottingTimer = 0.f;
				PrepareShotMissile(_shotMissileIdx);
				_shotMissileIdx++;
			}

			//	ÁØºñµÈ »ç¼ö·ÎºÎÅÍ »ç°Ý °³½Ã
			for (int i = 0; i < _shotMissileIdx; i++) {
				MissileMove(i);
			}

		}

	}
}

void snowflakeRotate::render()
{
	if (_isStart) {
		for (int i = 0; i < _vSnowFlakes.size(); i++) {
			_vSnowFlakes[i]->img->frameRender(getMemDC(),
				_vSnowFlakes[i]->rc.left - CAMERA2D->getCamPosX(),
				_vSnowFlakes[i]->rc.top - CAMERA2D->getCamPosY(),
				_vSnowFlakes[i]->frameX,
				0);


			//Rectangle(getMemDC(), _vSnowFlakes[i]->judgeRc);
		}

	}

	//if (_vSnowFlakes.size() != 0) {
	//	char str[128];
	//	sprintf_s(str, "[0].getFrameX = [%d]", _vSnowFlakes[0]->img->getFrameX());
	//	TextOut(getMemDC(), 100, 100, str, strlen(str));
	//}
	

}

void snowflakeRotate::UseSkill(POINTFLOAT * bossPos, POINTFLOAT * playerPos, int missileNum)
{
	_vSnowFlakes.clear();
	_vSnowFlakes.reserve(missileNum);

	_flakeNum = missileNum;
	_bossPos = bossPos;
	_playerPos = playerPos;
	_rotateRad = 0.f;
	_augRotateRad = ROTATE_AUG_RAD;	
	_augAngle = 0.f;

	_frameAugCounter = 0;
	


	_isStart = true;
	_isRdyToShot = false;

	_shottingTimer = 0.f;
	_shotMissileIdx = 0;

	
	//	º¤ÅÍ ¼¼ÆÃ!
	image* flakeImg = IMAGEMANAGER->findImage("iceFlake");
	float angle = 0.f;
	float augAngle = PI2 / missileNum;

	for (int i = 0; i < missileNum; i++) {
		tagSnowFlake* tmpFlake = new tagSnowFlake;
		tmpFlake->img = flakeImg;
		tmpFlake->img->SetFrameX(0);
		tmpFlake->img->SetFrameY(0);
		tmpFlake->pos.x = _bossPos->x;
		tmpFlake->pos.y = _bossPos->y;
		tmpFlake->rc = RectMakeCenter(tmpFlake->pos.x, tmpFlake->pos.y, FLAKERC_WID, FLAKERC_WID);
		tmpFlake->judgeRc = RectMakeCenter(tmpFlake->pos.x, tmpFlake->pos.y, JUDGERC_WID, JUDGERC_WID);
		tmpFlake->vec = { 0,0 };
		tmpFlake->rotateAngle = angle;
		tmpFlake->augRotateAngleSpd = 0.f;
		tmpFlake->isShot = false;
		tmpFlake->frameX = 0;

		_vSnowFlakes.push_back(tmpFlake);

		angle -= augAngle;
	}



}

void snowflakeRotate::FrameFunc()
{
	_frameAugCounter++;
	if (_frameAugCounter > FRAMECOUNT_MAX) {
		for (int i = 0; i < _vSnowFlakes.size(); i++) {
			_vSnowFlakes[i]->frameX++;
			if (_vSnowFlakes[i]->frameX >= _vSnowFlakes[i]->img->getMaxFrameX()) {
				_vSnowFlakes[i]->frameX = 0;
			}
		}
	}
}

void snowflakeRotate::RotateFlakes(int idx)
{
	if (_vSnowFlakes[idx]->isShot == false) {
		_vSnowFlakes[idx]->pos.x = _bossPos->x + cosf(_vSnowFlakes[idx]->rotateAngle) * _rotateRad;
		_vSnowFlakes[idx]->pos.y = _bossPos->y + sinf(_vSnowFlakes[idx]->rotateAngle) * _rotateRad;
		_vSnowFlakes[idx]->rc = RectMakeCenter(_vSnowFlakes[idx]->pos.x, _vSnowFlakes[idx]->pos.y, FLAKERC_WID, FLAKERC_WID);
		_vSnowFlakes[idx]->judgeRc = RectMakeCenter(_vSnowFlakes[idx]->pos.x, _vSnowFlakes[idx]->pos.y, JUDGERC_WID, JUDGERC_WID);
		_vSnowFlakes[idx]->rotateAngle += _augAngle;
		if (_vSnowFlakes[idx]->rotateAngle > PI2) 
			_vSnowFlakes[idx]->rotateAngle -= PI2;
		
			
		
	}
	
}

void snowflakeRotate::PrepareShotMissile(int idx)
{
	float shotAngle = atan2f(_playerPos->y - _vSnowFlakes[idx]->pos.y, _playerPos->x - _vSnowFlakes[idx]->pos.x);

	_vSnowFlakes[idx]->isShot = true;
	_vSnowFlakes[idx]->vec.x = MISSILE_SPD * cosf(shotAngle);
	_vSnowFlakes[idx]->vec.y = MISSILE_SPD * sinf(shotAngle);
	
}

void snowflakeRotate::MissileMove(int idx)
{
	
	_vSnowFlakes[idx]->pos.x += _vSnowFlakes[idx]->vec.x;
	_vSnowFlakes[idx]->pos.y += _vSnowFlakes[idx]->vec.y;
	_vSnowFlakes[idx]->rc = RectMakeCenter(_vSnowFlakes[idx]->pos.x, _vSnowFlakes[idx]->pos.y, FLAKERC_WID, FLAKERC_WID);
	_vSnowFlakes[idx]->judgeRc = RectMakeCenter(_vSnowFlakes[idx]->pos.x, _vSnowFlakes[idx]->pos.y, JUDGERC_WID, JUDGERC_WID);
}
