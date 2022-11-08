#pragma once
class CEngine : public SingleTon<CEngine>
{
	friend SingleTon<CEngine>;
private:
	CEngine();
	virtual ~CEngine();
};

