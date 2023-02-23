#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class IObject
{
public:
	virtual void Dispose() = 0;
};

template<typename A>
class IAwake : public IObject
{
public:
	virtual void Awake(A a) = 0;
};

class IAwake<void> : public IObject
{
public:
	virtual void Awake() = 0;
};

template<typename A, typename B>
class IAwake: public IObject
{
public:
	virtual void Awake(A a, B b) = 0;
};

template<typename A, typename B, typename C>
class IAwake: public IObject
{
public:
	virtual void Awake(A a, B b, C c) = 0;
};

class IStart: public IObject
{
public:
	virtual void Start() = 0;
};

class IUpdate: public IObject
{
public:
	virtual void Update() = 0;
};


class Entity;
class Component;

class Component : IObject
{
	friend Entity;
private:
	Entity* m_entity;
public:
	Component();
	~Component();
	bool IsDisposed;

public:
	Entity* GetEntity() const;
	virtual const type_info* GetTypeInfo() const = 0;
	virtual void Dispose() override;
};

class Entity : IObject
{
public:
	unsigned long long ID;
	bool IsDisposed;
private:
	std::unordered_map<const type_info*, Component*> m_comps;

public:
	Entity();
	~Entity();

	virtual void Dispose() override;

	template<typename T>
	T* AddComponent();

	template<typename T, typename A>
	T* AddComponent(A a);

	template<typename T, typename A, typename B>
	T* AddComponent(A a, B b);

	template<typename T, typename A, typename B, typename C>
	T* AddComponent(A a, B b, C c);

	template<typename T>
	T* GetComponent() const;

	template<typename T>
	void RemoveComponent();
	void RemoveComponent(const type_info* typeinfo);
	void RemoveAllComponents();
} Scene;

class EventCenter
{
private:
	std::unordered_set<IStart*> starters;
	std::unordered_set<IUpdate*> updaters;
	
	std::queue<IObject*> toRemove;
	std::queue<IStart*> toAddStart;
	std::queue<IUpdate*> toAddUpdate;

private:
	void Awake(IObject* obj);
public:
	void Awake(IObject* obj) const;

	template<typename A>
	void Awake(IObject* obj, A a) const;

	template<typename A, typename B>
	void Awake(IObject* obj, A a, B b) const;

	template<typename A, typename B, typename C>
	void Awake(IObject* obj, A a, B b, C c) const;

	void Remove(IObject* obj);

	void Update();
} EventCenter;