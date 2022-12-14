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

	CUI* GetFocusedUI();
	void SetFocusedUI(CUI* ui);

private:
	void MouseEvent(CUI* ui, CUI* topChildUI);

	CUI* GetTopUI();
	CUI* GetTopChildUI(CUI* parentUI);

private:
	CUI* focusedUI;
};

