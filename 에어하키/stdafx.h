// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h> //스탠다드 입출력 헤더 인클루드(printf, scanf, puts, gets등등)
#include <tchar.h> //윈도우에서 사용할 문자열 출력 헤더 인클루드 (TextOut, DrawText, wsprintf등등)
				//기본적으로 유니코드임 
				//MBCS(Multi Byte Chracter Set) -> 기존에 사용하던 멀티바이트 형태의 문자열..
				//WBCS(Wide Byte Chracter Set) -> 모든 문자를 2바이트로 처리함. 유니코드 기반

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <windef.h>
#include <iostream>
#include <vector>
using namespace std;


#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"



//윈도우 크기 및 스타일 설정
#define WINNAME (LPTSTR)(TEXT("winAPI"))
#define WINSTARTX 100
#define WINSTARTY 10
#define WINSIZEX 400
#define WINSIZEY 700
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()


//안전하게 삭제한다 (Macro Function)
#define SAFE_DELETE(p) {if(p) {delete (p); (p)= NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL}};
#define SAFE_RELEASE (p) {if(p) {(p)->release(); (p)= NULL}};

extern HINSTANCE _hInstance; //프로그램 인스턴스
extern HWND _hWnd;		   //윈도우 핸들
extern POINT _ptMouse;		//마우스 포인트