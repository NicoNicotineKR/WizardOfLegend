#pragma once
#include "gameNode.h"
#include "tile.h"
#include "objectInfo.h"

//	====	stageMapLoader�� �����Դϲ�!!!!! -> �� �ε��ϰ� ������Ʈ/���ʹ� �Ŵ����� ��������ִ¾�  ====
//	�����
//	���� �����ϰ� �ż��� vvMap, tileNum X,y �� �غ��Ѵ�.
//	�� Ŭ������ LoadMap�� �� ������ �ּҸ� �־��ش�. �̶� �ε��� �ʼ��ڵ� ���� �־��ָ� �� ���ִ�.
//	�׷� �갡 �������ϸ鼭 �˾Ƽ� �����Ͱ��� �־��ٰŽô�.
//	�׷� �غ� �� ��� vvMap��, vector<Objectinfo*> �� ������Ʈ �Ŵ�����
//	MakeObjects�� �ְ� ǫ ����ָ�,
//	����� vvMap�� ������Ʈ �Ŵ����� ���� �� �̵�.
//	������ ����Ҷ��� vvMap���� CamTileRender() �� ����Ͽ� �ȳ��Ѵ�.
//	������Ʈ�� CamRender�� ���� ������ֵ��� ����.


class stageMapLoader : public gameNode
{
private:
	typedef vector<tile*> vLine;
	typedef vector<vLine> vvMap;
	typedef vector<objectInfo*> vObjects;

	int _tileNumX;
	int _tileNumY;

public:
	stageMapLoader();
	~stageMapLoader();

	//	�ε�� �����, MakeObjects����Ͻÿ�!!!
	void LoadMap(vvMap * vvMapAddress, int * tileNumX, int * tileNumY, int stageNum);
	void MakeObjects(vvMap* vvMapAddress, vObjects* vectorObjAddress);
};


