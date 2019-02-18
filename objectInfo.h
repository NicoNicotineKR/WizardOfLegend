#pragma once
#include "gameNode.h"
#include "tileNode.h";
class objectInfo : public gameNode
{
private:
	POINT	_idx;		// 해당 오브제 LT의 인덱스
	image*	_img;
	POINT	_posLT;
	RECT	_rc;
	POINT	_startFrame;		//	그리기 시작프레임
	POINT	_endFrame;
	POINT	_size;				//	가로세로 타일 갯수
	int		_attribute;
	string	_imgKeyName;
	

public:
	objectInfo();
	~objectInfo();

	HRESULT ClearNewObj();
	void render();
	void CamRender(int camLeft, int camTop);


	//====	게셋키 ======

	POINT getIdx() { return _idx; }
	void setIdx(POINT idx) { _idx = idx; }

	image* getImg() { return _img; }
	void setImg(image* img) { _img = img; }

	POINT getPosLT() { return _posLT; }
	void setPosLT(POINT posLT) { _posLT = posLT; }

	RECT getRc() { return _rc; }
	void setRc(RECT rc) { _rc = rc; }

	POINT getStartFrame() { return _startFrame; }
	void setStartFrame(POINT startFrame) { _startFrame = startFrame; }
	
	POINT getEndFrame() { return _endFrame; }
	void setEndFrame(POINT endFrame) { _endFrame = endFrame; }

	POINT getSize() { return _size; }
	void setSize(POINT size) { _size = size; }

	int getAttr() { return _attribute; }
	void setAttr(int attr) { _attribute = attr; }

	string getImgKeyName() { return _imgKeyName; }
	void setImgKeyName(string imgKeyName) { _imgKeyName = imgKeyName; }


};

