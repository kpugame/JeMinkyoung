#pragma once

#include "gameNode.h"

//----------------------------------

#define PI 3.141592654f

#define TILEWIDTHNUM 3	// 0,1,2,3
#define TILEHEIGHTNUM 3
#define TILELASTNUM ((TILEWIDTHNUM * TILEHEIGHTNUM)- 1)
#define SHUFFLECOUNT 100

struct tagTile
{
	RECT rc;			//Ÿ��
	POINT ptDraw;	//�׸� �׸� ��ġ
	int idNumber;	//id(������ȣ! ������ id�� ������ ����)
	int tileNumber;	//Ÿ�Ϲ�ȣ
	int idX;			//x�� �ε���
	int idY;			//y�� �ε���
};


//----------------------------------

class gameStudy : public gameNode
{
	//--------------------------------------
private:

	image* _mapImage;
	image* _����;

	tagTile _tile[TILEWIDTHNUM][TILEHEIGHTNUM];
	tagTile* _emptyTile;

	int* _shuffleCount;
	//�Լ��� �Ѱ��ְ� �޾ƿ;� �ϹǷ� ������������ ����
	
	
	//-----------------------------------------

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	//-------------------------------------------

	
	//���� �Լ�
	tagTile* shuffle(tagTile* tile, int count);

	//Ÿ���� ��ġ�� �ٲ۴�
	tagTile* swapTile(tagTile* tile1, tagTile* tile2);

	//�� Ÿ���� �ٽ� ������ ��ġ�� ����
	void retraceTile();

	float getAngle(float x1, float y1, float x2, float y2);
	float getDistance(float x1, float y1, float x2, float y2);

	

	//--------------------------------------------

	gameStudy();
	virtual ~gameStudy();
};

