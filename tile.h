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
	POINT _topIdx;
	tagImgSet _topTile;
	tagImgSet _topObj;

	bool _isAvailMove;
	int _areaIdx;

	tile* _parent;

	


public:
	tile();
	~tile();

	HRESULT init();
	void release();
	void update();
	void render();
	void CamRender(int camLeft, int camTop);
	
	//	============ 鸥老包访 百悸 ==========

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
	
	//	============ 鸥老包访 百悸 昌 ==========

	RECT getObjRc() { return _topObj.rc; }
	void setTopObjImageSet(tagImgSet imgSet) { _topObj = imgSet; }
	

	tile* getParent() { return _parent; }
	void setParent(tile* parent) { _parent = parent; }




};

