/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 一些基本的逻辑结构类，用来对运行时的场景结构做组织
 */

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "Log.h"

class IObject
{
public:
	virtual void Dispose() = 0;
};

class IAwake
{
public:
	virtual void Awake() = 0;
};

template<typename A>
class IAwake1
{
public:
	virtual void Awake(A a) = 0;
};

template<typename A, typename B>
class IAwake2
{
public:
	virtual void Awake(A a, B b) = 0;
};

template<typename A, typename B, typename C>
class IAwake3
{
public:
	virtual void Awake(A a, B b, C c) = 0;
};

class IStart
{
public:
	virtual void Start() = 0;
};

class IUpdate
{
public:
	virtual void Update() = 0;
};



class Entity;
class Component;
class ObjectFactory;
class EventCenter;

/// <summary>
/// 组件类，请继承并自定义各种组件
/// 重写析构以控制内存释放
/// 重写Dispose方法来进行生命周期尾部的设置
/// (必须)请重写GetTyepInfo方法，使用typeid关键字获取自定类信息
/// 请勿手动更改IsDisposed
/// 请使用生命周期接口而非构造函数初始化数据
/// </summary>
class Component : IObject
{
	friend Entity;
private:
	Entity* m_entity;		//挂载实体
public:
	Component();
	virtual ~Component();
	bool IsDisposed;		//用于控制释放

public:
	/// <summary>
	/// 获取挂载的实体指针，若无返回nullptr
	/// </summary>
	/// <returns></returns>
	Entity* GetEntity() const;
	virtual const type_info* GetTypeInfo() const = 0;
	virtual void Dispose() override;
};



/// <summary>
/// 请使用Object工厂创建临时或根Object
/// </summary>
class ObjectFactory
{
public:
	template<typename T>
	static T* Create() {
		static_assert(std::is_base_of<Component, T>::value || std::is_base_of<Entity, T>::value, " -- need base on Entity/Component class -- ");
		T* obj = new T();
		EventCenter::Awake<T>(obj);
		return obj;
	}

	template<typename T, typename A>
	static T* Create(A a) {
		static_assert(std::is_base_of<Component, T>::value || std::is_base_of<Entity, T>::value, " -- need base on Entity/Component class -- ");
		T* obj = new T();
		EventCenter::Awake<T, A>(obj, a);
		return obj;
	}

	template<typename T, typename A, typename B>
	static T* Create(A a, B b) {
		static_assert(std::is_base_of<Component, T>::value || std::is_base_of<Entity, T>::value, " -- need base on Entity/Component class -- ");
		T* obj = new T();
		EventCenter::Awake<T, A, B>(obj, a, b);
		return obj;
	}

	template<typename T, typename A, typename B, typename C>
	static T* Create(A a, B b, C c) {
		static_assert(std::is_base_of<Component, T>::value || std::is_base_of<Entity, T>::value, " -- need base on Entity/Component class -- ");
		T* obj = new T();
		EventCenter::Awake<T, A, B, C>(obj, a, b, c);
		return obj;
	}
};



/// <summary>
/// 实体类，请继承并自定义各种实体
/// 重写析构以控制内存释放
/// 重写Dispose方法来进行生命周期尾部的设置
/// 请勿手动更改IsDisposed
/// 请使用生命周期接口而非构造函数初始化数据
/// </summary>
class Entity : IObject
{
public:
	bool IsDisposed;
private:
	std::unordered_map<const type_info*, Component*> m_comps;

public:
	Entity();
	virtual ~Entity();

	virtual void Dispose() override;

	template<typename T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, " -- need base on Component class -- ");
		const type_info* tid = &typeid(T);
		if (m_comps.find(tid) != m_comps.end()) {
			Log::Warning("Component already exist");
			return dynamic_cast<T*>(m_comps[tid]);
		}
		T* comp = new T();
		m_comps[tid] = comp;
		EventCenter::Awake<T>(comp);
		return comp;
	}

	template<typename T, typename A>
	T* AddComponent(A a)
	{
		static_assert(std::is_base_of<Component, T>::value, " -- need base on Component class -- ");
		const type_info* tid = &typeid(T);
		if (m_comps.find(tid) != m_comps.end()) {
			Log::Warning("Component already exist");
			return dynamic_cast<T*>(m_comps[tid]);
		}
		T* comp = new T();
		m_comps[tid] = comp;
		EventCenter::Awake<T, A>(comp, a);
		return comp;
	}

	template<typename T, typename A, typename B>
	T* AddComponent(A a, B b)
	{
		static_assert(std::is_base_of<Component, T>::value, " -- need base on Component class -- ");
		const type_info* tid = &typeid(T);
		if (m_comps.find(tid) != m_comps.end()) {
			Log::Warning("Component already exist");
			return dynamic_cast<T*>(m_comps[tid]);
		}
		T* comp = new T();
		m_comps[tid] = comp;
		EventCenter::Awake<T, A, B>(comp, a, b);
		return comp;
	}

	template<typename T, typename A, typename B, typename C>
	T* AddComponent(A a, B b, C c)
	{
		static_assert(std::is_base_of<Component, T>::value, " -- need base on Component class -- ");
		const type_info* tid = &typeid(T);
		if (m_comps.find(tid) != m_comps.end()) {
			Log::Warning("Component already exist");
			return dynamic_cast<T*>(m_comps[tid]);
		}
		T* comp = new T();
		m_comps[tid] = comp;
		EventCenter::Awake<T, A, B, C>(comp, a, b, c);
		return comp;
	}

	template<typename T>
	T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, " -- need base on Component class -- ");
		const type_info* tid = &typeid(T);
		if (m_comps.find(tid) == m_comps.end()) 
			return nullptr;
		return m_comps[tid];
	}

	template<typename T>
	void RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, " -- need base on Component class -- ");
		RemoveComponent(&typeid(T));
	}
	void RemoveComponent(const type_info* typeinfo);
	void RemoveAllComponents();
};



class EventCenter
{
private:
	static std::unordered_set<IStart*> starters;
	static std::unordered_set<IUpdate*> updaters;
	
	static std::queue<IObject*> toRemoves;
	static std::queue<IStart*> toAddStart;
	static std::queue<IUpdate*> toAddUpdate;

private:
	EventCenter() {};
	template<typename T>
	static void AwakeCommon(T* obj) {
		IStart* starter = dynamic_cast<IStart*>(obj);
		IUpdate* updater = dynamic_cast<IUpdate*>(obj);
		if (starter)
			toAddStart.push(starter);
		if (updater)
			toAddUpdate.push(updater);
	}
public:
	template<typename T>
	static void Awake(T* obj) {
		AwakeCommon(obj);
		if (obj)
			obj->Awake();
	}

	template<typename T, typename A>
	static void Awake(T* obj, A a)
	{
		AwakeCommon(obj);
		if (obj)
			obj->Awake(a);
	}

	template<typename T, typename A, typename B>
	static void Awake(T* obj, A a, B b)
	{
		AwakeCommon(obj);
		if (obj)
			obj->Awake(a, b);
	}

	template<typename T, typename A, typename B, typename C>
	static void Awake(T* obj, A a, B b, C c)
	{
		AwakeCommon(obj);
		if (obj)
			obj->Awake(a, b, c);
	}

	static void Delete(IObject* obj);

	static void Update();
};