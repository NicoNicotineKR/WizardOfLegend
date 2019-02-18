#pragma once
#include "gameNode.h"

enum class B_ANIDIRECTION
{
	LEFT,
	RIGHT
};

enum class B_STATE
{
	IDLE,			// 아이들...인데 있나?
	SPAWN,			// 최초 다이얼로그 나오기전 스폰하는거
	CASTING,		// 조롱 or 스턴후 보스턴되기전에 손휘두름
	MOCK,			// 스킬 다쓰고 조롱하는거 이떄 맞으면 스턴됨 (hit 없음)
	STUN,			// 조롱하다가 1대라도 맞으면 스턴상태들어감
	SKILL_ONE,		// 물방울 회전!!!! 회오리!!!!!
	SKILL_TWO,		// 눈송이 회전!!!! 회오리!!!!
	SKILL_THREE,	// 창 3개 날리기
	SKILL_FOUR,		// 돌진 얼음칼 돌리기
	SKILL_FIVE,		// 고드름비
	DEATH_START,	// 죽음 시작 -> 무릎꿇고 다이얼로그 뱉음
	DEATH			// 얼음되서 사라짐 (죽음 시작에서 나온 다이얼로그 에서 키눌러서 다이얼로그 종료되면 얼음되고 깨짐)
};

class boss : public gameNode
{
private:      

public:
	boss();
	~boss();
};

