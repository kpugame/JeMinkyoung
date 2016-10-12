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
	RECT rc;			//타일
	POINT ptDraw;	//그림 그릴 위치
	int idNumber;	//id(고유번호! 섞여도 id는 변하지 않음)
	int tileNumber;	//타일번호
	int idX;			//x축 인덱스
	int idY;			//y축 인덱스
};


//----------------------------------

class gameStudy : public gameNode
{
	//--------------------------------------
private:

	image* _mapImage;
	image* _포로;

	tagTile _tile[TILEWIDTHNUM][TILEHEIGHTNUM];
	tagTile* _emptyTile;

	int* _shuffleCount;
	//함수에 넘겨주고 받아와야 하므로 포인터형으로 선언
	
	
	//-----------------------------------------

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	//-------------------------------------------

	
	//셔플 함수
	tagTile* shuffle(tagTile* tile, int count);

	//타일의 위치를 바꾼다
	tagTile* swapTile(tagTile* tile1, tagTile* tile2);

	//빈 타일을 다시 마지막 위치로 보냄
	void retraceTile();

	float getAngle(float x1, float y1, float x2, float y2);
	float getDistance(float x1, float y1, float x2, float y2);

	

	//--------------------------------------------

	gameStudy();
	virtual ~gameStudy();
};

