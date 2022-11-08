// WinApi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WinApi.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE	hInst;							// 현재 인스턴스입니다.
WCHAR		szTitle[MAX_LOADSTRING];		// 제목 표시줄 텍스트입니다.
WCHAR		szWindowClass[MAX_LOADSTRING];	// 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/// <summary>
/// 윈도우 프로그램의 메인 함수
/// 1. 윈도우창의 설정 후 화면에 띄움
/// 2. 메세지 루프를 프로그램 종료까지 계속 반복
/// </summary>
/// <param name="hInstance"> 실행된 프로세스의 시작 주소. 인스턴스 핸들 </param>
/// <param name="hPrevInstance"> 이전에 실행된 인스턴스 핸들 </param>
/// <param name="lpCmdLine"> 명령으로 입력된 프로그램의 인수 </param>
/// <param name="nCmdShow"> 프로그램이 시작될 형태 </param>
/// <returns> 어플리케이션이 초기화 불가할 때 False, 메세지 루프에서 종료를 입력받았을 때 메세지의 wParam </returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 사용하지 않은 매개변수 정의
	// 불필요한 매개변수이지만 구버전 윈도우를 지원하기 위해 그대로 둠
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 리소스 뷰의 String table 정보
	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 리소스 뷰의 단축키 정보
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

	MSG msg;

	// 기본 메시지 루프입니다:
	// 메세지 큐에서 메세지가 확인될 때까지 대기
	// 메세지 큐에 msg.mssage == WM_QUIT 인 경우 false를 반환
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))	// 단축키 처리
		{
			TranslateMessage(&msg);	// 키보드 입력메세지 처리를 담당
			DispatchMessage(&msg);	// WndProc에서 전달된 메세지를 실제 윈도우에 전달
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// 윈도우 창의 정보를 저장하기 위한 구조체
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);	// 구조체의 크기 설정

	wcex.style = CS_HREDRAW | CS_VREDRAW;							// 윈도우 클래스의 스타일 지정
	wcex.lpfnWndProc = WndProc;										// 메세지를 처리하는 함수를 지정(윈도우 프로시져)
	wcex.cbClsExtra = 0;											// 윈도우 클래스에서 사용하고자 하는 여분의 메모리양을 바이트 단위로 지정
	wcex.cbWndExtra = 0;											// cbClsExtra와 유사하나 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
	wcex.hInstance = hInstance;										// 윈도우 클래스를 등록한 인스턴스의 핸들
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));	// 프로그램 아이콘
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));	// 프로그램 작은사이즈 아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);					// 커서 지정
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);				// 윈도우 작업영역에 칠한 배경 브러시
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI);				// 윈도우에서 사용할 메뉴 지정. nullptr로 없앰
	wcex.lpszClassName = szWindowClass;								// 윈도우 클래스의 이름

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindow(	// 윈도우 생성 및 핸들값 반환
		szWindowClass,			// 윈도우 클래스 이름
		szTitle,				// 윈도우 타이틀 이름
		WS_OVERLAPPEDWINDOW,	// 윈도우 스타일
		CW_USEDEFAULT,			// 윈도우 화면 X
		0,						// 윈도우 화면 Y
		CW_USEDEFAULT,			// 윈도우 가로 크기
		0,						// 윈도우 세로 크기
		nullptr,				// 부모 윈도우
		nullptr,				// 메뉴 핸들
		hInstance,				// 인스턴스 지정
		nullptr					// 추가 매개변수
	);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

/// <summary>
/// 메세지를 운영체제에 전달
/// 강제로 운영체제가 호출함
/// </summary>
/// <param name="hWnd"> 메세지가 어느 윈도우를 대상으로 전달되었는지 구분 </param>
/// <param name="message"> 메세지 구분 번호 </param>
/// <param name="wParam"> 메세지의 매개변수 1 </param>
/// <param name="lParam"> 메세지의 매개변수 2 </param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:	// 윈도우 명령용 메세지
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	// 윈도우의 화면 출력용 메세지
	// 윈도우의 작업영역이 다시 그려져야 할때 실행됨
	// -> 무효화 영역이 발생 했을 때
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	// 윈도우가 종료될 때 실행됨
	// -> 메세지 큐에 WM_QUIT 입력
	// -> 메세지 루프의 GetMessage에서 false를 반환하여 프로그램 종료
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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
