#include "pch.h"
#include "CCameraController.h"

CCameraController::CCameraController()
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Init()
{
}

void CCameraController::OnEnable()
{
}

void CCameraController::Update()
{
	if (INPUT->ButtonDown(VK_LBUTTON))
	{
		CAMERA->SetLookAt(INPUT->MouseWorldPos());
	}
}

void CCameraController::Render()
{
}

void CCameraController::OnDisable()
{
}

void CCameraController::Release()
{
}
