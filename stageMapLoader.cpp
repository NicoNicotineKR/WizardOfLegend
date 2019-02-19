#include "stdafx.h"
#include "stageMapLoader.h"
#pragma warning(disable: 4996)


stageMapLoader::stageMapLoader()
{
}


stageMapLoader::~stageMapLoader()
{
}

void stageMapLoader::LoadMap(vvMap * vvMapAddress, int * tileNumX, int * tileNumY, int mapNum)
{
	
	vvMapAddress->clear();
	//vObjMgrAddress->clear();

	HANDLE file;
	DWORD read;

	//itoa(무엇을, 어디에저장,몇진수?)
	//strcat_s(des, sizof(des), sour) '\0'에 붙여넣기
	//잘린것 = strtok_s(무엇을 / seperator/ 남은거저장)
	//strtok_s 가 실행될떄마다 원본의 seperator 부분을 NULL로 만들어버린다.
	//연속해서 사용시, token = strtok_s(원본, seperator, &context)는 한번만 사용,
	//		  이후에는, token = strtok_s(NULL, seperator, &context)로 계속 진행한다.
	//	char* token , context 임에 유의.


	// tilenumX] tilenumY]
	// 인덱스
	// tile - pos, rc, framex/y, attr, imgKey
	char load[500000] = {};
	char* token;			//1번 잘려진 문자열의 주소
	char* context;			//2번 잘려진 문자열의
	char tmp[10] = {};
	const char* seperator = "/";	//구분자
	char fileName[20] = "saveMap";
	//char tmpStr[128];
	int tmpInt;

	//	로드할 파일이름 설정
	itoa(mapNum, tmp, 10);
	strcat_s(fileName, sizeof(fileName), tmp);
	strcat_s(fileName, sizeof(fileName), ".map");


	file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, load, sizeof(load), &read, NULL);
	CloseHandle(file);


	//	=== 여까지 load에 데이터 입력받은 상태 ===

	//	맵 크기 로드
	token = strtok_s(load, "]", &context);
	tmpInt = atoi(token);
	*tileNumX = tmpInt;
	_tileNumX = tmpInt;
	token = strtok_s(NULL, "]", &context);
	tmpInt = atoi(token);
	*tileNumY = tmpInt;
	_tileNumY = tmpInt;

	tile* tmpTile;
	//objectInfo* tmpObj;
	// tile - pos, rc, framex/y, attr, imgKey
	for (int i = 0; i < *tileNumY; i++) {
		vLine vLineX;
		vLineX.clear();
		for (int j = 0; j < *tileNumX; j++) {
			tmpTile = new tile;
			//	인덱스
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
				//	pos
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

				//	tileframeX
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileFrameX(tmpInt);

				//	tileframeY
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileFrameY(tmpInt);

				//	attribute
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopTileAttr(tmpInt);

				//	imgKeyValue
				token = strtok_s(NULL, "/", &context);
				tmpTile->setTopTileImgKey(token);

				//	이미지 키로 받은다음 찾아서 넣어줘야함
				if (token == "none") {
					tmpTile->setTopTileImage(nullptr);
				}
				else {
					tmpTile->setTopTileImage(IMAGEMANAGER->findImage(token));
				}


			}
			//	타일정보 로드 끗

			// 오브젝트정보 로드 - pos, rc, framex/y, attr, imgKey
			{
				//	pos
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

				//	tileframeX
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjFrameX(tmpInt);

				//	tileframeY
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjFrameY(tmpInt);

				//	attribute
				token = strtok_s(NULL, "/", &context);
				tmpInt = atoi(token);
				tmpTile->setTopObjAttr(tmpInt);

				//	imgKeyValue
				token = strtok_s(NULL, "/", &context);
				tmpTile->setTopObjImgKey(token);

				//	이미지 키로 받은다음 찾아서 넣어줘야함
				if (token == "none") {
					tmpTile->setTopObjImage(nullptr);
				}
				else {
					tmpTile->setTopObjImage(IMAGEMANAGER->findImage(token));
				}
			}
			

			//	isAvailMove
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			if (tmpInt == 0)
				tmpTile->setIsAvailMove(false);
			else if (tmpInt == 1)
				tmpTile->setIsAvailMove(true);

			//	AreaIdx
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpTile->setAreaIdx(tmpInt);


			vLineX.push_back(tmpTile);

		}	// for j 끝
		(*vvMapAddress).push_back(vLineX);
	}
	

	//	여까지 vvMap에 로드 완료.
	//	이 데이터를 기반으로, Obj 를 생성하고, vvMap에 잔류 데이터 제거.
	/*
	
	for (int i = 0; i < *tileNumY; i++) {
		for (int j = 0; j < *tileNumX; j++) {
			//	뒤져봤는데 오브젝트 이미지가 있다면!!!
			if ((*vvMapAddress)[i][j]->getTopObjImg() != nullptr) {
				//	임시 오브젝트 하나 새로 맹글고
				tmpObj = new objectInfo;
				tmpObj->ClearNewObj();

				//인덱스설정
				tmpObj->setIdx((*vvMapAddress)[i][j]->getTopIdx());
				//이미지 설정
				tmpObj->setImg((*vvMapAddress)[i][j]->getTopObjImg());
				//이미지 키네임 설정
				tmpObj->setImgKeyName((*vvMapAddress)[i][j]->getTopObjImgKey());
				//	(pos와 rc는 밑에서 한번에)

				//	속성 attr
				int tmpAttr = (*vvMapAddress)[i][j]->getTopObjAttr();
				tmpObj->setAttr(tmpAttr);

				//	시작프레임넘버 설정
				POINT tmpStartFrame;
				tmpStartFrame.x = (*vvMapAddress)[i][j]->getTopObjFrameX();
				tmpStartFrame.y = (*vvMapAddress)[i][j]->getTopObjFrameY();
				tmpObj->setStartFrame(tmpStartFrame);

				//	사이즈 하나씩 증가시켜가면서, tmpAttr과 같은애들 찾으면서 지워준다.
				POINT tmpSize = { 1,1 };
				POINT tmpEndFrame = tmpStartFrame;

				//	맵에서, X축으로 하나씩 증가시키면서 찾아보니, 그놈이 속성이 같더라.	(tmpSize.x 는 1부터 시작함)
				while (1) {
					//	처음들어오면, x축으로 한칸 움직인 타일의 오브제

					if (j + tmpSize.x > (*tileNumX) - 1)	break;		//	인덱스 아웃 예외처리
					if ((*vvMapAddress)[i][j + tmpSize.x]->getTopObjAttr() != tmpAttr)		break;	//	다르면 끝내라
					//	여기까지왔다는건, Attr이 같은것이라는거.
					tmpEndFrame.x = (*vvMapAddress)[i][j + tmpSize.x]->getTopObjFrameX();		//	얘의 FrameX를 EndFrame.x로 갱신한다.
					(*vvMapAddress)[i][j + tmpSize.x]->setTopObjAttr(0);						//	이놈 속성은 0으로 초기화한다.

					tmpSize.x++;																//	마지막에 쁠쁠
				}

				//	맵에서, Y축으로 하나씩 증가시키면서 찾아보니, 그놈이 속성이 같더라.	(tmpSize.y 는 1부터 시작함)
				while (1) {
					//	처음들어오면, x축으로 한칸 움직인 타일의 오브제

					if (i + tmpSize.y > (*tileNumY) - 1)	break;		//	인덱스 아웃 예외처리
					if ((*vvMapAddress)[i + tmpSize.y][j]->getTopObjAttr() != tmpAttr)		break;	//	다르면 끝내라
					//	여기까지왔다는건, Attr이 같은것이라는거.
					tmpEndFrame.y = (*vvMapAddress)[i + tmpSize.y][j]->getTopObjFrameY();		//	얘의 FrameX를 EndFrame.x로 갱신한다.
					(*vvMapAddress)[i + tmpSize.y][j]->setTopObjAttr(0);						//	이놈 속성은 0으로 초기화한다.

					tmpSize.y++;																//	마지막에 쁠쁠
				}

				//	여까지왔으면, tmpSize로, 이녀석의 크기를 유추가능. 시작인덱스는 [i][j]
				//	크기만큼 이 오브젝트 속성을 0으로 초기화
				for (int idY = i; idY < i + tmpSize.y; idY++) {
					for (int idX = j; idX < j + tmpSize.x; idX++) {
						(*vvMapAddress)[idY][idX]->setTopObjAttr(0);
					}
				}

				//	사이즈, endFrame, 알아냈고, 맵데이터에 오브제 속성 초기화 완료.================

				tmpObj->setSize(tmpSize);
				tmpObj->setEndFrame(tmpEndFrame);

				tmpObj->setPosLT({ j*TOP_TILESIZE, i*TOP_TILESIZE });			//	1픽셀 오류날 수 있음@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				tmpObj->setRc(RectMake(j*TOP_TILESIZE, i*TOP_TILESIZE, tmpSize.x*TOP_TILESIZE, tmpSize.y*TOP_TILESIZE));

				//	여기까지하면, tmpObj 셋팅 완료.
				vObjMgrAddress->push_back(tmpObj);


			}	//	오브젝 발견 if 끝
		}
	}
	*/




}

void stageMapLoader::MakeObjects(vvMap * vvMapAddress, vObjects * vectorObjAddress, enemyMgr* enemyMgr)
{
	//	여까지 vvMap에 로드 완료.
	//	이 데이터를 기반으로, Obj 를 생성하고, vvMap에 잔류 데이터 제거.
	objectInfo* tmpObj;
	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {

			//	뒤져봤는데 오브젝트 이미지가 있다면!!!
			if ((*vvMapAddress)[i][j]->getTopObjImg() != nullptr) {
				int objAttr = (*vvMapAddress)[i][j]->getTopObjAttr();
				//	그놈이 몹이어따
				if (UNIT_GHOUL <= objAttr && objAttr <= UNIT_ARCHER) {

					POINTFLOAT generatePos;
					generatePos.x = j * TOP_TILESIZE;
					generatePos.x = i * TOP_TILESIZE;
					//	몹생성!
					_enemyMgr->makeEnemy(objAttr, generatePos);

					//	내가 읽은 몹데이터 싹 지움
					POINT tmpSize = { 1,1 };
					while (1) {
						//	처음들어오면, x축으로 한칸 움직인 타일의 오브제
						if (j + tmpSize.x > (_tileNumX)-1)	break;		//	인덱스 아웃 예외처리
						if ((*vvMapAddress)[i][j + tmpSize.x]->getTopObjAttr() != objAttr)		break;	//	다르면 끝내라

						//	여기까지왔다는건, Attr이 같은것이라는거.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjAttr(0);						//	이놈 속성은 0으로 초기화한다.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjImage(nullptr);					//	이놈 이미지는 nullptr;
						tmpSize.x++;																//	마지막에 쁠쁠
					}
					//	맵에서, Y축으로 하나씩 증가시키면서 찾아보니, 그놈이 속성이 같더라.	(tmpSize.y 는 1부터 시작함)
					while (1) {
						//	처음들어오면, x축으로 한칸 움직인 타일의 오브제

						if (i + tmpSize.y > (_tileNumY)-1)	break;		//	인덱스 아웃 예외처리
						if ((*vvMapAddress)[i + tmpSize.y][j]->getTopObjAttr() != objAttr)		break;	//	다르면 끝내라
						//	여기까지왔다는건, Attr이 같은것이라는거.
						
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjAttr(0);						//	이놈 속성은 0으로 초기화한다.
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjImage(nullptr);					//이놈 이미지는 nullptr;

						tmpSize.y++;																//	마지막에 쁠쁠
					}

					//	여까지왔으면, tmpSize로, 이녀석의 크기를 유추가능. 시작인덱스는 [i][j]
					//	크기만큼 이 오브젝트 속성을 0으로 초기화
					for (int idY = i; idY < i + tmpSize.y; idY++) {
						for (int idX = j; idX < j + tmpSize.x; idX++) {
							(*vvMapAddress)[idY][idX]->setTopObjAttr(0);
							(*vvMapAddress)[idY][idX]->setTopObjImage(nullptr);
						}
					}

//=================================================================================

				}
				//	걍 오브젝이어따
				else {
					//	임시 오브젝트 하나 새로 맹글고
					tmpObj = new objectInfo;
					tmpObj->ClearNewObj();

					//인덱스설정
					tmpObj->setIdx((*vvMapAddress)[i][j]->getTopIdx());
					//이미지 설정
					tmpObj->setImg((*vvMapAddress)[i][j]->getTopObjImg());
					//이미지 키네임 설정
					tmpObj->setImgKeyName((*vvMapAddress)[i][j]->getTopObjImgKey());
					//	(pos와 rc는 밑에서 한번에)

					//	속성 attr
					int tmpAttr = (*vvMapAddress)[i][j]->getTopObjAttr();
					tmpObj->setAttr(tmpAttr);

					//	시작프레임넘버 설정
					POINT tmpStartFrame;
					tmpStartFrame.x = (*vvMapAddress)[i][j]->getTopObjFrameX();
					tmpStartFrame.y = (*vvMapAddress)[i][j]->getTopObjFrameY();
					tmpObj->setStartFrame(tmpStartFrame);

					//	사이즈 하나씩 증가시켜가면서, tmpAttr과 같은애들 찾으면서 지워준다.
					POINT tmpSize = { 1,1 };
					POINT tmpEndFrame = tmpStartFrame;

					//	맵에서, X축으로 하나씩 증가시키면서 찾아보니, 그놈이 속성이 같더라.	(tmpSize.x 는 1부터 시작함)
					while (1) {
						//	처음들어오면, x축으로 한칸 움직인 타일의 오브제

						if (j + tmpSize.x > (_tileNumX)-1)	break;		//	인덱스 아웃 예외처리
						if ((*vvMapAddress)[i][j + tmpSize.x]->getTopObjAttr() != tmpAttr)		break;	//	다르면 끝내라
						//	여기까지왔다는건, Attr이 같은것이라는거.
						tmpEndFrame.x = (*vvMapAddress)[i][j + tmpSize.x]->getTopObjFrameX();		//	얘의 FrameX를 EndFrame.x로 갱신한다.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjAttr(0);						//	이놈 속성은 0으로 초기화한다.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjImage(nullptr);					//	이놈 이미지는 nullptr;

						tmpSize.x++;																//	마지막에 쁠쁠
					}

					//	맵에서, Y축으로 하나씩 증가시키면서 찾아보니, 그놈이 속성이 같더라.	(tmpSize.y 는 1부터 시작함)
					while (1) {
						//	처음들어오면, x축으로 한칸 움직인 타일의 오브제

						if (i + tmpSize.y > (_tileNumY)-1)	break;		//	인덱스 아웃 예외처리
						if ((*vvMapAddress)[i + tmpSize.y][j]->getTopObjAttr() != tmpAttr)		break;	//	다르면 끝내라
						//	여기까지왔다는건, Attr이 같은것이라는거.
						tmpEndFrame.y = (*vvMapAddress)[i + tmpSize.y][j]->getTopObjFrameY();		//	얘의 FrameX를 EndFrame.x로 갱신한다.
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjAttr(0);						//	이놈 속성은 0으로 초기화한다.
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjImage(nullptr);					//이놈 이미지는 nullptr;

						tmpSize.y++;																//	마지막에 쁠쁠
					}

					//	여까지왔으면, tmpSize로, 이녀석의 크기를 유추가능. 시작인덱스는 [i][j]
					//	크기만큼 이 오브젝트 속성을 0으로 초기화
					for (int idY = i; idY < i + tmpSize.y; idY++) {
						for (int idX = j; idX < j + tmpSize.x; idX++) {
							(*vvMapAddress)[idY][idX]->setTopObjAttr(0);
							(*vvMapAddress)[idY][idX]->setTopObjImage(nullptr);
						}
					}

					//	사이즈, endFrame, 알아냈고, 맵데이터에 오브제 속성 초기화 완료.================

					tmpObj->setSize(tmpSize);
					tmpObj->setEndFrame(tmpEndFrame);

					tmpObj->setPosLT({ j*TOP_TILESIZE, i*TOP_TILESIZE });			//	1픽셀 오류날 수 있음@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					tmpObj->setRc(RectMake(j*TOP_TILESIZE, i*TOP_TILESIZE, tmpSize.x*TOP_TILESIZE, tmpSize.y*TOP_TILESIZE));

					//	여기까지하면, tmpObj 셋팅 완료.
					vectorObjAddress->push_back(tmpObj);
				}
			}	//	오브젝 발견 if 끝
		}
	}

}
