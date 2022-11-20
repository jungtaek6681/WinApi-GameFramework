#pragma once

class CUI;

class CUIManager : public SingleTon<CUIManager>
{
	friend SingleTon<CUIManager>;
private:
	CUIManager();
	virtual ~CUIManager();

public:
	void Init();
	void Update();
	void Release();

private:
	void MouseEvent(CUI* ui);
};

