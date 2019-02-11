#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tile : public gameNode
{
private:
	//struct tagImgSet {
	//	image* img;
	//	POINT pos;
	//	RECT rc;
	//	int frameX;
	//	int frameY;
	//	int attribute;
	//
	//};
	POINT _topIdx;		// �ش� Ÿ�� �ε���
	tagImgSet _topTile;	// Ÿ�� ����
	tagImgSet _topObj;	// ������Ʈ ���� -> null�� �ʱ�ȭ �Ǿ��ֽ�(���ٸ�)

	bool _isAvailMove;  // Ʈ��� �����ս�
	int _areaIdx;		// �������� ���̹�

	tile* _parent;		// ����
	
	int _gScore;
	int _hScore;
	int _fScore;

public:
	tile();
	~tile();

	HRESULT init();
	void release();
	void update();
	void render();
	void CamRender(int camLeft, int camTop);
	void AlphaFrameRender(int destX, int destY, BYTE alpha);
	
	//	============ Ÿ�ϰ��� �ټ� ==========

	POINT getTopIdx() { return _topIdx; }
	image* getTopTileImg() { return _topTile.img; }
	int getTopTileFrameX() { return _topTile.frameX; }
	int getTopTileFrameY() { return _topTile.frameY; }
	POINT getTopTilePos() { return _topTile.pos; }
	RECT getTopTileRc() { return _topTile.rc; }
	int getTopTileAttr() { return _topTile.attribute; }
	string getTopTileImgKey() { return _topTile.imgKeyValue; }

	bool getIsAvailMove() { return _isAvailMove; }
	int getAreaIdx() { return _areaIdx; }

	int getGScore() { return _gScore; }
	int getHScore() { return _hScore; }
	int getFScore() { return _fScore; }

	void setTopIdx(POINT topIdx) { _topIdx = topIdx; }
	void setTopTileImage(image* topTileImage) { _topTile.img = topTileImage; }
	void setTopTileImageSet(tagImgSet imgSet) { _topTile = imgSet; }
	void setTopTileFrameX(int frameX) { _topTile.frameX = frameX; }
	void setTopTileFrameY(int frameY) { _topTile.frameY = frameY; }
	void setTopTilePos(POINT pos) { _topTile.pos = pos; }
	void setTopTileRc(RECT rc) { _topTile.rc = rc; }
	void setTopTileAttr(int attr) { _topTile.attribute = attr; }
	void setTopTileImgKey(string keyValue) { _topTile.imgKeyValue = keyValue; }

	void setIsAvailMove(bool value) { _isAvailMove = value; }
	void setAreaIdx(int areaIdx) { _areaIdx = areaIdx; }

	void setGScore(int gScore) { _gScore = gScore; }
	void setHScore(int hScore) { _hScore = hScore; }
	void setFScore(int fScore) { _fScore = fScore; }
	
	//	============ Ÿ�ϰ��� �ټ� �� ==========

	//	============ Obj���� �ټ� ==========
	
	image* getTopObjImg()		{ return _topObj.img; }
	int getTopObjFrameX()		{ return _topObj.frameX; }
	int getTopObjFrameY()		{ return _topObj.frameY; }
	POINT getTopObjPos()		{ return _topObj.pos; }
	RECT getTopObjRc()			{ return _topObj.rc; }
	int getTopObjAttr()			{ return _topObj.attribute; }
	string getTopObjImgKey()	{ return _topObj.imgKeyValue; }


	void setTopObjImage(image* topObjImage)	{ _topObj.img = topObjImage; }
	void setTopObjImageSet(tagImgSet imgSet)	{ _topObj = imgSet; }
	void setTopObjFrameX(int frameX)			{ _topObj.frameX = frameX; }
	void setTopObjFrameY(int frameY)			{ _topObj.frameY = frameY; }
	void setTopObjPos(POINT pos)				{ _topObj.pos = pos; }
	void setTopObjRc(RECT rc)					{ _topObj.rc = rc; }
	void setTopObjAttr(int attr)				{ _topObj.attribute = attr; }
	void setTopObjImgKey(string keyValue)		{ _topObj.imgKeyValue = keyValue; }

	//	============ Obj���� �ټ� �� ==========

	

	tile* getParent() { return _parent; }
	void setParent(tile* parent) { _parent = parent; }




};

