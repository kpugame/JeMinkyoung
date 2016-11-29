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

	_Coat[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 +
		(WINSIZEY / 4), WINSIZEX, WINSIZEY / 2);
	_Coat[1] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 -
		(WINSIZEY / 4), WINSIZEX, WINSIZEY / 2);

	_Goal[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 
		WINSIZEX / 3, 10);
	_Goal[1] = RectMakeCenter(WINSIZEX / 2, 0,
		WINSIZEX / 3, 10);

	_ball.speed = 0.0f;
	_ball.smash = false;
	_ball.radius = WINSIZEX / 26;
	_ball.x = WINSIZEX / 2;
	_ball.y = WINSIZEY / 2;
	_ball.rc = RectMakeCenter(_ball.x, _ball.y,
		_ball.radius * 2, _ball.radius * 2);

	_racket[0].radius = WINSIZEX / 15;
	_racket[0].x = WINSIZEX / 2;
	_racket[0].y = WINSIZEY / 2 + (WINSIZEY / 4);
	_racket[0].rc = RectMakeCenter(_racket[0].x, _racket[0].y,
		_racket[0].radius * 2, _racket[0].radius * 2);
	
	_racket[1].radius = WINSIZEX / 15;
	_racket[1].x = WINSIZEX / 2;
	_racket[1].y = WINSIZEY / 2 - (WINSIZEY / 4);
	_racket[1].rc = RectMakeCenter(_racket[1].x, _racket[1].y,
		_racket[1].radius * 2, _racket[1].radius * 2);

	//-------------------------------------

	return S_OK;
}

void gameStudy::release()
{
	gameNode::release();

	//해제---------------------------------



	//----------------------------------

}

void gameStudy::update()
{
	gameNode::update();

	//갱신-----------------------------------

	//1p키 셋업
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_racket[0].x += RACKET_SPEED;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_racket[0].x -= RACKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_racket[0].y -= RACKET_SPEED;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_racket[0].y += RACKET_SPEED;
	}

	//2p키 셋업
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_racket[1].x += RACKET_SPEED;
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		_racket[1].x -= RACKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_racket[1].y -= RACKET_SPEED;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		_racket[1].y += RACKET_SPEED;
	}

	//채를 코트에 가둠
	for (int i = 0; i < 2; ++i)
	{
		if (_racket[i].x - _racket[i].radius < 0)
		{
			_racket[i].x = _racket[i].radius;
		}
		else if (_racket[i].x + _racket[i].radius > WINSIZEX)
		{
			_racket[i].x = WINSIZEX - _racket[i].radius;
		}
		if (_racket[i].y - _racket[i].radius < _Coat[i].top)
		{
			_racket[i].y = _Coat[i].top + _racket[i].radius;
		}
		else if (_racket[i].y + _racket[i].radius > _Coat[i].bottom)
		{
			_racket[i].y = _Coat[i].bottom - _racket[i].radius;
		}

	}

	//채로 공을 치면
	smash();

	//공 이동
	ballMove();

	//골인 되면 점수를 카운트 하고 상태 초기화 한다.
	if (_Goal[0].top <= _ball.y + _ball.radius
		&& _Goal[0].left <= _ball.x 
		&& _Goal[0].right >= _ball.x)
	{
		_Score[1]++;
		_ball.smash = false;
		_ball.x = WINSIZEX / 2;
		_ball.y = WINSIZEY / 2;
		_ball.rc = RectMakeCenter(_ball.x, _ball.y,
			_ball.radius * 2, _ball.radius * 2);

		_racket[0].x = WINSIZEX / 2;
		_racket[0].y = WINSIZEY / 2 + (WINSIZEY / 4);
		_racket[0].rc = RectMakeCenter(_racket[0].x, _racket[0].y,
			_racket[0].radius * 2, _racket[0].radius * 2);

		_racket[1].x = WINSIZEX / 2;
		_racket[1].y = WINSIZEY / 2 - (WINSIZEY / 4);
		_racket[1].rc = RectMakeCenter(_racket[1].x, _racket[1].y,
			_racket[1].radius * 2, _racket[1].radius * 2);
		
	}

	if (_Goal[1].bottom >= _ball.y - _ball.radius
		&& _Goal[1].left <= _ball.x
		&& _Goal[1].right >= _ball.x)
	{
		_Score[0]++;
		_ball.smash = false;
		_ball.x = WINSIZEX / 2;
		_ball.y = WINSIZEY / 2;
		_ball.rc = RectMakeCenter(_ball.x, _ball.y,
			_ball.radius * 2, _ball.radius * 2);

		_racket[0].x = WINSIZEX / 2;
		_racket[0].y = WINSIZEY / 2 + (WINSIZEY / 4);
		_racket[0].rc = RectMakeCenter(_racket[0].x, _racket[0].y,
			_racket[0].radius * 2, _racket[0].radius * 2);

		_racket[1].x = WINSIZEX / 2;
		_racket[1].y = WINSIZEY / 2 - (WINSIZEY / 4);
		_racket[1].rc = RectMakeCenter(_racket[1].x, _racket[1].y,
			_racket[1].radius * 2, _racket[1].radius * 2);

	}
	



	//----------------------------------------
}

void gameStudy::render(HDC hdc)
{
	//그리기-----------------------------------------

	for (int i = 0; i < 2; ++i)
	{
		Rectangle(hdc, _Coat[i].left, _Coat[i].top,
			_Coat[i].right, _Coat[i].bottom);
		Rectangle(hdc, _Goal[i].left, _Goal[i].top,
			_Goal[i].right, _Goal[i].bottom);
		EllipseMakeCenter(hdc, _racket[i].x, _racket[i].y,
			_racket[i].radius * 2, _racket[i].radius * 2);
	}

	EllipseMakeCenter(hdc, _ball.x, _ball.y,
		_ball.radius * 2, _ball.radius * 2);

	sprintf_s(Score1, "1P 점수 : %d", _Score[0]);
	TextOut(hdc, 20, WINSIZEY - 40, Score1, strlen(Score1));
	
	sprintf_s(Score2, "2P 점수 : %d", _Score[1]);
	TextOut(hdc, 20, 20, Score2, strlen(Score2));

	//------------------------------------------
}


//추가되는 함수----------------------------------------

// 공을 채로 치면 함수
void gameStudy::smash(void)
{
	for (int i = 0; i < 2; i++)
	{
		float length = getDistance(_racket[i].x, _racket[i].y,
			_ball.x, _ball.y);
				

		if (_racket[i].radius + _ball.radius < length) continue;

		_ball.angle = getAngle(_racket[i].x, _racket[i].y, _ball.x, _ball.y); // 각도를 준다

		_ball.speed = 10; // 속도를 준다

		_ball.smash = true; // 공을 살린다
	}

}

void gameStudy::ballMove()
{
	if (_ball.smash) // 쳤으면
	{
		_ball.x += cosf(_ball.angle) * _ball.speed;
		_ball.y += -sinf(_ball.angle) * _ball.speed;

		_ball.rc = RectMakeCenter(_ball.x,
			_ball.y, _ball.radius * 2,
			_ball.radius * 2);

		_ball.speed -= 0.02; // 시간에 따른 감속

		// 벽에 충돌시
		//왼쪽
		if (_ball.x - _ball.radius < 0)
		{
			_ball.x = _ball.radius;
			_ball.angle = PI - _ball.angle;
		}
		//오른쪽
		else if (_ball.x + _ball.radius > WINSIZEX)
		{
			_ball.x = WINSIZEX - _ball.radius;
			_ball.angle = PI - _ball.angle;
		}
		//위
		else if (_ball.y - _ball.radius < 0)
		{
			_ball.y = _ball.radius;
			_ball.angle = 2 * PI - _ball.angle;
		}
		//아래
		else if (_ball.y + _ball.radius > WINSIZEY)
		{
			_ball.y = WINSIZEY - _ball.radius;
			_ball.angle = 2 * PI - _ball.angle;
		}

		if (_ball.speed <= 0) _ball.smash = false; // 공이 정지하면 죽인다
	}
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

float gameStudy::getDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	return sqrtf(x*x + y*y);
}

//------------------------------------------