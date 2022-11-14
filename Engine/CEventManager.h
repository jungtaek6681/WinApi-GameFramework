#pragma once
class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
private:
	CEventManager();
	virtual ~CEventManager();

public:
	void Init();
	void Update();
	void Release();
};

