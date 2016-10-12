// winAPI.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//



#include "stdafx.h"
#include "winAPI.h"
#include "gameStudy.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE _hInstance;							// 현재 인스턴스입니다.
HWND _hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

POINT _ptMouse = { 0, 0 };
gameStudy _gs;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));


	// 기본 메시지 루프입니다.

	////게임용
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

	//게임스터디를 초기화
	if (FAILED(_gs.init()))
	{
		//실패하면 바로 종료
		return 0;
	}

	//일반 프로그램용
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일
	wcex.lpfnWndProc	= WndProc;											//프로시져 함(메시지 처리함수)
	wcex.cbClsExtra		= 0;												//클래스 여분의 메모리
	wcex.cbWndExtra		= 0;												//윈도우 여분의 메모리
	wcex.hInstance		= hInstance;										//윈도우 인스턴스
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI)); //아이콘
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);							//커서
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);						//백그라운드
	wcex.lpszMenuName = NULL;							//클래스 메뉴
	wcex.lpszClassName	= WINNAME;									//클래스 이름
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); 

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   _hInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   _hWnd = CreateWindow(
	   WINNAME				//윈도우 클래스 이름
	   , WINNAME			//윈도우 타이틀 바에 나타날 이름
	   , WINSTYLE			//윈도우 스타일
	   , WINSTARTX			//윈도우 화면 좌표 x
	   , WINSTARTY			//윈도우 화면 좌표 y
	   , WINSIZEX			//윈도우 화면 width
	   , WINSIZEY			//윈도우 화면 height
	   , NULL				//부모윈도우
	   , NULL				//메뉴 핸들
	   , hInstance			//인스턴스 윈도우 지정
	   , NULL				//mdi클라이언트 윈도우 및
	   //자식 윈도우를 생성하면 지정해 주되 사용하지
	   //않을 경우에는 NULL 설정
	   );

   if (!_hWnd)
   {
      return FALSE;
   }

   setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

   //화면에 윈도우 보여준다
   ShowWindow(_hWnd, nCmdShow);
   //UpdateWindow(_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
//hWnd : 어느 윈도우에서 발생한 메시지인지 구분한다
//message : 메시지 구분 번호
//wParam : unsigned int형 마우스 버튼 상태, 키보드키 또는 조합키 상태를 전달한다
//lParam : 마우스 클릭 좌표 전달

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	return _gs.MainProc(hWnd, message, wParam, lParam);
}

// 정보 대화 상자의 메시지 처리기입니다.
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

