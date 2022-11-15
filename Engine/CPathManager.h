#pragma once
class CPathManager : public SingleTon<CPathManager>
{
	friend SingleTon<CPathManager>;
private:
	CPathManager();
	virtual ~CPathManager();

public:
	void Init();
	void Release();

	const wstring& GetPath();

private:
	wstring path;
};

#define PATH			CPathManager::GetInstance()->GetPath()
