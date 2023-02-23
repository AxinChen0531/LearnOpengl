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
	EventCenter.Remove(this);
}

Entity::Entity() : ID(0), IsDisposed(false)
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
	EventCenter.Remove(this);
}
