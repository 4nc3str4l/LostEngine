#pragma once

#include <map>
#include <vector>
#include "../Components/Component.h"
#include "../Tools/Log.h"
#include "../Components/Transform.h"

namespace LostEngine { namespace Components {
class Entity
{
public:
	Transform* transform;
public:
    Entity();
    ~Entity();
	std::map<GlobalType, std::vector<Component*>*>* m_components;
	Component* AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	std::vector<Component*>* GetComponentsOfType(GlobalType _type);
	virtual void Tick(float _delta);

private:
	void DeleteComponentsOfType(GlobalType _type);
};
}}

/*
	TODO: GetComponent<>();
	template <typename T> struct Map{}
	template <> struct Map<Camera>{ const static int value = 0; };
	template <> struct Map<Player> { const static int value = 1; }
	template <typename T>
	T get() {
	...
	}
	int idx = Map<T>::value;
*/