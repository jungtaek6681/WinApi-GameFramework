#pragma once

// 전방선언 : 클래스의 이름만으로 선언
class CScene;

class CSceneManager : public SingleTon<CSceneManager>
{
	friend SingleTon<CSceneManager>;
private:
	CSceneManager();
	virtual ~CSceneManager();

public:
	void		Init();
	void		Update();
	void		Render();
	void		Release();

	CScene*		FindScene(int key);					// 씬 탐색
	void		AddScene(int key, CScene* scene);	// 씬 추가
	void		RemoveScene(int key);				// 씬 삭제
	void		ChangeScene(int key);				// 씬 전환
	void		SetStartScene(int key);				// 시작 씬 설정

	CScene*		GetCurScene();						// 현재 씬 반환

private:
	map<int, CScene*>		mapScene;				// 게임씬들을 보관하는 자료구조
	CScene*					curScene;				// 현재 게임씬
};

