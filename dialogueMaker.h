#pragma once
#include "gameNode.h"
class dialogueMaker : public gameNode
{
private:
	//ä���̹���
	image* _chatBoxImg;
	//�޾ƿ� Npc �̹���(�̹����Ŵ����� �߰����վ�ߵ�)
	image* _npcPicture;
	//������ ���
	string _text;

	//�����ҽ�
	bool _isStart;



	//TimeManger����� ���� ������
	float _time;
	//��¼ӵ�
	float _printSpeed;

	//�޾ƿ� ���ڱ���
	int _printLen;

	//�ƽ�Ű���� �񱳿�
	char tmpChar;


public:
	dialogueMaker();
	~dialogueMaker();

	HRESULT init();
	void release();
	void update();
	void render();

	void setText(string text) { _text = text; }
	void setPrintSpeed(float talkSpeed) { _printSpeed = talkSpeed; }


	void setIsStart(bool isStart) { _isStart = isStart; }
	//�ؽ�Ʈ,��Ʈ���ӵ�,ä�ý���
	void setDialogue(image* npcPicture, string text, float talkSpeed);
	bool getisStart() { return _isStart; }
	int getPrintLen() { return _printLen; }
	string getText() { return _text; }

	void setPrintLen(int printLen) { _printLen = printLen; }
};

