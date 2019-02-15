#include "stdafx.h"
#include "utils.h"


namespace BRAVO_UTIL
{
	//	각(rad)을 0~360도 사이로 만들어줌, 주소 집어넣으면 알아서 바뀜
	void RefreshAngle(float* angle)
	{
		while (1)
		{
			if (0 <= *angle && *angle < PI2)	break;

			if (*angle < 0)		*angle += PI2;
			if (*angle >= PI2)	*angle -= PI2;
			
		}
	}

	//	각(rad)을 0~360도 사이로 만들어줌, 리턴받아라~
	float getRefreshAngle(float angle)
	{
		while (1)
		{
			if (0 <= angle && angle < PI2)	break;

			if (angle < 0)		angle += PI2;
			if (angle >= PI2)	angle -= PI2;

		}

		return angle;
	}

	//거리 구하는 함수
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return x * x + y * y;
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{

		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		//아탄투
		float angle = -atan2f(y, x);

		//float angle = acosf(x / distance);

		////예외처리 필쑤
		//if (y2 > y1)
		//{
		//	angle = 2 * PI - angle;
		//	if (angle >= PI * 2) angle -= PI * 2;
		//}

		if (angle < 0)		angle += PI2;
		if (angle >= PI2)	angle -= PI2;

		return angle;
	}

}