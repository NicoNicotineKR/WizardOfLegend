#pragma once
#include "singletonBase.h"
#include "image.h"


enum stateSelectOption
{
	EFFECT_SOUND = 0,
	MUSIC_SOUND,
	CAMERA_SHAKING,
	NUMBER_VISION,
	SYSTEM_CURSOR,
	LANGUAGE,
	RESET,
	BACK,
	E_OPTION_KINDS_END,
};
struct tagOptionButton
{
	image* img;
	RECT rc;

	POINT pos;
	int idxX;
	int idxY;
	int imgAlpha;

	float ratio;
};

class optionManager : public singletonBase<optionManager>
{
private:
	image* _backBuffer2;
	//�ൿ����
	bool _isStartOption;

	int _selectOption;

	//�ɼ�
	image* _optionImg;
	int _optionAlpha;

	//����,����,ī�޶���鸲..�۾���
	tagOptionButton _optionButton[8];

	//����,����,�չ�ư
	tagOptionButton _longButton[3];
	//����ǥ�� ,�ý���Ŀ�� ������ư
	tagOptionButton _smallButton[2];

	//���콺 Ŀ��
	image* _mouse;

	bool _isBarClick[3];

	const int CONTROLBAR_MOVE_SPEED = 2;
	const int CONTROLBAR_START_XPOS = 818;
	const int CONTROLBAR_END_XPOS = 1054;
	const int CONTROLBAR_LENGTH = 236;
	
	

public:
	optionManager();
	~optionManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void SelectOption();
	void UpDownSelectOption();
	void backTheGame();
	//������ư
	void ShortButtonControl();

	void NumberVision();
	void SystemCursor();
	//�չ�ư
	void longButtonControl();
	//���¹�ư
	void resetResult();

	

	HDC getMemDC() { return _backBuffer2->getMemDC(); }
	void LinkDC(image* backBuffer) {_backBuffer2 = backBuffer;}

	void setIsStartOption(bool isStartOption) { _isStartOption = isStartOption; }
	bool getIsStartOption(){return _isStartOption;}
};

