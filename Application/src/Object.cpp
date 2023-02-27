/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : 一些基本的逻辑结构类，用来对运行时的场景结构做组织
 */

#include <exception>

#include "Object.h"

Component::Component() : m_entity(nullptr), IsDisposed(false)
{
}

Component::~Component()
{
	m_entity = nullptr;
}

Entity* Component::GetEntity() const
{
	return m_entity;
}

void Component::Dispose()
{
	if (IsDisposed)
		return;
	IsDisposed = true;
	if (m_entity != nullptr) {
		m_entity->RemoveComponent(GetTypeInfo());
		m_entity = nullptr;
	}
	EventCenter::Delete(this);
}

Entity::Entity() : IsDisposed(false)
{
}

Entity::~Entity()
{
}

void Entity::Dispose()
{
	if (IsDisposed)
		return;
	IsDisposed = true;
	for (auto p : m_comps) {
		p.second->m_entity = nullptr;
		p.second->Dispose();
	}
	m_comps.clear();
	EventCenter::Delete(this);
}

void Entity::RemoveComponent(const type_info* typeinfo)
{
	if (m_comps.find(typeinfo) == m_comps.end()) 
		return;
	Component* p = m_comps[typeinfo];
	m_comps.erase(typeinfo);
	p->m_entity = nullptr;
	p->Dispose();
}

void Entity::RemoveAllComponents()
{
	for (auto p : m_comps) {
		p.second->m_entity = nullptr;
		p.second->Dispose();
	}
	m_comps.clear();
}

std::unordered_set<IStart*> EventCenter::starters;
std::unordered_set<IUpdate*> EventCenter::updaters;
std::queue<IObject*> EventCenter::toRemoves;
std::queue<IStart*> EventCenter::toAddStart;
std::queue<IUpdate*> EventCenter::toAddUpdate;

void EventCenter::Delete(IObject* obj)
{
	toRemoves.push(obj);
}

void EventCenter::Update()
{
	while (!toRemoves.empty()) {
		IObject* ro = toRemoves.front();
		toRemoves.pop();
		updaters.erase(dynamic_cast<IUpdate*>(ro));
		delete ro;
	}
	while (!toAddStart.empty()) {
		starters.insert(toAddStart.front());
		toAddStart.pop();
	}
	while (!toAddUpdate.empty()) {
		updaters.insert(toAddUpdate.front());
		toAddUpdate.pop();
	}

	for (IStart* s : starters) {
		try {
			s->Start();
		} catch (std::exception e) {
			Log::Error(e.what());
		}
	}
	starters.clear();

	for (IUpdate* u : updaters) {
		try {
			u->Update();
		} catch (std::exception e) {
			Log::Error(e.what());
		}
	}
}