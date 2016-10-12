#pragma once

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ��κ��� �̹��� �ε�
		LOAD_FILE,			//���Ϸκ��� �̹��� �ε�
		LOAD_EMPTY,			//�ƹ��͵� ���� �̹��� ����
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
	LPIMAGE_INFO _imageInfo; //�̹��� ����
	CHAR*		_fileName;	//�̹��� ���� ��� ��

	BOOL			_trans;		//���� ��� �ֳ�?
	COLORREF		_transColor;	//���� �÷�Ű

public:
	//�� ��Ʈ���� �����
	HRESULT init(int width, int height);

	//���Ϸκ��� �̹����� �о�´�
	HRESULT init(const char* fileName, int width,
		int height, BOOL trans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	//�����Ѵ�
	void release();

	//����Ű �����Ѵ�
	void setTransColor(BOOL trans, COLORREF transColor);

	//������
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY,
		int sourX, int sourY, int width, int height);

	//�޸� DC���´�
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//�����ػ�
	inline int getWidth() { return _imageInfo->width; }

	//���� �ػ�
	inline int getHeight() { return _imageInfo->height; }

	image();
	~image();
};

