#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; ++i)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}

	return S_OK;
}

void keyManager::release()
{

}

//0x0000 : ������ ���� ���� ���� ȣ�� ������ �� ���� ����
//0x8000 : ������ ���� ���� ���� ȣ�� ������ ���� ����
//0x8001 : ������ ���� ���� �ְ� ȣ�� ������ ���� ����
//0x0001 : ������ ���� ���� �ְ� ȣ�� ������ �� ���� ����

//Ű�� �ѹ��� ���ȴ��� �˻�
bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);
	return false;
}

//Ű�� �����ٰ� ������ �˻�
bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUP()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}
	return false;
	
}

//Ű�� ������ ���� �� ��� �˻�
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) && 0x8000) return true;
	return false;
}

//�����ٰ� ���� true, �ٽ� �����ٰ� ���� false
//���� �ݺ�
bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
