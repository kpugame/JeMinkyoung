#pragma once

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스로부터 이미지 로딩
		LOAD_FILE,			//파일로부터 이미지 로딩
		LOAD_EMPTY,			//아무것도 없는 이미지 생성
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		int			width;
		int			height;
		BYTE			loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO _imageInfo; //이미지 정보
	CHAR*		_fileName;	//이미지 파일 경로 명

	BOOL			_trans;		//투명 배경 있냐?
	COLORREF		_transColor;	//투명 컬러키

public:
	//빈 비트맵을 만든다
	HRESULT init(int width, int height);

	//파일로부터 이미지를 읽어온다
	HRESULT init(const char* fileName, int width,
		int height, BOOL trans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//삭제한다
	void release();

	//투명키 셋팅한다
	void setTransColor(BOOL trans, COLORREF transColor);

	//렌더링
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY,
		int sourX, int sourY, int width, int height);

	//메모리 DC얻어온다
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//가로해상도
	inline int getWidth() { return _imageInfo->width; }

	//세로 해상도
	inline int getHeight() { return _imageInfo->height; }

	image();
	~image();
};

