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
		CAMERA->SetTargetPos(INPUT->MouseWorldPos(), 1);
	}

	Vec2 dir;
	if (INPUT->ButtonStay('A'))
		dir.x = -1;
	else if (INPUT->ButtonStay('D'))
		dir.x = 1;
	else
		dir.x = 0;

	if (INPUT->ButtonStay('W'))
		dir.y = -1;
	else if (INPUT->ButtonStay('S'))
		dir.y = 1;
	else
		dir.y = 0;

	CAMERA->Scroll(dir, 200);
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
