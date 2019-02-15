#include "stdafx.h"
#include "testStage.h"


testStage::testStage()
{
}


testStage::~testStage()
{
}

HRESULT testStage::init()
{
	IMAGEMANAGER->addFrameImage("tileCastle", "images/map/CastleBaseTileSet.bmp", 704, 384, 22, 12, true, 0xFF00FF);
	IMAGEMANAGER->addFrameImage("objCastle", "images/map/CastleBaseObjSet.bmp", 736, 384, 23, 12, true, 0xFF00FF);
	_player = new player;
	_player->init();

	_tileNumX = 0;
	_tileNumY = 0;
	_vvMap.clear();

	LoadMap();   //   saveMap0.map 로드, _vvMap, _tileNumX,Y 세팅

	_aStar = new aStar;
	_aStar->init();
	_aStar->setMap(_vvMap);

	_test = RectMakeCenter(_vvMap[19][16]->getTopTilePos().x, _vvMap[19][16]->getTopTilePos().y, 32, 32);

	_myWay.clear();

	_em = new enemyMgr;
	_em->setPlayerAdress(_player);
	_em->setMapAdress(_vvMap);
	_em->init();

	return S_OK;
}

void testStage::release()
{
	_em->release();
}

void testStage::update()
{
	_player->update();
	_player->tileCheckFunc(_vvMap);
	_em->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		_em->getVEnemy()[0]->getPath()->clear();
		_myWay.clear();

		int e_posX = _em->getVEnemy()[0]->getPos().x / TOP_TILESIZE;
		int e_posY = _em->getVEnemy()[0]->getPos().y / TOP_TILESIZE;

		int p_posX = _em->getVEnemy()[0]->getPlayerPos().x / TOP_TILESIZE;
		int p_posY = _em->getVEnemy()[0]->getPlayerPos().y / TOP_TILESIZE;

		_aStar->pathFinder(PointMake(e_posX, e_posY), PointMake(p_posX, p_posY), PointMake(e_posX, e_posY), *(_em->getVEnemy()[0]->getPath()));
		for (list<POINT>::iterator iter = _em->getVEnemy()[0]->getPath()->begin();
			iter != _em->getVEnemy()[0]->getPath()->end(); ++iter)
		{
			_myWay.push_front(*iter);
		}

	}
//if (_em->getVEnemy()[0]->getState() == E_STATE::MOVE)
//{
//   aStarCount += TIMEMANAGER->getElapsedTime();
//   if (aStarCount > 0.5)
//   {
//      _myWay.clear();
//
//      _em->getVEnemy()[0]->getPath()->clear();
//
//      int e_posX = _em->getVEnemy()[0]->getPos().x / TOP_TILESIZE;
//      int e_posY = _em->getVEnemy()[0]->getPos().y / TOP_TILESIZE;
//
//		int p_posX = _em->getVEnemy()[0]->getPlayerPos().x / TOP_TILESIZE;
//		int p_posY = _em->getVEnemy()[0]->getPlayerPos().y / TOP_TILESIZE;

//      _aStar->pathFinder(PointMake(e_posX, e_posY), PointMake(p_posX, p_posY), PointMake(e_posX, e_posY), *(_em->getVEnemy()[0]->getPath()));
//      aStarCount = 0;
//
//
//      for (list<POINT>::iterator iter = _em->getVEnemy()[0]->getPath()->begin();
//         iter != _em->getVEnemy()[0]->getPath()->end(); ++iter)
//      {
//         _myWay.push_front(*iter);
//      }
//   }
//}
}

void testStage::render()
{
	RenderMap();
	_player->render(getMemDC());
	_em->render();
	if (_myWay.size() != 0)
	{
		for (_imyWay = _myWay.begin(); _imyWay != _myWay.end(); _imyWay++)
		{
			int idX = (*_imyWay).x;
			int idY = (*_imyWay).y;
	
			RECT temp = _vvMap[idY][idX]->getTopTileRc();
	
			Rectangle(getMemDC(), temp);
		}
	}
	Rectangle(getMemDC(), _test);

	int e_posX = _em->getVEnemy()[0]->getPos().x / TOP_TILESIZE;
	int e_posY = _em->getVEnemy()[0]->getPos().y / TOP_TILESIZE;

	int p_posX = _em->getVEnemy()[0]->getPlayerPos().x / TOP_TILESIZE;
	int p_posY = _em->getVEnemy()[0]->getPlayerPos().y / TOP_TILESIZE;

	//에너미 좌표 인덱스 구역 출력
	//Rectangle(getMemDC(), _vvMap[e_posY][e_posX]->getTopTileRc().left, _vvMap[e_posY][e_posX]->getTopTileRc().top
	//, _vvMap[e_posY][e_posX]->getTopTileRc().right, _vvMap[e_posY][e_posX]->getTopTileRc().bottom);

	//플레이어 좌표 인덱스 구역 출력
	//Rectangle(getMemDC(), _vvMap[p_posY][p_posX]->getTopTileRc().left, _vvMap[p_posY][p_posX]->getTopTileRc().top
	//	, _vvMap[p_posY][p_posX]->getTopTileRc().right, _vvMap[p_posY][p_posX]->getTopTileRc().bottom);
}

void testStage::RenderMap()
{
	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {
			_vvMap[i][j]->render();
		}
	}
}

void testStage::LoadMap()
{
	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {
			delete _vvMap[i][j];
			_vvMap[i][j] = nullptr;
		}
		_vvMap[i].clear();
	}
	_vvMap.clear();




	HANDLE file;
	DWORD read;

	//itoa(무엇을, 어디에저장,몇진수?)
	//strcat_s(des, sizof(des), sour) '\0'에 붙여넣기
	//잘린것 = strtok_s(무엇을 / seperator/ 남은거저장)
	//strtok_s 가 실행될떄마다 원본의 seperator 부분을 NULL로 만들어버린다.
	//연속해서 사용시, token = strtok_s(원본, seperator, &context)는 한번만 사용,
	//        이후에는, token = strtok_s(NULL, seperator, &context)로 계속 진행한다.
	//   char* token , context 임에 유의.


	// tilenumX] tilenumY]
	// 인덱스
	// tile - pos, rc, framex/y, attr, imgKey
	char load[500000] = {};
	char* token;         //1번 잘려진 문자열의 주소
	char* context;         //2번 잘려진 문자열의
	char tmp[10] = {};
	const char* seperator = "/";   //구분자
	char fileName[20] = "saveMap";
	//char tmpStr[128];
	int tmpInt;

	//   로드할 파일이름 설정
	//itoa(_curMapIdx, tmp, 10);
	//strcat_s(fileName, sizeof(fileName), tmp);
	strcat_s(fileName, sizeof(fileName), "9");
	strcat_s(fileName, sizeof(fileName), ".map");


	file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, load, sizeof(load), &read, NULL);
	CloseHandle(file);


	//   === 여까지 load에 데이터 입력받은 상태 ===

	//   맵 크기 로드
	token = strtok_s(load, "]", &context);
	tmpInt = atoi(token);
	_tileNumX = tmpInt;
	token = strtok_s(NULL, "]", &context);
	tmpInt = atoi(token);
	_tileNumY = tmpInt;

	tile* tmpTile;
	// tile - pos, rc, framex/y, attr, imgKey
	for (int i = 0; i < _tileNumY; i++) {
		vLine vLineX;
		vLineX.clear();
		for (int j = 0; j < _tileNumX; j++) {
			tmpTile = new tile;
			//   인덱스
			POINT tmpIdx;

			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpIdx.x = tmpInt;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpIdx.y = tmpInt;
			tmpTile->setTopIdx(tmpIdx);

			// 타일정보 로드 - pos, rc, framex/y, attr, imgKey
			{
				//   pos
				POINT tmpPos;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.x = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.y = tmpInt;
				tmpTile->setTopTilePos(tmpPos);

				// rect
				RECT tmpRc;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.left = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.top = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.right = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.bottom = tmpInt;
				tmpTile->setTopTileRc(tmpRc);

				//   tileframeX
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileFrameX(tmpInt);

				//   tileframeY
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileFrameY(tmpInt);

				//   attribute
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileAttr(tmpInt);

				//   imgKeyValue
				token = strtok_s(NULL, "/", &context);
				tmpTile->setTopTileImgKey(token);

				//   이미지 키로 받은다음 찾아서 넣어줘야함
				if (token == "none") {
					tmpTile->setTopTileImage(nullptr);
				}
				else {
					tmpTile->setTopTileImage(IMAGEMANAGER->findImage(token));
				}


			}
			//   타일정보 로드 끗

			// 오브젝트정보 로드 - pos, rc, framex/y, attr, imgKey
			{
				//   pos
				POINT tmpPos;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.x = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpPos.y = tmpInt;
				tmpTile->setTopObjPos(tmpPos);

				// rect
				RECT tmpRc;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.left = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.top = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.right = tmpInt;
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpRc.bottom = tmpInt;
				tmpTile->setTopObjRc(tmpRc);

				//   tileframeX
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjFrameX(tmpInt);

				//   tileframeY
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjFrameY(tmpInt);

				//   attribute
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjAttr(tmpInt);

				//   imgKeyValue
				token = strtok_s(NULL, "/", &context);
				tmpTile->setTopObjImgKey(token);

				//   이미지 키로 받은다음 찾아서 넣어줘야함
				if (token == "none") {
					tmpTile->setTopObjImage(nullptr);
				}
				else {
					tmpTile->setTopObjImage(IMAGEMANAGER->findImage(token));
				}
			}
			//   obj정보 끗

			//   isAvailMove
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			if (tmpInt == 0)
				tmpTile->setIsAvailMove(false);
			else if (tmpInt == 1)
				tmpTile->setIsAvailMove(true);

			//   AreaIdx
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setAreaIdx(tmpInt);


			vLineX.push_back(tmpTile);

		}   // for j 끝
		_vvMap.push_back(vLineX);

	}
}