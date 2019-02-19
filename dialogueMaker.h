#pragma once
#include "gameNode.h"
class dialogueMaker : public gameNode
{
private:
	//채팅이미지
	image* _chatBoxImg;
	//받아올 Npc 이미지(이미지매니저에 추가되잇어야됨)
	image* _npcPicture;
	//가져올 대사
	string _text;

	//시작할시
	bool _isStart;



	//TimeManger사용을 위한 변수들
	float _time;
	//출력속도
	float _printSpeed;

	//받아온 글자길이
	int _printLen;

	//아스키문자 비교용
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
	//텍스트,폰트별속도,채팅시작
	void setDialogue(image* npcPicture, string text, float talkSpeed);
	bool getisStart() { return _isStart; }
	int getPrintLen() { return _printLen; }
	string getText() { return _text; }

	void setPrintLen(int printLen) { _printLen = printLen; }
};

