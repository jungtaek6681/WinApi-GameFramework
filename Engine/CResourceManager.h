#pragma once

//========================================
//##		디자인 패턴 FlyWeight		##
//========================================
/*
	한개의 고유 데이터를 다른 객체들에서 공유하게 만들어 메모리 사용량을 줄임
	고유 데이터를 참조하여 사용하기에 불러오는 시간을 줄임
*/

class CResourceManager : public SingleTon<CResourceManager>
{
	friend SingleTon<CResourceManager>;
private:
	CResourceManager();
	virtual ~CResourceManager();

public:
	void			Init();
	void			Release();

	CImage*			ImageFind(const wstring& key);
	CImage*			ImageLoad(const wstring& key, const wstring& file);

	const wstring&	GetResourceFolder()							{ return resourceFolder; }
	void			SetResourceFolder(const wstring& folder)	{ this->resourceFolder = folder; }

private:
	unordered_map<wstring, CImage*>	images;

	wstring resourceFolder;
};

#define LOADIMAGE(key, file)	CResourceManager::GetInstance()->ImageLoad(key, file)