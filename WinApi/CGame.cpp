#include "pch.h"
#include "CGame.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

void CGame::Init()
{
	// 게임의 초기화 진행
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
}

void CGame::Input()
{
	// 게임의 입력 진행
}

void CGame::Update()
{
	// 게임의 처리 진행
}

void CGame::Render()
{
	// 게임의 표현 진행
}
