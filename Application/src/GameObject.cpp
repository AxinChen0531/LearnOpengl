/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : GameObject，整合了Transform的实体类
*/

#include "GameObject.h"

GameObject GameObject::SceneRoot = GameObject();

GameObject::GameObject() : m_indexAsChild(-1), m_Parent(nullptr), updateFlag(true), m_depth(0)
{
	m_uid = cid++;
}

GameObject::~GameObject()
{
}

void GameObject::Dispose()
{
	if (IsDisposed)
		return;
	Entity::Dispose();

	if (m_Parent) {
		m_Parent->m_children.back()->m_indexAsChild = m_indexAsChild;
		m_Parent->m_children[m_indexAsChild] = m_children.back();
		m_Parent->m_children.pop_back();
		m_Parent = nullptr;
	}
	for (GameObject* p : m_children) {
		p->Dispose();
		p->m_Parent = nullptr;
	}
	m_children.clear();
}

void GameObject::Awake()
{
	SetParentWithoutJudge(&SceneRoot);
}

void GameObject::Awake(GameObject* parent)
{
	SetParentWithoutJudge(parent);
}

void GameObject::Awake(GameObject* parent, const Vec3& localPos)
{
	m_localPosition = localPos;
	SetParentWithoutJudge(parent);
}

GameObject* GameObject::GetChild(int index)
{
	if (index < 0 || index >= m_children.size())
		return nullptr;
	return m_children[index];
}

bool GameObject::SetParent(GameObject* newParent)
{
	if (!newParent) {
		SetParentWithoutJudge(&SceneRoot);
		return true;
	}
	int dura = newParent->m_depth - m_depth;
	if (dura > 0) {
		GameObject* p = newParent;
		for (int i = 0; i < dura; i++)
			p = p->m_Parent;
		if (p == this) 
			return false;
		SetParentWithoutJudge(newParent);
		return true;
	} else {
		SetParentWithoutJudge(newParent);
		return true;
	}
}

bool GameObject::MakeIndep(int index)
{
	if (index < 0 || index >= m_children.size())
		return false;
	m_children[index]->SetParentWithoutJudge(&SceneRoot);
	return true;
}

bool GameObject::MakeIndep(GameObject* child)
{
	if (child->m_Parent != this)
		return false;
	child->SetParentWithoutJudge(&SceneRoot);
	return false;
}

void GameObject::UpdateDepth(int depth)
{
	m_depth = depth;
	depth++;
	for (GameObject* p : m_children)
		UpdateDepth(depth);
}

void GameObject::SetParentWithoutJudge(GameObject* newParent)
{
	updateFlag = true;
	if (m_Parent) {
		m_Parent->m_children.back()->m_indexAsChild = m_indexAsChild;
		m_Parent->m_children[m_indexAsChild] = m_children.back();
		m_Parent->m_children.pop_back();
	}
	m_Parent = newParent;
	m_indexAsChild = newParent->m_children.size();
	UpdateDepth(newParent->m_depth + 1);
	newParent->m_children.push_back(this);
}
