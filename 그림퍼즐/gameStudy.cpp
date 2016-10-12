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

	//�ʱ�ȭ------------------------------------

	_mapImage = new image;
	_mapImage->init("mapImage.bmp", 700, 700);

	//����
	_���� = new image;
	_����->init("����.bmp", 600, 600);

	//���� �¾�
	int tileWidth = _����->getWidth() / TILEWIDTHNUM;	// ������ ũ�⸦ Ÿ�� ������ ������.
	int tileHeight = _����->getHeight() / TILEHEIGHTNUM;


	for (int y = 0; y < TILEHEIGHTNUM; ++y)	// Ÿ�� ��
	{
		for (int x = 0; x < TILEWIDTHNUM; ++x)
		{
			_tile[x][y].rc = RectMake(x * tileWidth, y*tileHeight, tileWidth, tileHeight);	// x�� y������ŭ
			_tile[x][y].idNumber = _tile[x][y].tileNumber = x + (y * TILEWIDTHNUM);
			_tile[x][y].ptDraw = PointMake(_tile[x][y].rc.left, _tile[x][y].rc.top);
			_tile[x][y].idX = x;
			_tile[x][y].idY = y;
			//x�� �ε����� y�� �ε��� ����
			//�� Ÿ�ϸ��� �ٸ� ���̵� ��ȣ�� �ְ�
			//�׸� �׸� ��ġ�� �����
		}
	}

	//���� ī��Ʈ ����
	int count = SHUFFLECOUNT;
	_shuffleCount = &count;

	//������ �� Ÿ�� ������ �־��ش�
	_emptyTile = &_tile[TILEWIDTHNUM - 1][TILEHEIGHTNUM - 1];

	//���´�
	shuffle(_emptyTile, *_shuffleCount);

	//�� Ÿ���� ������~
	retraceTile();


	//-------------------------------------

	return S_OK;
}

void gameStudy::release()
{
	gameNode::release();

	//����---------------------------------

	_mapImage->release();
	SAFE_DELETE(_mapImage);

	_����->release();
	SAFE_DELETE(_����);

	//----------------------------------

}

void gameStudy::update()
{
	gameNode::update();



	//����-----------------------------------

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int y = 0; y < TILEHEIGHTNUM; ++y)
		{
			for (int x = 0; x < TILEWIDTHNUM; ++x)
			{
				if (PtInRect(&_tile[x][y].rc, _ptMouse))
				{
					//Ŭ���� Ÿ���� �� Ÿ���̸� ����
					//if (_tile[x][y].tileNumber == TILELASTNUM) return;

					//Ŭ���� Ÿ���� ���� ���̳� ���� ���� �ƴϸ� ����
					if (_emptyTile->idX != _tile[x][y].idX && _emptyTile->idY != _tile[x][y].idY) return;

					//Ŭ���� Ÿ�ϰ� �� Ÿ���� �Ÿ��� ���
					int rangeX = _emptyTile->idX - _tile[x][y].idX;
					int rangeY = _emptyTile->idY - _tile[x][y].idY;

					//���� �࿭�� �� ���� ����� ���
					//���밪���� �Ÿ���ū �ݺ��ؼ� �Ű���
					if (abs(rangeX) > 1)
					{
						//x�� ����
						for (int i = 0; i < abs(rangeX); ++i)
						{
							_emptyTile = swapTile(_emptyTile, &_tile[_emptyTile->idX + ((rangeX > 0) ? -1 : 1)][_emptyTile->idY]);
						}
					}
					else if (abs(rangeY) > 1)
					{
						//y�� ����
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

	//�׸���-----------------------------------------

	
	for (int y = 0; y < TILEHEIGHTNUM; ++y)
	{
		for (int x = 0; x < TILEWIDTHNUM; ++x)
		{
			if (&_tile[x][y] == _emptyTile) continue;
			_����->render(backDC, _tile[x][y].rc.left,
				_tile[x][y].rc.top, _tile[x][y].ptDraw.x,
				_tile[x][y].ptDraw.y,
				_tile[x][y].rc.right - _tile[x][y].rc.left,
				_tile[x][y].rc.bottom - _tile[x][y].rc.top);
		}
	}
	
	
	//------------------------------------------


	this->getBackBuffer()->render(hdc, 0, 0);
}


//�߰��Ǵ� �Լ�----------------------------------------

//���� �Լ�
tagTile* gameStudy::shuffle(tagTile* tile, int count)
{
	//������ ������ �� Ÿ�� ��ȯ
	if (count <= 0) return tile;

	//��Ʈ����
	const int up = 0x00000001;
	const int down = 0x00000002;
	const int left = 0x00000004;
	const int right = 0x00000008;

	int move = 0;

	//��Ÿ���� ��ġ�� �ľ��ؼ� �̵������� ������ �Ǻ�
	//��Ʈ�����̹Ƿ� �ߺ� ������ �����ϴ�
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

	//�̵������� ī��Ʈ �ٿ�
	count--;

	//��ͷ� ����
	return shuffle(_emptyTile, count);
}

//Ÿ���� ��ġ�� �ٲ۴�
tagTile* gameStudy::swapTile(tagTile* tile1, tagTile* tile2)
{
	//id�� �ǵ帮�� �ʰ�
	//Ÿ�Ϲ�ȣ�� �׸� ��ġ�� �ٲ���
	int tileNumber;
	POINT ptDraw;

	tileNumber = tile1->tileNumber;
	tile1->tileNumber = tile2->tileNumber;
	tile2->tileNumber = tileNumber;

	ptDraw = tile1->ptDraw;
	tile1->ptDraw = tile2->ptDraw;
	tile2->ptDraw = ptDraw;

	//��Ÿ���� ����
	return tile2;
}

//�� Ÿ���� �ٽ� ������ ��ġ�� ����
void gameStudy::retraceTile()
{
	while (true)
	{
		//�ٽ� ���´�
		_emptyTile = shuffle(_emptyTile, *_shuffleCount);
		if (_emptyTile->idNumber == TILELASTNUM) break;
		//��Ÿ���� ������ ��ġ�� ���� ��������
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

	//acos(x) x�� -1 ~ 1�� ���� ������ (���Ȱ�)
	//cos�� ���Լ��̸�, ġ���� (0 ~ 180 degree)
	//180���� �Ѿ�� 181���� �ƴ϶� 179���� �ȴ�.

	if (y > 0) angle = PI * 2 - angle;
	return angle;
}

//------------------------------------------