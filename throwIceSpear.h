#pragma once
#include "gameNode.h"
#include "skills.h"
#include "rotateImgMaker.h"
class throwIceSpear :public skills
{
private:
	image* _iceSpearDefault;
	image* _iceSpearImg[36];
	
	struct tagIceSpear {
		image* img;
		POINTFLOAT pos;
		RECT rc;
		POINTFLOAT vec;
		POINTFLOAT atkDestPos;
		float angle;

	};


	vector<tagIceSpear*> _iceSpear;
	
	


public:
	throwIceSpear();
	~throwIceSpear();
};

