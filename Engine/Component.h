#pragma once

// 디자인패턴 컴포지트 :
// 여러 개의 객체들로 구성된 복합 객체와 단일 객체를
// 클라이언트에서 구별 없이 다루게 해주는 패턴
// 전체-부분의 관계를 갖는 객체들 사이의 관계를 정의할 때 유용
// 트리형 구조를 가지게 됨
// 
// 게임프로그래밍 컴포넌트 : 
// 프로그래밍에 있어 기능 재사용이 가능한 각각의 독립된 모듈
// 컴포지트 구조에서 부모에 포함될 경우 독립적으로 동작하는 자식 모듈로 사용
// 상속의 경우 모든 상속하는 자식에게 반드시 기능이 포함되지만
// 컴포넌트의 경우 필요한 객체에만 조립식으로 붙일 수 있음

template <typename T>
class Component
{
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

protected:
	void			SetOwner(T* owner)		{ this->owner = owner; }
	void			SetActive(bool active)	{ this->active = active; }

protected:
	T*				owner					= nullptr;
	bool			active					= false;
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

protected:
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
	list<Component<T>*> childList;
};