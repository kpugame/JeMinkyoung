#include "stdafx.h"
#include "image.h"


image::image()
	:_imageInfo(NULL)
	, _fileName(NULL)
	, _trans(FALSE)
	, _transColor(RGB(0,0,0))
{

}


image::~image()
{
}

//빈 비트맵을 만든다
HRESULT image::init(int width, int height)
{
	//재 초기화 대비...
	if (_imageInfo != NULL) release();

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어 준다

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY; //로드타입 (빈 이미지)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//얻어온 DC해제한다.
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 이미지를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//파일로부터 이미지를 읽어온다
HRESULT image::init(const char* fileName, int width,
	int height, BOOL trans, COLORREF transColor)
{
	//파일 경로가 잘못 되었으면
	if (fileName == NULL) return E_FAIL;

	//재 초기화 대비...
	if (_imageInfo != NULL) release();

	//CreateCompatibleDC
	//비트맵 이미지를 출력하기 위해서 메모리 DC를 만들어 준다

	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵 생성해준다

	//DC얻어온다
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //로드타입 (파일로부터)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance,
		fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일 경로 이름 복사한다.
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	

	//얻어온 DC해제한다.
	ReleaseDC(_hWnd, hdc);

	//투명컬러 셋팅한다
	_trans = trans;
	_transColor = transColor;

	//리소스 이미지를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//삭제한다
void image::release()
{
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//투명 컬러값 초기화
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//투명키 셋팅한다
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//렌더링
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			_imageInfo->width,	//복사될 좌표 width
			_imageInfo->height,	//복사될 좌표 height
			_imageInfo->hMemDC,	//복사대상의 DC
			0,					//복사 시작지점 X
			0,					//복사 시작지점 Y
			_imageInfo->width,	//복사될 영역의 widht
			_imageInfo->height,	//복사될 역역의 height
			_transColor);		//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY,
	int sourX, int sourY, int width, int height)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//복사할 장소의 DC
			destX,				//복사될 좌표 시작점 X
			destY,				//복사될 좌표 시작점 Y
			width,	//복사될 좌표 width
			height,	//복사될 좌표 height
			_imageInfo->hMemDC,	//복사대상의 DC
			sourX,					//복사 시작지점 X
			sourY,					//복사 시작지점 Y
			width,	//복사될 영역의 widht
			height,	//복사될 역역의 height
			_transColor);		//복사에서 제외 될 색상 값
	}
	else
	{
		//BitBlt는 DC간의 영역끼리 서로 고속복사를
		//해 주는 함수이다.
		//(CreateCompatibleDC함수로 만든 메모리 DC에 있는
		//비트맵을 화면 DC로 복사해줄때 사용.....)
		//같은 기능으로 StrechBlt가 있는데 이 함수는 
		//비트맵의 확대 및 축소가 가능하다.
		BitBlt(hdc, destX, destY, width,
			height, _imageInfo->hMemDC,
			sourX, sourY, SRCCOPY);
	}
}
