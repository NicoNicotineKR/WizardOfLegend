#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tile : public gameNode
{
private:
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

	void setTopIdx(POINT topIdx) { _topIdx = topIdx; }
	void setTopTileImage(image* topTileImage) { _topTile.img = topTileImage; }
	void setTopTileImageSet(tagImgSet imgSet) { _topTile = imgSet; }
	void setTopObjImageSet(tagImgSet imgSet) { _topObj = imgSet; }
	void setIsAvailMove(bool value) { _isAvailMove = value; }
	void setAreaIdx(int areaIdx) { _areaIdx = areaIdx; }


	void setParent(tile* parent) { _parent = parent; }




};

