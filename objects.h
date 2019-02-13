#pragma once
#include "gameNode.h"
#include "tileNode.h"
class objects : public gameNode
{
private:
	image* _img;
	POINT _posLT;
	RECT _rc;
	int _frameX;
	int _frameY;
	int _attribute;
	string _imgKeyValue;
	POINT _xySize;			//	¸îÄ­¸Ô³Ä





public:
	objects();
	~objects();

	HRESULT init();
	void release();
	void update();
	void render();

	void SetObj(image* img, POINT posLT, int frameX, int frameY, int attr, string keyName, POINT xySize);





	image* getImg() { return _img; }
	void setImg(image* img) { _img = img; }

	POINT getPosLT() { return _posLT; }
	void setPosLT(POINT posLT) { _posLT = posLT; }

	RECT getRc() { return _rc; }
	void setRc(RECT rc) { _rc = rc; }

	int getFrameX() { return _frameX; }
	void setFrameX(int frameX) { _frameX = frameX; }

	int getFrameY() { return _frameY; }
	void setFrameY(int frameY) { _frameY = frameY; }

	string getImgKeyValue() { return _imgKeyValue; }
	void setImgKeyValue(string keyName) { _imgKeyValue = keyName; }

	POINT getXYSize() { return _xySize; }
	void setXYSize(POINT xySize) { _xySize = xySize; }

};

