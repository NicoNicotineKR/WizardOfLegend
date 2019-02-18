#pragma once
#include "gameNode.h"

enum class B_ANIDIRECTION
{
	LEFT,
	RIGHT
};

enum class B_STATE
{
	IDLE,			// ���̵�...�ε� �ֳ�?
	SPAWN,			// ���� ���̾�α� �������� �����ϴ°�
	CASTING,		// ���� or ������ �����ϵǱ����� ���ֵθ�
	MOCK,			// ��ų �پ��� �����ϴ°� �̋� ������ ���ϵ� (hit ����)
	STUN,			// �����ϴٰ� 1��� ������ ���ϻ��µ�
	SKILL_ONE,		// ����� ȸ��!!!! ȸ����!!!!!
	SKILL_TWO,		// ������ ȸ��!!!! ȸ����!!!!
	SKILL_THREE,	// â 3�� ������
	SKILL_FOUR,		// ���� ����Į ������
	SKILL_FIVE,		// ��帧��
	DEATH_START,	// ���� ���� -> �����ݰ� ���̾�α� ����
	DEATH			// �����Ǽ� ����� (���� ���ۿ��� ���� ���̾�α� ���� Ű������ ���̾�α� ����Ǹ� �����ǰ� ����)
};

class boss : public gameNode
{
private:      

public:
	boss();
	~boss();
};

