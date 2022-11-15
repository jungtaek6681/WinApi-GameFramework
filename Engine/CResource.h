#pragma once

// 리소스 : 게임에 필요한 코드 외의 자원
// ex) 이미지, 사운드, 애니메이션, 등
class CResource
{
public:
	CResource();
	virtual ~CResource();

public:
	const		wstring& GetKey()				{ return key; }
	const		wstring& GetPath()				{ return path; }

	void		SetKey(const wstring& key)		{ this->key = key; }
	void		SetPath(const wstring& path)	{ this->path = path; }

protected:
	wstring		key;							// 리소스의 탐색용 키
	wstring		path;							// 리소스의 경로
};
