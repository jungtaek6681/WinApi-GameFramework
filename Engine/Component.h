#pragma once

// ���������� ������Ʈ :
// ���� ���� ��ü��� ������ ���� ��ü�� ���� ��ü��
// Ŭ���̾�Ʈ���� ���� ���� �ٷ�� ���ִ� ����
// ��ü-�κ��� ���踦 ���� ��ü�� ������ ���踦 ������ �� ����
// Ʈ���� ������ ������ ��
// 
// �������α׷��� ������Ʈ : 
// ���α׷��ֿ� �־� ��� ������ ������ ������ ������ ���
// ������Ʈ �������� �θ� ���Ե� ��� ���������� �����ϴ� �ڽ� ���� ���
// ����� ��� ��� ����ϴ� �ڽĿ��� �ݵ�� ����� ���Ե�����
// ������Ʈ�� ��� �ʿ��� ��ü���� ���������� ���� �� ����

class CEventManager;
template <typename T>
class Composite;
class CScene;

template <typename T>
class Component
{
	friend CEventManager;
	friend Composite<T>;
public:
	Component() {}
	virtual ~Component() {}

public:
	virtual void	ComponentInit()			= 0;
	virtual void	ComponentOnEnable()		{ active = true; }
	virtual void	ComponentUpdate()		= 0;
	virtual void	ComponentRender()		= 0;
	virtual void	ComponentOnDisable()	{ active = false; }
	virtual void	ComponentRelease()		= 0;

public:
	T*				GetOwner()				{ return owner; }
	bool			IsActive()				{ return active; }
	CScene*			GetScene()				{ return (owner == nullptr) ? scene : owner->GetScene(); }
	bool			IsReservedDelete()		{ return reservedDelete; }

protected:
	void			SetOwner(T* owner)		{ this->owner = owner; }
	void			SetActive(bool active)	{ this->active = active; }
	void			SetScene(CScene* scene) { this->scene = scene; }
	virtual void	SetReservedDelete()		{ reservedDelete = true; }	// ������Ʈ ���� ����

	virtual void	DeleteReservedChild()	{}

protected:
	T*				owner					= nullptr;
	bool			active					= false;
	CScene*			scene					= nullptr;
	bool			reservedDelete			= false;					// ������Ʈ�� ������������ ����
};

template <typename T>
class Composite abstract : public Component<T>
{
public:
	Composite() {}
	virtual ~Composite() {}

public:
	void ComponentInit() override
	{
	}

	void ComponentOnEnable() override
	{
		this->active = true;
		for (Component<T>* component : childList)
		{
			component->ComponentOnEnable();
		}
	}

	void ComponentUpdate() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentUpdate();
		}
	}

	void ComponentRender() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentRender();
		}
	}

	void ComponentOnDisable() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentOnDisable();
		}
		this->active = false;
	}

	void ComponentRelease() override
	{
		for (Component<T>* component : childList)
		{
			component->ComponentRelease();
			delete component;
		}
		childList.clear();
	}

	void AddChild(Component<T>* component)
	{
		childList.push_back(component);
		component->SetOwner((T*)this);
		component->ComponentInit();
		if (this->IsActive()) component->ComponentOnEnable();
	}

	void RemoveChild(Component<T>* component)
	{
		if (this->IsActive()) component->ComponentOnDisable();
		component->ComponentRelease();
		component->SetOwner(nullptr);
		childList.remove(component);
		delete component;
	}

protected:
	void SetReservedDelete() override
	{
		this->reservedDelete = true;
		for (Component<T>* component : childList)
		{
			component->SetReservedDelete();
		}
	}

	void DeleteReservedChild() override
	{
		childList.remove_if([&](Component<T>* child) {
			if (child->IsReservedDelete())
			{
				child->SetOwner(nullptr);
				if (this->IsActive()) child->ComponentOnDisable();
				child->ComponentRelease();
				delete child;
				return true;
			}
			else
			{
				child->DeleteReservedChild();
				return false;
			}
			});
	}

protected:
	list<Component<T>*> childList;
};