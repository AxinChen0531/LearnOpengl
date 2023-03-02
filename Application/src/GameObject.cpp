/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : GameObject，整合了Transform的实体类
*/

#include "GameObject.h"

GameObject GameObject::SceneRoot = GameObject();
unsigned long long GameObject::cid = 0;

GameObject::GameObject() : m_indexAsChild(-1), m_Parent(nullptr), m_updateFlag(0), m_depth(0)
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

Vec3 GameObject::GetPosition()
{
	UpdateTrans();
	return m_position;
}

Vec3 GameObject::GetScale()
{
	UpdateTrans();
	return m_Scale;
}

Quaternion GameObject::GetRotation()
{
	UpdateTrans();
	return m_Rotation;
}

void GameObject::SetLocalPosition(const Vec3& newPos)
{
	ResetFlags(1);
	m_localPosition = newPos;
}

void GameObject::SetLocalRotation(const Quaternion& newRotation)
{
	ResetFlags(5);
	m_LocalRotation = newRotation;
}

void GameObject::SetLocalScale(const Vec3& newScale)
{
	ResetFlags(3);
	m_localScale = newScale;
}

GameObject* GameObject::GetChild(unsigned int  index)
{
	if (index >= m_children.size())
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

bool GameObject::MakeIndep(unsigned int index)
{
	if (index >= m_children.size())
		return false;
	m_children[index]->SetParentWithoutJudge(&SceneRoot);
	return true;
}

bool GameObject::MakeIndep(GameObject* child)
{
	if (child->m_Parent != this)
		return false;
	child->SetParentWithoutJudge(&SceneRoot);
	return true;
}

void GameObject::ResetDepth(int depth)
{
	m_depth = depth;
	depth++;
	for (GameObject* p : m_children)
		p->ResetDepth(depth);
}

void GameObject::ResetFlags(char flag)
{
	char t = m_updateFlag | flag;
	if (t == m_updateFlag)
		return;
	m_updateFlag = t;
	for (GameObject* p : m_children)
		p->ResetFlags(flag);
}

void GameObject::SetParentWithoutJudge(GameObject* newParent)
{
	ResetFlags(7);
	if (m_Parent) {
		m_Parent->m_children.back()->m_indexAsChild = m_indexAsChild;
		m_Parent->m_children[m_indexAsChild] = m_children.back();
		m_Parent->m_children.pop_back();
	}
	m_Parent = newParent;
	m_indexAsChild = newParent->m_children.size();
	ResetDepth(newParent->m_depth + 1);
	newParent->m_children.push_back(this);
}

void GameObject::UpdateTrans()
{
	if (!m_updateFlag)
		return;
	m_Parent->UpdateTrans();
	if (m_updateFlag & 1)
		m_position = (m_localPosition * m_Parent->m_Scale).Rotate(m_Parent->m_Rotation) + m_Parent->m_position;
	if (m_updateFlag & 2)
		m_Scale = m_localScale * m_Parent->m_Scale;
	if (m_updateFlag & 4)
		m_Rotation = m_LocalRotation * m_Parent->m_Rotation;
	m_updateFlag = 0;
}
