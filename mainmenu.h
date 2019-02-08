#pragma once
#include "gameNode.h"
#include "mapEditor.h"

enum stateMainMenu
{
	RUN_WIZARD = 0,
	TITLE_ALPHA_UP,
	PRESS_ENTER,
	MOVE_THE_TITLE_FONT,
	MAIN_MENU,
	SELECT_OPTION,
};
enum stateSelectMenu
{
	SINGLE_PLAYER = 0,
	MAP_TOOL = 1,
	OPTION = 2,
	STAFF = 3,
	END = 4,
};
struct tagButton
{
	image* img;
	RECT rc;

	POINT pos;
	int idxX;
	int idxY;
	int imgAlpha;
};
class mainmenu : public gameNode
{
private:
	int _mainMenuState;

	//시작전 카운트
	int _startCount;

	//인트로화면 알파값
	image* _title;
	int _titleAlpha;

	//로딩이미지
	image* _loading;
	int _loadingIdx;
	int _loadingAlpha;
	int _loadingFrameCount;

	//pressTheEnterButton
	image* _pressTheEnterButton;
	int _pressTheEnterButtonAlpha;
	bool _isPressTheEnterButtonOn;
	bool _isPressTheEnterButtonBlink;

	//타이틀로고
	image* _titleLogo;
	int _titleLogoAlpha;
	int _titleLogoIdxY;

	//메인메뉴
	tagButton _button[5];
	int _selectMenu;

	mapEditor* _mapEditor;


	//mainMenuState = 1
	const int LOADING_ALPHA_SPEED = 6;
	//mainMenuState = 2
	const int TITLE_START_COUNT = 300;
	//const int TITLE_START_COUNT = 0;
	const int TITLE_ALPHA_UP_SPEED = 1;
	//mainMenuState = 3
	const int PRESS_THE_ENTER_BUTTON_ALPHA_MIN = 100;
	const int PRESS_THE_ENTER_BUTTON_BLINK_SPEED = 3;
	//mainMenuState = 4
	const int TITLE_ALPHA_MIN = 100;
	const int TITLE_ALPHA_DOWN_SPEED = 7;
	const int TITLELOGO_MOVE_SPEED = 10;
	const int TITLELOGO_POS_Y = 200;

	//mainMenuState = 6
	const int TITLELOGO_ALPHA_DOWN_SPEED = 5;
public:
	mainmenu();
	~mainmenu();

	HRESULT init();
	void release();
	void update();
	void render();

	void RunWizard();
	void TitleAlphaUp();
	void PressTheEnterButton();
	void MoveTheTitleFont();
	void SelectMenu();
	void EnterTheOption();

	void setMainMenuState(int mainMenuState) { _mainMenuState = mainMenuState; }
	void setTitleLogoAlpha(int titleLogoAlpha) { _titleLogoAlpha = titleLogoAlpha; }
	void OptionPressBack(int mainMenuState, int titleLogoAlpha);
};

