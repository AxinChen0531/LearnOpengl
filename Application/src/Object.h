/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : 一些基本的场景结构类
*/

#pragma once

#include "AMath.h"
#include <unordered_map>
#include <vector>
#include <memory>

class GameObject;
class Component;

class GameObject final
{
private:
	static GameObject* m_root;

private:
	unsigned int m_indexAsChild;
	bool m_active;
	bool m_needDestroy;
	std::unordered_map<unsigned int, Component*> m_comps;

	bool m_transFlag;
	std::weak_ptr<GameObject> m_parent;
	std::vector<std::shared_ptr<GameObject>> m_children;
	Vec3 m_localScale;
	Vec3 m_scale;
	Quaternion m_localRotation;
	Quaternion m_rotation;
	Vec3 m_localPosition;
	Vec3 m_position;

public:
	GameObject();
	~GameObject();

	template<typename T>
	T& AddComponent();
	template<typename T>
	T& GetComponent() const;
	template<typename T>
	bool RemoveComponent();

	void SetActive(bool active);
	std::weak_ptr<GameObject> GetParent() const;
	void SetParent(std::weak_ptr<GameObject> newP);
	unsigned int GetChildCount() const;
	std::weak_ptr<GameObject> GetChild(int index) const;
	void RemoveChild(int index);
	const GameObject* Root() const;

	Vec3 LocalPosition() const;
	Vec3 Position() const;
	Vec3 LocalScale() const;
	Vec3 Scale() const;
	Quaternion LocalRotation() const;
	Quaternion Rotation() const;
	void SetPosition(const Vec3& newPos);
	void SetLocalPosition(const Vec3& newPos);
	void SetLocalScale(const Vec3& newScale);
	void SetRotation(const Quaternion& newR);
	void SetLocalRotation(const Quaternion& newR);

	void Destroy();

private:
	void Update();
};



class Component
{
private:
	bool m_enable;
	std::weak_ptr<GameObject> m_gameObj;

public:
	Component();
	~Component();

	GameObject& GameObject() const;
	void SetEnable(bool enable);
	void Destroy();

	virtual void Awake();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void Update();
	virtual void OnDestroy();
};