#pragma once

#include <map>
#include <vector>
#include "../Components/Component.h"
#include "../Tools/Log.h"
#include "../Components/Transform.h"

namespace LostEngine { namespace  Entities {
using namespace Components;
class Entity
{
public:
    Entity();
    ~Entity();
	std::map<GlobalType, std::vector<Component*>*>* m_components;
	Component* AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	std::vector<Component*>* GetComponentsOfType(GlobalType _type);
	virtual void Tick(float _delta) = 0;
public:
	Transform* transform;
private:
	void DeleteComponentsOfType(GlobalType _type);
};
}}
