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

	//itoa(������, �������,������?)
	//strcat_s(des, sizof(des), sour) '\0'�� �ٿ��ֱ�
	//�߸��� = strtok_s(������ / seperator/ ����������)
	//strtok_s �� ����ɋ����� ������ seperator �κ��� NULL�� ����������.
	//�����ؼ� ����, token = strtok_s(����, seperator, &context)�� �ѹ��� ���,
	//		  ���Ŀ���, token = strtok_s(NULL, seperator, &context)�� ��� �����Ѵ�.
	//	char* token , context �ӿ� ����.


	// tilenumX] tilenumY]
	// �ε���
	// tile - pos, rc, framex/y, attr, imgKey
	char load[500000] = {};
	char* token;			//1�� �߷��� ���ڿ��� �ּ�
	char* context;			//2�� �߷��� ���ڿ���
	char tmp[10] = {};
	const char* seperator = "/";	//������
	char fileName[20] = "saveMap";
	//char tmpStr[128];
	int tmpInt;

	//	�ε��� �����̸� ����
	itoa(mapNum, tmp, 10);
	strcat_s(fileName, sizeof(fileName), tmp);
	strcat_s(fileName, sizeof(fileName), ".map");


	file = CreateFile(fileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, load, sizeof(load), &read, NULL);
	CloseHandle(file);


	//	=== ������ load�� ������ �Է¹��� ���� ===

	//	�� ũ�� �ε�
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
			//	�ε���
			POINT tmpIdx;

			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpIdx.x = tmpInt;
			token = strtok_s(NULL, "/", &context);
			tmpInt = atoi(token);
			tmpIdx.y = tmpInt;
			tmpTile->setTopIdx(tmpIdx);

			// Ÿ������ �ε� - pos, rc, framex/y, attr, imgKey
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

				//	�̹��� Ű�� �������� ã�Ƽ� �־������
				if (token == "none") {
					tmpTile->setTopTileImage(nullptr);
				}
				else {
					tmpTile->setTopTileImage(IMAGEMANAGER->findImage(token));
				}


			}
			//	Ÿ������ �ε� ��

			// ������Ʈ���� �ε� - pos, rc, framex/y, attr, imgKey
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

				//	�̹��� Ű�� �������� ã�Ƽ� �־������
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

		}	// for j ��
		(*vvMapAddress).push_back(vLineX);
	}
	

	//	������ vvMap�� �ε� �Ϸ�.
	//	�� �����͸� �������, Obj �� �����ϰ�, vvMap�� �ܷ� ������ ����.
	/*
	
	for (int i = 0; i < *tileNumY; i++) {
		for (int j = 0; j < *tileNumX; j++) {
			//	�����ôµ� ������Ʈ �̹����� �ִٸ�!!!
			if ((*vvMapAddress)[i][j]->getTopObjImg() != nullptr) {
				//	�ӽ� ������Ʈ �ϳ� ���� �ͱ۰�
				tmpObj = new objectInfo;
				tmpObj->ClearNewObj();

				//�ε�������
				tmpObj->setIdx((*vvMapAddress)[i][j]->getTopIdx());
				//�̹��� ����
				tmpObj->setImg((*vvMapAddress)[i][j]->getTopObjImg());
				//�̹��� Ű���� ����
				tmpObj->setImgKeyName((*vvMapAddress)[i][j]->getTopObjImgKey());
				//	(pos�� rc�� �ؿ��� �ѹ���)

				//	�Ӽ� attr
				int tmpAttr = (*vvMapAddress)[i][j]->getTopObjAttr();
				tmpObj->setAttr(tmpAttr);

				//	���������ӳѹ� ����
				POINT tmpStartFrame;
				tmpStartFrame.x = (*vvMapAddress)[i][j]->getTopObjFrameX();
				tmpStartFrame.y = (*vvMapAddress)[i][j]->getTopObjFrameY();
				tmpObj->setStartFrame(tmpStartFrame);

				//	������ �ϳ��� �������Ѱ��鼭, tmpAttr�� �����ֵ� ã���鼭 �����ش�.
				POINT tmpSize = { 1,1 };
				POINT tmpEndFrame = tmpStartFrame;

				//	�ʿ���, X������ �ϳ��� ������Ű�鼭 ã�ƺ���, �׳��� �Ӽ��� ������.	(tmpSize.x �� 1���� ������)
				while (1) {
					//	ó��������, x������ ��ĭ ������ Ÿ���� ������

					if (j + tmpSize.x > (*tileNumX) - 1)	break;		//	�ε��� �ƿ� ����ó��
					if ((*vvMapAddress)[i][j + tmpSize.x]->getTopObjAttr() != tmpAttr)		break;	//	�ٸ��� ������
					//	��������Դٴ°�, Attr�� �������̶�°�.
					tmpEndFrame.x = (*vvMapAddress)[i][j + tmpSize.x]->getTopObjFrameX();		//	���� FrameX�� EndFrame.x�� �����Ѵ�.
					(*vvMapAddress)[i][j + tmpSize.x]->setTopObjAttr(0);						//	�̳� �Ӽ��� 0���� �ʱ�ȭ�Ѵ�.

					tmpSize.x++;																//	�������� �ܻ�
				}

				//	�ʿ���, Y������ �ϳ��� ������Ű�鼭 ã�ƺ���, �׳��� �Ӽ��� ������.	(tmpSize.y �� 1���� ������)
				while (1) {
					//	ó��������, x������ ��ĭ ������ Ÿ���� ������

					if (i + tmpSize.y > (*tileNumY) - 1)	break;		//	�ε��� �ƿ� ����ó��
					if ((*vvMapAddress)[i + tmpSize.y][j]->getTopObjAttr() != tmpAttr)		break;	//	�ٸ��� ������
					//	��������Դٴ°�, Attr�� �������̶�°�.
					tmpEndFrame.y = (*vvMapAddress)[i + tmpSize.y][j]->getTopObjFrameY();		//	���� FrameX�� EndFrame.x�� �����Ѵ�.
					(*vvMapAddress)[i + tmpSize.y][j]->setTopObjAttr(0);						//	�̳� �Ӽ��� 0���� �ʱ�ȭ�Ѵ�.

					tmpSize.y++;																//	�������� �ܻ�
				}

				//	������������, tmpSize��, �̳༮�� ũ�⸦ ���߰���. �����ε����� [i][j]
				//	ũ�⸸ŭ �� ������Ʈ �Ӽ��� 0���� �ʱ�ȭ
				for (int idY = i; idY < i + tmpSize.y; idY++) {
					for (int idX = j; idX < j + tmpSize.x; idX++) {
						(*vvMapAddress)[idY][idX]->setTopObjAttr(0);
					}
				}

				//	������, endFrame, �˾Ƴ°�, �ʵ����Ϳ� ������ �Ӽ� �ʱ�ȭ �Ϸ�.================

				tmpObj->setSize(tmpSize);
				tmpObj->setEndFrame(tmpEndFrame);

				tmpObj->setPosLT({ j*TOP_TILESIZE, i*TOP_TILESIZE });			//	1�ȼ� ������ �� ����@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				tmpObj->setRc(RectMake(j*TOP_TILESIZE, i*TOP_TILESIZE, tmpSize.x*TOP_TILESIZE, tmpSize.y*TOP_TILESIZE));

				//	��������ϸ�, tmpObj ���� �Ϸ�.
				vObjMgrAddress->push_back(tmpObj);


			}	//	������ �߰� if ��
		}
	}
	*/




}

void stageMapLoader::MakeObjects(vvMap * vvMapAddress, vObjects * vectorObjAddress, enemyMgr* enemyMgr)
{
	//	������ vvMap�� �ε� �Ϸ�.
	//	�� �����͸� �������, Obj �� �����ϰ�, vvMap�� �ܷ� ������ ����.
	objectInfo* tmpObj;
	for (int i = 0; i < _tileNumY; i++) {
		for (int j = 0; j < _tileNumX; j++) {

			//	�����ôµ� ������Ʈ �̹����� �ִٸ�!!!
			if ((*vvMapAddress)[i][j]->getTopObjImg() != nullptr) {
				int objAttr = (*vvMapAddress)[i][j]->getTopObjAttr();
				//	�׳��� ���̾��
				if (UNIT_GHOUL <= objAttr && objAttr <= UNIT_ARCHER) {

					POINTFLOAT generatePos;
					generatePos.x = j * TOP_TILESIZE;
					generatePos.x = i * TOP_TILESIZE;
					//	������!
					_enemyMgr->makeEnemy(objAttr, generatePos);

					//	���� ���� �������� �� ����
					POINT tmpSize = { 1,1 };
					while (1) {
						//	ó��������, x������ ��ĭ ������ Ÿ���� ������
						if (j + tmpSize.x > (_tileNumX)-1)	break;		//	�ε��� �ƿ� ����ó��
						if ((*vvMapAddress)[i][j + tmpSize.x]->getTopObjAttr() != objAttr)		break;	//	�ٸ��� ������

						//	��������Դٴ°�, Attr�� �������̶�°�.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjAttr(0);						//	�̳� �Ӽ��� 0���� �ʱ�ȭ�Ѵ�.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjImage(nullptr);					//	�̳� �̹����� nullptr;
						tmpSize.x++;																//	�������� �ܻ�
					}
					//	�ʿ���, Y������ �ϳ��� ������Ű�鼭 ã�ƺ���, �׳��� �Ӽ��� ������.	(tmpSize.y �� 1���� ������)
					while (1) {
						//	ó��������, x������ ��ĭ ������ Ÿ���� ������

						if (i + tmpSize.y > (_tileNumY)-1)	break;		//	�ε��� �ƿ� ����ó��
						if ((*vvMapAddress)[i + tmpSize.y][j]->getTopObjAttr() != objAttr)		break;	//	�ٸ��� ������
						//	��������Դٴ°�, Attr�� �������̶�°�.
						
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjAttr(0);						//	�̳� �Ӽ��� 0���� �ʱ�ȭ�Ѵ�.
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjImage(nullptr);					//�̳� �̹����� nullptr;

						tmpSize.y++;																//	�������� �ܻ�
					}

					//	������������, tmpSize��, �̳༮�� ũ�⸦ ���߰���. �����ε����� [i][j]
					//	ũ�⸸ŭ �� ������Ʈ �Ӽ��� 0���� �ʱ�ȭ
					for (int idY = i; idY < i + tmpSize.y; idY++) {
						for (int idX = j; idX < j + tmpSize.x; idX++) {
							(*vvMapAddress)[idY][idX]->setTopObjAttr(0);
							(*vvMapAddress)[idY][idX]->setTopObjImage(nullptr);
						}
					}

//=================================================================================

				}
				//	�� �������̾��
				else {
					//	�ӽ� ������Ʈ �ϳ� ���� �ͱ۰�
					tmpObj = new objectInfo;
					tmpObj->ClearNewObj();

					//�ε�������
					tmpObj->setIdx((*vvMapAddress)[i][j]->getTopIdx());
					//�̹��� ����
					tmpObj->setImg((*vvMapAddress)[i][j]->getTopObjImg());
					//�̹��� Ű���� ����
					tmpObj->setImgKeyName((*vvMapAddress)[i][j]->getTopObjImgKey());
					//	(pos�� rc�� �ؿ��� �ѹ���)

					//	�Ӽ� attr
					int tmpAttr = (*vvMapAddress)[i][j]->getTopObjAttr();
					tmpObj->setAttr(tmpAttr);

					//	���������ӳѹ� ����
					POINT tmpStartFrame;
					tmpStartFrame.x = (*vvMapAddress)[i][j]->getTopObjFrameX();
					tmpStartFrame.y = (*vvMapAddress)[i][j]->getTopObjFrameY();
					tmpObj->setStartFrame(tmpStartFrame);

					//	������ �ϳ��� �������Ѱ��鼭, tmpAttr�� �����ֵ� ã���鼭 �����ش�.
					POINT tmpSize = { 1,1 };
					POINT tmpEndFrame = tmpStartFrame;

					//	�ʿ���, X������ �ϳ��� ������Ű�鼭 ã�ƺ���, �׳��� �Ӽ��� ������.	(tmpSize.x �� 1���� ������)
					while (1) {
						//	ó��������, x������ ��ĭ ������ Ÿ���� ������

						if (j + tmpSize.x > (_tileNumX)-1)	break;		//	�ε��� �ƿ� ����ó��
						if ((*vvMapAddress)[i][j + tmpSize.x]->getTopObjAttr() != tmpAttr)		break;	//	�ٸ��� ������
						//	��������Դٴ°�, Attr�� �������̶�°�.
						tmpEndFrame.x = (*vvMapAddress)[i][j + tmpSize.x]->getTopObjFrameX();		//	���� FrameX�� EndFrame.x�� �����Ѵ�.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjAttr(0);						//	�̳� �Ӽ��� 0���� �ʱ�ȭ�Ѵ�.
						(*vvMapAddress)[i][j + tmpSize.x]->setTopObjImage(nullptr);					//	�̳� �̹����� nullptr;

						tmpSize.x++;																//	�������� �ܻ�
					}

					//	�ʿ���, Y������ �ϳ��� ������Ű�鼭 ã�ƺ���, �׳��� �Ӽ��� ������.	(tmpSize.y �� 1���� ������)
					while (1) {
						//	ó��������, x������ ��ĭ ������ Ÿ���� ������

						if (i + tmpSize.y > (_tileNumY)-1)	break;		//	�ε��� �ƿ� ����ó��
						if ((*vvMapAddress)[i + tmpSize.y][j]->getTopObjAttr() != tmpAttr)		break;	//	�ٸ��� ������
						//	��������Դٴ°�, Attr�� �������̶�°�.
						tmpEndFrame.y = (*vvMapAddress)[i + tmpSize.y][j]->getTopObjFrameY();		//	���� FrameX�� EndFrame.x�� �����Ѵ�.
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjAttr(0);						//	�̳� �Ӽ��� 0���� �ʱ�ȭ�Ѵ�.
						(*vvMapAddress)[i + tmpSize.y][j]->setTopObjImage(nullptr);					//�̳� �̹����� nullptr;

						tmpSize.y++;																//	�������� �ܻ�
					}

					//	������������, tmpSize��, �̳༮�� ũ�⸦ ���߰���. �����ε����� [i][j]
					//	ũ�⸸ŭ �� ������Ʈ �Ӽ��� 0���� �ʱ�ȭ
					for (int idY = i; idY < i + tmpSize.y; idY++) {
						for (int idX = j; idX < j + tmpSize.x; idX++) {
							(*vvMapAddress)[idY][idX]->setTopObjAttr(0);
							(*vvMapAddress)[idY][idX]->setTopObjImage(nullptr);
						}
					}

					//	������, endFrame, �˾Ƴ°�, �ʵ����Ϳ� ������ �Ӽ� �ʱ�ȭ �Ϸ�.================

					tmpObj->setSize(tmpSize);
					tmpObj->setEndFrame(tmpEndFrame);

					tmpObj->setPosLT({ j*TOP_TILESIZE, i*TOP_TILESIZE });			//	1�ȼ� ������ �� ����@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					tmpObj->setRc(RectMake(j*TOP_TILESIZE, i*TOP_TILESIZE, tmpSize.x*TOP_TILESIZE, tmpSize.y*TOP_TILESIZE));

					//	��������ϸ�, tmpObj ���� �Ϸ�.
					vectorObjAddress->push_back(tmpObj);
				}
			}	//	������ �߰� if ��
		}
	}

}
