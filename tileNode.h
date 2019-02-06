#pragma once

const int TOP_TILESIZE = 32;

struct tagImgSet {
	image* img;
	POINT pos;
	RECT rc;
	int frameX;
	int frameY;
	int attribute;

};

enum E_TILETYPE_STAGE {
	TILETYPE_CASTLE,
	TILETYPE_EARTH,
	TILETYPE_FIRE,
	TILETYPE_FOREST,


};


enum E_TILE_ATR {
	TILE_NONE,
	TILE_FLOOR,
	TILE_WALL,
	TILE_HOLE,

};

enum E_TILE_OBJ {
	OBJ_NONE,
};