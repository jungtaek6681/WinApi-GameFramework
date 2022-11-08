#pragma once
class CGame
{
public:
	CGame();
	virtual ~CGame();

public:
	void Init();
	void Run();
	void Release();

private:
	void Input();
	void Update();
	void Render();
};

