#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	name		= TEXT("플레이어");
	scale		= Vec2(100, 100);
	animator	= nullptr;
	speed		= 200.f;

	moveDir		= Vec2(0, 0);
	lookDir		= Vec2(0, -1);
	isMove		= false;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	CImage* idleImage = LOADIMAGE(TEXT("PlayerIdle"), TEXT("Image\\PlayerIdle.bmp"));
	CImage* moveImage = LOADIMAGE(TEXT("PlayerMove"), TEXT("Image\\PlayerMove.bmp"));

	animator = new CAnimator();

	animator->CreateAnimation(TEXT("IdleUp"),			idleImage, 0.1f, 7, true, Vec2(0.f,   0.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleRightUp"),		idleImage, 0.1f, 7, true, Vec2(0.f,  70.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleRight"),		idleImage, 0.1f, 7, true, Vec2(0.f, 140.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleRightDown"),	idleImage, 0.1f, 7, true, Vec2(0.f, 210.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleDown"),			idleImage, 0.1f, 7, true, Vec2(0.f, 280.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleLeftDown"),		idleImage, 0.1f, 7, true, Vec2(0.f, 350.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleLeft"),			idleImage, 0.1f, 7, true, Vec2(0.f, 420.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));
	animator->CreateAnimation(TEXT("IdleLeftUp"),		idleImage, 0.1f, 7, true, Vec2(0.f, 490.f), Vec2(80.f, 70.f), Vec2(80.f, 0.f));

	animator->CreateAnimation(TEXT("MoveUp"),			moveImage, 0.05f, 16, true, Vec2(0.f,   0.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveRightUp"),		moveImage, 0.05f, 16, true, Vec2(0.f,  79.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveRight"),		moveImage, 0.05f, 16, true, Vec2(0.f, 158.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveRightDown"),	moveImage, 0.05f, 16, true, Vec2(0.f, 237.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveDown"),			moveImage, 0.05f, 16, true, Vec2(0.f, 316.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveLeftDown"),		moveImage, 0.05f, 16, true, Vec2(0.f, 395.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveLeft"),			moveImage, 0.05f, 16, true, Vec2(0.f, 474.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));
	animator->CreateAnimation(TEXT("MoveLeftUp"),		moveImage, 0.05f, 16, true, Vec2(0.f, 553.f), Vec2(80.f, 75.f), Vec2(84.f, 0.f));

	AddChild(animator);
}

void CPlayer::OnEnable()
{
}

void CPlayer::Update()
{
	isMove = false;

	// 이동
	if (INPUT->ButtonStay(VK_LEFT))
	{
		pos.x -= speed * DT;
		isMove = true;
		moveDir.x = -1;
	}
	else if (INPUT->ButtonStay(VK_RIGHT))
	{
		pos.x += speed * DT;
		isMove = true;
		moveDir.x = +1;
	}
	else
	{
		moveDir.x = 0;
	}

	if (INPUT->ButtonStay(VK_UP))
	{
		pos.y -= speed * DT;
		isMove = true;
		moveDir.y = +1;
	}
	else if (INPUT->ButtonStay(VK_DOWN))
	{
		pos.y += speed * DT;
		isMove = true;
		moveDir.y = -1;
	}
	else
	{
		moveDir.y = 0;
	}

	AnimatorUpdate();
}

void CPlayer::Render()
{
}

void CPlayer::OnDisable()
{
}

void CPlayer::Release()
{
}

void CPlayer::AnimatorUpdate()
{
	if (moveDir.Length() > 0)
		lookDir = moveDir;

	wstring str = TEXT("");

	if (isMove)	str += TEXT("Move");
	else			str += TEXT("Idle");

	if (lookDir.x > 0) str += TEXT("Right");
	else if (lookDir.x < 0) str += TEXT("Left");

	if (lookDir.y > 0) str += TEXT("Up");
	else if (lookDir.y < 0) str += TEXT("Down");

	animator->Play(str, false);
}
