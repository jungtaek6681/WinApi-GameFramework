#include "pch.h"
#include "CGame.h"

#include "Resource.h"

const Vec2 CGame::WINSTART	= Vec2(100, 100);
const Vec2 CGame::WINSIZE	= Vec2(1280, 720);

CGame::CGame()
{
	hInst	= 0;
	hWnd	= 0;

	moveDir	= Vec2(0.f, 0.f);
	pos		= Vec2(WINSIZE.x * 0.5f, WINSIZE.y * 0.5f);
	scale	= Vec2(100.f, 100.f);
}

CGame::~CGame()
{
}

void CGame::Init(HINSTANCE hInstance)
{
	// 게임의 초기화 진행
	const UINT MAX_LOADSTRING = 100;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	hWnd = CreateWindow(	// 윈도우 생성 및 핸들값 반환
		szWindowClass,		// 윈도우 클래스 이름
		szTitle,			// 윈도우 타이틀 이름
		WINSTYLE,			// 윈도우 스타일
		(int)WINSTART.x,	// 윈도우 화면 X
		(int)WINSTART.y,	// 윈도우 화면 Y
		(int)WINSIZE.x,		// 윈도우 가로 크기
		(int)WINSIZE.y,		// 윈도우 세로 크기
		nullptr,			// 부모 윈도우
		nullptr,			// 메뉴 핸들
		hInstance,			// 인스턴스 지정
		nullptr				// 추가 매개변수
	);

	assert(hWnd != nullptr && "Create window failed");

	// 게임 윈도우 크기(테두리, 메뉴바의 크기를 제외한 크기)를 구하기 위해 AdjustWindowRect 사용
	RECT rc = { 0, 0, (LONG)WINSIZE.x, (LONG)WINSIZE.y };

	// 윈도우 스타일에 따라 화면 컨텐츠의 크기에 맞게 나온다.
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	// 윈도우 사이즈를 설정
	SetWindowPos(hWnd, HWND_TOPMOST, (int)WINSTART.x, (int)WINSTART.y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// 게임엔진 초기화
	SINGLE(CEngine)->Init(hInst, hWnd, WINSIZE);
	SINGLE(CTimeManager)->Init();
	SINGLE(CRenderManager)->Init();
}

void CGame::Run()
{
	// 게임의 동작 진행

	Input();
	Update();
	Render();
}

void CGame::Release()
{
	// 게임의 마무리 진행

	// 게임엔진 마무리
	SINGLE(CEngine)->Release();
	SINGLE(CTimeManager)->Release();
	SINGLE(CRenderManager)->Release();
}

void CGame::Input()
{
	// 게임의 입력 진행

	// GetAsyncKeyState : 키보드의 키 입력상태 확인
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		moveDir.x = -1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		moveDir.x = +1;
	}
	else
	{
		moveDir.x = 0;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		moveDir.y = -1;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		moveDir.y = +1;
	}
	else
	{
		moveDir.y = 0;
	}
}

void CGame::Update()
{
	// 게임의 처리 진행

	SINGLE(CTimeManager)->Update();

	pos += moveDir * 100 * DT;
}

void CGame::Render()
{
	SINGLE(CRenderManager)->BeginDraw();

	// 게임의 표현 진행

	RENDER->SetPen(PenType::Solid, RGB(255, 0, 0), 1);
	RENDER->SetBrush(BrushType::Solid, RGB(0, 255, 0));
	RENDER->Rect(
		pos.x - scale.x * 0.5f,
		pos.y - scale.y * 0.5f,
		pos.x + scale.x * 0.5f,
		pos.y + scale.y * 0.5f
	);
	RENDER->SetPen();
	RENDER->SetBrush();

	// 게임의 우상단에 게임 FPS 출력 (60프레임 이상을 목표로 최적화 해야함)
	wstring frame = to_wstring(FPS);
	RENDER->SetText(20, RGB(0, 255, 0), TextAlign::Right);
	RENDER->Text(WINSIZE.x - 30, 10, frame);
	RENDER->SetText();

	SINGLE(CRenderManager)->EndDraw();
}
