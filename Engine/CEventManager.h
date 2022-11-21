#pragma once

class CScene;
class CGameObject;
class CUI;

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

	void AddGameObject(CScene* scene, CGameObject* obj);							// ���ӿ�����Ʈ �߰� �̺�Ʈ �߰�
	void AddChild(CGameObject* parent, Component<CGameObject>* child);				// ������Ʈ �߰� �̺�Ʈ �߰�
	void Delete(CScene* scene, Component<CGameObject>* obj);						// ������Ʈ ���� �̺�Ʈ �߰�

	void AddUI(CScene* scene, CUI* ui);												// UI �߰� �̺�Ʈ �߰�
	void AddChild(CUI* parent, CUI* child);											// �ڽ�UI �߰� �̺�Ʈ �߰�
	void Delete(CScene* scene, CUI* ui);											// UI ���� �̺�Ʈ �߰�
	void ShowUI(CUI* ui, bool show);												// UI ǥ�� ���� �̺�Ʈ �߰�

	void ChangeScene(int sceneType, float delay = 0);								// �� ��ȯ �̺�Ʈ �߰�

private:
	void ProgressAddGameObject();													// ���ӿ�����Ʈ �߰� �̺�Ʈ ����
	void ProgressAddComponent();													// ������Ʈ �߰� �̺�Ʈ ����
	void ProgressDeleteObject();													// ������Ʈ ���� �̺�Ʈ ����

	void ProgressAddUI();															// UI �߰� �̺�Ʈ ����
	void ProgressAddChildUI();														// �ڽ�UI �߰� �̺�Ʈ ����
	void ProgressDeleteUI();														// UI ���� �̺�Ʈ ����
	void ProgressShowUI();															// UI ǥ�� ���� �̺�Ʈ ����

	void ProgressChangeScene();														// �� ��ȯ �̺�Ʈ ����

private:
	queue<pair<CScene*, CGameObject*>>					addGameObjectQueue;			// ���ӿ�����Ʈ �߰� �̺�Ʈ ����
	queue<pair<CGameObject*, Component<CGameObject>*>>	addChildQueue;				// ������Ʈ �߰� �̺�Ʈ ����
	queue<pair<CScene*, Component<CGameObject>*>>		deleteObjectQueue;			// ������Ʈ ���� �̺�Ʈ ����

	queue<pair<CScene*, CUI*>>							addUIQueue;					// UI �߰� �̺�Ʈ ����
	queue<pair<CUI*, CUI*>>								addChildUIQueue;			// �ڽ�UI �߰� �̺�Ʈ ����
	queue<pair<CScene*, CUI*>>							deleteUIQueue;				// UI ���� �̺�Ʈ ����
	queue<pair<CUI*, bool>>								showUIQueue;				// UI ǥ�� ���� �̺�Ʈ ����

	pair<int, float>*									changeSceneEvent;			// �� ��ȯ �̺�Ʈ ���� ����
};

#define EVENT		CEventManager::GetInstance()

