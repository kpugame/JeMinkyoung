#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//Ÿ�̸� ����
	SetTimer(_hWnd, 0, 10, NULL);

	//Ű�Ŵ��� �ʱ�ȭ
	KEYMANAGER->init();

	//����� ����
	setBackBuffer();

	return S_OK;
}

void gameNode::release()
{
	_backBuffer->release();
	SAFE_DELETE(_backBuffer);

	//Ÿ�̸� ����
	KillTimer(_hWnd, 0);

	//Ű�Ŵ��� ����
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
}
void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}
void gameNode::render(HDC hdc)
{

}

void gameNode::setBackBuffer()
{
	_backBuffer = new image;
	_backBuffer->init(WINSIZEX, WINSIZEY);
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	

	switch (iMessage)
	{
	case WM_TIMER:
	{
		this->update();
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(_hWnd, &ps);
		this->render(hdc);
		EndPaint(_hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		
		break;
	case WM_RBUTTONDOWN:
		
		break;
	case WM_LBUTTONUP:

		break;
	case WM_MOUSEMOVE:
	{
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));
		

	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		

		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		//InvalidateRect(hWnd, NULL, true);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
		//������ ���ν������� ó������ ���� ������ �޽����� ó���Ѵ�.
		
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
