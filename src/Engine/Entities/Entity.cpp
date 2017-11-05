#include "Entity.h"

namespace LostEngine { namespace Components {

Entity::Entity()
{
	m_components = new std::map<GlobalType, std::vector<Component*>*>();
	transform = new Transform(this);
}

void Entity::DeleteComponentsOfType(GlobalType _type)
{
	if (m_components->find(_type) != m_components->end())
	{
		std::vector<Component*>* componentsOfType = (*m_components)[_type];
		for(Component* component : (*componentsOfType))
		{
			delete component;
		}
		componentsOfType->clear();
		delete componentsOfType;
	}
}

Entity::~Entity()
{
	// If the entity contains a parent the transform will be destroyed by him
	if(!transform->HasParent())
		delete transform;

	DeleteComponentsOfType(GlobalType::Type_PhysXComponent);
	DeleteComponentsOfType(GlobalType::Type_RenderComponent);
}

void Entity::Tick(float _delta)
{

}

// TODO: use templates for that
Component* Entity::AddComponent(Component* _component)
{
	// If there is no component on the dictionary for the global type
	if (m_components->find(_component->globalType) == m_components->end()) 
	{
		(*m_components)[_component->globalType] = new std::vector<Component*>();
	}
	(*m_components)[_component->globalType]->push_back(_component);
	return _component;
}

void Entity::RemoveComponent(Component* _component)
{
	if (m_components->find(_component->globalType) != m_components->end())
	{
		std::vector<Component*>* componentsOfType = (*m_components)[_component->globalType];
		for (int i = m_components->size() - 1; i >= 0; i--)
		{
			Component* component = componentsOfType->at(i);
			if (component->id == _component->id) 
			{
				componentsOfType->erase(componentsOfType->begin() + i);
				delete _component;
				return;
			}
		}
	}
	Tools::LOG::FAIL("Component With ID: " + std::to_string(_component->id) + " Not found!");
}

std::vector<Component*>* Entity::GetComponentsOfType(GlobalType _type)
{
	if (m_components->find(_type) != m_components->end())
	{
		return (*m_components)[_type];
	}
	return nullptr;
}


}}