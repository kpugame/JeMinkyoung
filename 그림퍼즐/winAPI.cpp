// winAPI.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//



#include "stdafx.h"
#include "winAPI.h"
#include "gameStudy.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE _hInstance;							// ���� �ν��Ͻ��Դϴ�.
HWND _hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.

POINT _ptMouse = { 0, 0 };
gameStudy _gs;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));


	// �⺻ �޽��� �����Դϴ�.

	////���ӿ�
	//while (true)
	//{
	//	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	//	{
	//		if (message.message == WM_QUIT) break;
	//		TranslateMessage(&message);
	//		DispatchMessage(&message);
	//	}
	//	//render()
	//}

	//���ӽ��͵� �ʱ�ȭ
	if (FAILED(_gs.init()))
	{
		//�����ϸ� �ٷ� ����
		return 0;
	}

	//�Ϲ� ���α׷���
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��
	wcex.lpfnWndProc	= WndProc;											//���ν��� ��(�޽��� ó���Լ�)
	wcex.cbClsExtra		= 0;												//Ŭ���� ������ �޸�
	wcex.cbWndExtra		= 0;												//������ ������ �޸�
	wcex.hInstance		= hInstance;										//������ �ν��Ͻ�
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI)); //������
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);							//Ŀ��
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);						//��׶���
	wcex.lpszMenuName = NULL;							//Ŭ���� �޴�
	wcex.lpszClassName	= WINNAME;									//Ŭ���� �̸�
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); 

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   _hInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   _hWnd = CreateWindow(
	   WINNAME				//������ Ŭ���� �̸�
	   , WINNAME			//������ Ÿ��Ʋ �ٿ� ��Ÿ�� �̸�
	   , WINSTYLE			//������ ��Ÿ��
	   , WINSTARTX			//������ ȭ�� ��ǥ x
	   , WINSTARTY			//������ ȭ�� ��ǥ y
	   , WINSIZEX			//������ ȭ�� width
	   , WINSIZEY			//������ ȭ�� height
	   , NULL				//�θ�������
	   , NULL				//�޴� �ڵ�
	   , hInstance			//�ν��Ͻ� ������ ����
	   , NULL				//mdiŬ���̾�Ʈ ������ ��
	   //�ڽ� �����츦 �����ϸ� ������ �ֵ� �������
	   //���� ��쿡�� NULL ����
	   );

   if (!_hWnd)
   {
      return FALSE;
   }

   setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

   //ȭ�鿡 ������ �����ش�
   ShowWindow(_hWnd, nCmdShow);
   //UpdateWindow(_hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
//hWnd : ��� �����쿡�� �߻��� �޽������� �����Ѵ�
//message : �޽��� ���� ��ȣ
//wParam : unsigned int�� ���콺 ��ư ����, Ű����Ű �Ǵ� ����Ű ���¸� �����Ѵ�
//lParam : ���콺 Ŭ�� ��ǥ ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	return _gs.MainProc(hWnd, message, wParam, lParam);
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}

