// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h> //���Ĵٵ� ����� ��� ��Ŭ���(printf, scanf, puts, gets���)
#include <tchar.h> //�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ��� (TextOut, DrawText, wsprintf���)
				//�⺻������ �����ڵ��� 
				//MBCS(Multi Byte Chracter Set) -> ������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ�..
				//WBCS(Wide Byte Chracter Set) -> ��� ���ڸ� 2����Ʈ�� ó����. �����ڵ� ���

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <windef.h>
#include <iostream>
#include <vector>
using namespace std;


#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"



//������ ũ�� �� ��Ÿ�� ����
#define WINNAME (LPTSTR)(TEXT("winAPI"))
#define WINSTARTX 100
#define WINSTARTY 10
#define WINSIZEX 400
#define WINSIZEY 700
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()


//�����ϰ� �����Ѵ� (Macro Function)
#define SAFE_DELETE(p) {if(p) {delete (p); (p)= NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL}};
#define SAFE_RELEASE (p) {if(p) {(p)->release(); (p)= NULL}};

extern HINSTANCE _hInstance; //���α׷� �ν��Ͻ�
extern HWND _hWnd;		   //������ �ڵ�
extern POINT _ptMouse;		//���콺 ����Ʈ