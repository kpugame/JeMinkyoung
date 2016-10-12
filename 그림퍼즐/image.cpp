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

//�� ��Ʈ���� �����
HRESULT image::init(int width, int height)
{
	//�� �ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY; //�ε�Ÿ�� (�� �̹���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	//���� DC�����Ѵ�.
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//���Ϸκ��� �̹����� �о�´�
HRESULT image::init(const char* fileName, int width,
	int height, BOOL trans, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ�����
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ ���...
	if (_imageInfo != NULL) release();

	//CreateCompatibleDC
	//��Ʈ�� �̹����� ����ϱ� ���ؼ� �޸� DC�� ����� �ش�

	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ�� �������ش�

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; //�ε�Ÿ�� (���Ϸκ���)
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance,
		fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� ��� �̸� �����Ѵ�.
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);
	

	//���� DC�����Ѵ�.
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_trans = trans;
	_transColor = transColor;

	//���ҽ� �̹����� ��µ� �����ϸ�
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�����Ѵ�
void image::release()
{
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//���� �÷��� �ʱ�ȭ
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

//����Ű �����Ѵ�
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

//������
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			_imageInfo->width,	//����� ��ǥ width
			_imageInfo->height,	//����� ��ǥ height
			_imageInfo->hMemDC,	//�������� DC
			0,					//���� �������� X
			0,					//���� �������� Y
			_imageInfo->width,	//����� ������ widht
			_imageInfo->height,	//����� ������ height
			_transColor);		//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
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
			hdc,				//������ ����� DC
			destX,				//����� ��ǥ ������ X
			destY,				//����� ��ǥ ������ Y
			width,	//����� ��ǥ width
			height,	//����� ��ǥ height
			_imageInfo->hMemDC,	//�������� DC
			sourX,					//���� �������� X
			sourY,					//���� �������� Y
			width,	//����� ������ widht
			height,	//����� ������ height
			_transColor);		//���翡�� ���� �� ���� ��
	}
	else
	{
		//BitBlt�� DC���� �������� ���� ��Ӻ��縦
		//�� �ִ� �Լ��̴�.
		//(CreateCompatibleDC�Լ��� ���� �޸� DC�� �ִ�
		//��Ʈ���� ȭ�� DC�� �������ٶ� ���.....)
		//���� ������� StrechBlt�� �ִµ� �� �Լ��� 
		//��Ʈ���� Ȯ�� �� ��Ұ� �����ϴ�.
		BitBlt(hdc, destX, destY, width,
			height, _imageInfo->hMemDC,
			sourX, sourY, SRCCOPY);
	}
}
