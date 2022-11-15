#include "pch.h"
#include "CGame.h"

#include "Resource.h"

#include "CSceneTitle.h"
#include "CSceneStage01.h"

const Vec2 CGame::WINSTART	= Vec2(100, 100);
const Vec2 CGame::WINSIZE	= Vec2(1280, 720);

CGame::CGame()
{
	hInst	= 0;
	hWnd	= 0;
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
	SINGLE(CInputManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CEventManager)->Init();
	SINGLE(CCollisionManager)->Init();

	// TODO : 씬 추가
	SINGLE(CSceneManager)->AddScene(SceneType::Title,	new CSceneTitle());
	SINGLE(CSceneManager)->AddScene(SceneType::Stage01,	new CSceneStage01());

	// 씬 시작
	SINGLE(CSceneManager)->SetStartScene(SceneType::Title);
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
	SINGLE(CInputManager)->Release();
	SINGLE(CSceneManager)->Release();
	SINGLE(CEventManager)->Release();
	SINGLE(CCollisionManager)->Release();
}

void CGame::Input()
{
	// 게임의 입력 진행
	SINGLE(CInputManager)->Update();
}

void CGame::Update()
{
	// 게임의 처리 진행
	// 순서 주의! : 이벤트 매니저는 업데이트 가장 초기에 진행
	// 같은 프레임내에 모든 게임 오브젝트가 동일한 상황을 기준으로 처리하기 위해
	SINGLE(CEventManager)->Update();

	SINGLE(CTimeManager)->Update();
	SINGLE(CSceneManager)->Update();

	// 순서 주의! : 충돌 매니저는 업데이트 가장 마지막에 진행
	// 씬에서 움직인 결과위치를 기준으로 충돌판정을 진행하기 위해
	SINGLE(CCollisionManager)->Update();
}

void CGame::Render()
{
	SINGLE(CRenderManager)->BeginDraw();

	// 게임의 표현 진행
	SINGLE(CSceneManager)->Render();

	// 게임의 우상단에 게임 FPS 출력 (60프레임 이상을 목표로 최적화 해야함)
	wstring frame = to_wstring(FPS);
	RENDER->SetText(20, RGB(0, 255, 0), TextAlign::Right);
	RENDER->Text(WINSIZE.x - 30, 10, frame);
	RENDER->SetText();

	SINGLE(CRenderManager)->EndDraw();
}
