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
	// ������ �ʱ�ȭ ����
	const UINT MAX_LOADSTRING = 100;
	WCHAR szTitle[MAX_LOADSTRING];
	WCHAR szWindowClass[MAX_LOADSTRING];
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);

	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	hWnd = CreateWindow(	// ������ ���� �� �ڵ鰪 ��ȯ
		szWindowClass,		// ������ Ŭ���� �̸�
		szTitle,			// ������ Ÿ��Ʋ �̸�
		WINSTYLE,			// ������ ��Ÿ��
		(int)WINSTART.x,	// ������ ȭ�� X
		(int)WINSTART.y,	// ������ ȭ�� Y
		(int)WINSIZE.x,		// ������ ���� ũ��
		(int)WINSIZE.y,		// ������ ���� ũ��
		nullptr,			// �θ� ������
		nullptr,			// �޴� �ڵ�
		hInstance,			// �ν��Ͻ� ����
		nullptr				// �߰� �Ű�����
	);

	assert(hWnd != nullptr && "Create window failed");

	// ���� ������ ũ��(�׵θ�, �޴����� ũ�⸦ ������ ũ��)�� ���ϱ� ���� AdjustWindowRect ���
	RECT rc = { 0, 0, (LONG)WINSIZE.x, (LONG)WINSIZE.y };

	// ������ ��Ÿ�Ͽ� ���� ȭ�� �������� ũ�⿡ �°� ���´�.
	AdjustWindowRect(&rc, WINSTYLE, FALSE);
	// ������ ����� ����
	SetWindowPos(hWnd, HWND_TOPMOST, (int)WINSTART.x, (int)WINSTART.y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// ���ӿ��� �ʱ�ȭ
	SINGLE(CEngine)->Init(hInst, hWnd, WINSIZE);
	SINGLE(CTimeManager)->Init();
	SINGLE(CRenderManager)->Init();
	SINGLE(CInputManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CEventManager)->Init();
	SINGLE(CCollisionManager)->Init();
	SINGLE(CPathManager)->Init();
	SINGLE(CResourceManager)->Init();
	SINGLE(CCameraManager)->Init();
	SINGLE(CSoundManager)->Init();
	SINGLE(CUIManager)->Init();

	// TODO : ���ҽ� ��� ����
	SINGLE(CResourceManager)->SetResourceFolder(PATH + TEXT("\\..\\Resource\\"));

	// TODO : �� �߰�
	SINGLE(CSceneManager)->AddScene(SceneType::Title,	new CSceneTitle());
	SINGLE(CSceneManager)->AddScene(SceneType::Stage01,	new CSceneStage01());

	// TODO : �浹 ���̾� ����
	SINGLE(CCollisionManager)->CheckLayer(Layer::Player, Layer::Monster);
	SINGLE(CCollisionManager)->CheckLayer(Layer::Monster, Layer::Missile);

	// �� ����
	SINGLE(CSceneManager)->SetStartScene(SceneType::Title);
}

void CGame::Run()
{
	// ������ ���� ����

	Input();
	Update();
	Render();
}

void CGame::Release()
{
	// ������ ������ ����

	// ���ӿ��� ������
	SINGLE(CEngine)->Release();
	SINGLE(CTimeManager)->Release();
	SINGLE(CRenderManager)->Release();
	SINGLE(CInputManager)->Release();
	SINGLE(CSceneManager)->Release();
	SINGLE(CEventManager)->Release();
	SINGLE(CCollisionManager)->Release();
	SINGLE(CPathManager)->Release();
	SINGLE(CResourceManager)->Release();
	SINGLE(CCameraManager)->Release();
	SINGLE(CSoundManager)->Release();
	SINGLE(CUIManager)->Release();
}

void CGame::Input()
{
	// ������ �Է� ����
	SINGLE(CInputManager)->Update();
}

void CGame::Update()
{
	// ������ ó�� ����
	// ���� ����! : �̺�Ʈ �Ŵ����� ������Ʈ ���� �ʱ⿡ ����
	// ���� �����ӳ��� ��� ���� ������Ʈ�� ������ ��Ȳ�� �������� ó���ϱ� ����
	SINGLE(CEventManager)->Update();

	SINGLE(CTimeManager)->Update();
	SINGLE(CUIManager)->Update();
	SINGLE(CSceneManager)->Update();
	SINGLE(CCameraManager)->Update();
	SINGLE(CSoundManager)->Update();

	// ���� ����! : �浹 �Ŵ����� ������Ʈ ���� �������� ����
	// ������ ������ �����ġ�� �������� �浹������ �����ϱ� ����
	SINGLE(CCollisionManager)->Update();
}

void CGame::Render()
{
	SINGLE(CRenderManager)->BeginDraw();

	// ������ ǥ�� ����
	SINGLE(CSceneManager)->Render();
	SINGLE(CCameraManager)->Render();

	// ������ ���ܿ� ���� FPS ��� (60������ �̻��� ��ǥ�� ����ȭ �ؾ���)
	wstring frame = to_wstring(FPS);
	RENDER->SetText(20, RGB(0, 255, 0), TextAlign::Right);
	RENDER->Text(WINSIZE.x - 30, 10, frame);
	RENDER->SetText();

	SINGLE(CRenderManager)->EndDraw();
}
