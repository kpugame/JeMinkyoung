#include "stdafx.h"
#include "gameStudy.h"

gameStudy::gameStudy()
{
	
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init();

	//초기화------------------------------------

	_mapImage = new image;
	_mapImage->init("mapImage.bmp", 700, 700);

	//쯔위
	_포로 = new image;
	_포로->init("포로.bmp", 600, 600);

	//퍼즐 셋업
	int tileWidth = _포로->getWidth() / TILEWIDTHNUM;	// 포로의 크기를 타일 개수로 나눈다.
	int tileHeight = _포로->getHeight() / TILEHEIGHTNUM;


	for (int y = 0; y < TILEHEIGHTNUM; ++y)	// 타일 판
	{
		for (int x = 0; x < TILEWIDTHNUM; ++x)
		{
			_tile[x][y].rc = RectMake(x * tileWidth, y*tileHeight, tileWidth, tileHeight);	// x와 y개수만큼
			_tile[x][y].idNumber = _tile[x][y].tileNumber = x + (y * TILEWIDTHNUM);
			_tile[x][y].ptDraw = PointMake(_tile[x][y].rc.left, _tile[x][y].rc.top);
			_tile[x][y].idX = x;
			_tile[x][y].idY = y;
			//x축 인덱스와 y축 인덱스 셋팅
			//각 타일마다 다른 아이디 번호를 주고
			//그림 그릴 위치를 잡아줌
		}
	}

	//섞을 카운트 셋팅
	int count = SHUFFLECOUNT;
	_shuffleCount = &count;

	//마지막 빈 타일 포인터 넣어준다
	_emptyTile = &_tile[TILEWIDTHNUM - 1][TILEHEIGHTNUM - 1];

	//섞는다
	shuffle(_emptyTile, *_shuffleCount);

	//빈 타일을 집으로~
	retraceTile();


	//-------------------------------------

	return S_OK;
}

void gameStudy::release()
{
	gameNode::release();

	//해제---------------------------------

	_mapImage->release();
	SAFE_DELETE(_mapImage);

	_포로->release();
	SAFE_DELETE(_포로);

	//----------------------------------

}

void gameStudy::update()
{
	gameNode::update();



	//갱신-----------------------------------

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int y = 0; y < TILEHEIGHTNUM; ++y)
		{
			for (int x = 0; x < TILEWIDTHNUM; ++x)
			{
				if (PtInRect(&_tile[x][y].rc, _ptMouse))
				{
					//클릭한 타일이 빈 타일이면 무시
					//if (_tile[x][y].tileNumber == TILELASTNUM) return;

					//클릭한 타일이 같은 행이나 같은 열이 아니면 무시
					if (_emptyTile->idX != _tile[x][y].idX && _emptyTile->idY != _tile[x][y].idY) return;

					//클릭한 타일과 빈 타일의 거리를 계산
					int rangeX = _emptyTile->idX - _tile[x][y].idX;
					int rangeY = _emptyTile->idY - _tile[x][y].idY;

					//같은 행열의 먼 곳을 찍었을 경우
					//절대값으로 거리만큰 반복해서 옮겨줌
					if (abs(rangeX) > 1)
					{
						//x행 연산
						for (int i = 0; i < abs(rangeX); ++i)
						{
							_emptyTile = swapTile(_emptyTile, &_tile[_emptyTile->idX + ((rangeX > 0) ? -1 : 1)][_emptyTile->idY]);
						}
					}
					else if (abs(rangeY) > 1)
					{
						//y행 연산
						for (int i = 0; i < abs(rangeY); ++i)
						{
							_emptyTile = swapTile(_emptyTile, &_tile[_emptyTile->idX][_emptyTile->idY + ((rangeY > 0) ? -1 : 1)]);
						}
					}
					else _emptyTile = swapTile(_emptyTile, &_tile[x][y]);

				}
			}
		}
	}
	
	

	//----------------------------------------
}

void gameStudy::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();

	_mapImage->render(backDC, 0, 0);

	//그리기-----------------------------------------

	
	for (int y = 0; y < TILEHEIGHTNUM; ++y)
	{
		for (int x = 0; x < TILEWIDTHNUM; ++x)
		{
			if (&_tile[x][y] == _emptyTile) continue;
			_포로->render(backDC, _tile[x][y].rc.left,
				_tile[x][y].rc.top, _tile[x][y].ptDraw.x,
				_tile[x][y].ptDraw.y,
				_tile[x][y].rc.right - _tile[x][y].rc.left,
				_tile[x][y].rc.bottom - _tile[x][y].rc.top);
		}
	}
	
	
	//------------------------------------------


	this->getBackBuffer()->render(hdc, 0, 0);
}


//추가되는 함수----------------------------------------

//셔플 함수
tagTile* gameStudy::shuffle(tagTile* tile, int count)
{
	//셔플이 끝나면 빈 타일 반환
	if (count <= 0) return tile;

	//비트연산
	const int up = 0x00000001;
	const int down = 0x00000002;
	const int left = 0x00000004;
	const int right = 0x00000008;

	int move = 0;

	//빈타일의 위치를 파악해서 이동가능한 방향을 판별
	//비트연산이므로 중복 방향이 가능하다
	if (tile->idY > 0) move = move | up;
	if (tile->idY < TILEHEIGHTNUM - 1) move = move | down;
	if (tile->idX > 0) move = move | left;
	if (tile->idX < TILEWIDTHNUM - 1) move = move | right;

	int rnd;

	switch (move)
	{
	case up + left:
		rnd = RND->getInt(2);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX - 1][tile->idY]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY-1]);
		break;
	case up + right:
		rnd = RND->getInt(2);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX + 1][tile->idY]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY - 1]);
		break;
	case down + left:
		rnd = RND->getInt(2);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX - 1][tile->idY]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY + 1]);
		break;
	case down + right:
		rnd = RND->getInt(2);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX + 1][tile->idY]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY + 1]);
		break;
	case up + left + right:
		rnd = RND->getInt(3);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX - 1][tile->idY]);
		else if (rnd == 1) _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY - 1]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX + 1][tile->idY]);
		break;
	case down + left + right:
		rnd = RND->getInt(3);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX - 1][tile->idY]);
		else if (rnd == 1) _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY + 1]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX + 1][tile->idY]);
		break;
	case up + down + right:
		rnd = RND->getInt(3);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX + 1][tile->idY]);
		else if (rnd == 1) _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY + 1]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY - 1]);
		break;
	case up + down + left:
		rnd = RND->getInt(3);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX - 1][tile->idY]);
		else if (rnd == 1) _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY + 1]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY - 1]);
		break;
	case up + down + left + right:
		rnd = RND->getInt(4);
		if (rnd == 0) _emptyTile = swapTile(tile, &_tile[tile->idX - 1][tile->idY]);
		else if (rnd == 1) _emptyTile = swapTile(tile, &_tile[tile->idX + 1][tile->idY]);
		else if (rnd == 2) _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY + 1]);
		else _emptyTile = swapTile(tile, &_tile[tile->idX][tile->idY - 1]);
		break;
	}

	//이동했으면 카운트 다운
	count--;

	//재귀로 돌림
	return shuffle(_emptyTile, count);
}

//타일의 위치를 바꾼다
tagTile* gameStudy::swapTile(tagTile* tile1, tagTile* tile2)
{
	//id는 건드리지 않고
	//타일번호와 그릴 위치를 바꿔줌
	int tileNumber;
	POINT ptDraw;

	tileNumber = tile1->tileNumber;
	tile1->tileNumber = tile2->tileNumber;
	tile2->tileNumber = tileNumber;

	ptDraw = tile1->ptDraw;
	tile1->ptDraw = tile2->ptDraw;
	tile2->ptDraw = ptDraw;

	//빈타일을 리턴
	return tile2;
}

//빈 타일을 다시 마지막 위치로 보냄
void gameStudy::retraceTile()
{
	while (true)
	{
		//다시 섞는다
		_emptyTile = shuffle(_emptyTile, *_shuffleCount);
		if (_emptyTile->idNumber == TILELASTNUM) break;
		//빈타일이 마지막 위치에 오면 빠져나옴
	}
}



float gameStudy::getDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	return sqrtf(x*x + y*y);
}

float gameStudy::getAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	float d = sqrtf(x*x + y*y);
	float angle = acosf(x / d);

	//acos(x) x는 -1 ~ 1의 값을 가진다 (라디안값)
	//cos의 역함수이며, 치역은 (0 ~ 180 degree)
	//180도가 넘어가면 181도가 아니라 179도가 된다.

	if (y > 0) angle = PI * 2 - angle;
	return angle;
}

//------------------------------------------