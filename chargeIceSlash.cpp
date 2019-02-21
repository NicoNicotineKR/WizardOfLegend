#include "stdafx.h"
#include "chargeIceSlash.h"


chargeIceSlash::chargeIceSlash()
{
}


chargeIceSlash::~chargeIceSlash()
{
}

HRESULT chargeIceSlash::init()
{
	_slashNum = 0;
	_destPos = { 0, 0 };
	_vec = { 0,0 };
	_angle = 0;

	_skillTimer = 0;

	_isStart = false;

	_bossPos = nullptr;
	_playerPos = nullptr;

	return S_OK;
}

void chargeIceSlash::release()
{
	_isStart = false;
	_bossPos = nullptr;
	_playerPos = nullptr;
	_slashNum = 0;

	_skillTimer = 0.f;
	_destPos.x = 0;
	_destPos.y = 0;

	_angle = 0.f;
	_vec.x = 0.f;
	_vec.y = 0.f;
}

void chargeIceSlash::update()
{

	if (_isStart) {
		if (_skillTimer > END_TIME) {
			_isStart = false;
			this->release();
			return;
		}

		_skillTimer += TIMEMANAGER->getElapsedTime();
		

		_bossPos->x += _vec.x;
		_bossPos->y += _vec.y;

	}

}

void chargeIceSlash::render()
{
}

void chargeIceSlash::UseSkill(POINTFLOAT * bossPos, POINTFLOAT * playerPos, int slashNum)
{
	_isStart = true;
	_bossPos = bossPos;
	_playerPos = playerPos;
	_slashNum = slashNum;
	
	_skillTimer = 0.f;
	_destPos.x = playerPos->x;
	_destPos.y = playerPos->y;


	_totalFrameNum = END_TIME * 60;

	_angle = atan2f(_destPos.y - _bossPos->y, _destPos.x - _bossPos->x);
	
	_vec.x = (_destPos.x - _bossPos->x) / _totalFrameNum;
	_vec.y = (_destPos.y - _bossPos->y) / _totalFrameNum;

	//_vec.x = MOVESPD * cosf(_angle);
	//_vec.y = MOVESPD * sinf(_angle);

}
