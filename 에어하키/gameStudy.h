#pragma once

#include "gameNode.h"

//----------------------------------

#define PI 3.141592654f
#define RACKET_SPEED 5


struct tagBall
{
	RECT rc;
	float x, y; //중점
	float angle; //각도
	float speed; //이동속도
	float radius; //반지름
	bool smash; //쳤냐?

};


struct tagRacket
{
	RECT rc;
	float x, y;
	float radius;
	float angle; //라디안 값임
};

//----------------------------------

class gameStudy : public gameNode
{
	//--------------------------------------
private:

	tagBall _ball;
	tagRacket _racket[2];
	RECT _Coat[2];
	RECT _Goal[2];
	int _Score[2];
	char Score1[64];
	char Score2[64];
	
	//-----------------------------------------

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	//-------------------------------------------

	void ballMove();
	void smash();

	float getAngle(float x1, float y1, float x2, float y2);
	float getDistance(float x1, float y1, float x2, float y2);

	
	//--------------------------------------------

	gameStudy();
	virtual ~gameStudy();
};

