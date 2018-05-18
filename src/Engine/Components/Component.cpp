#include "Component.h"

namespace le { namespace components {

int Component::instanceCounter = 0;

Component::Component(SpecificType _componentType)
{
    specificType = _componentType;
	id = instanceCounter++;
	isActive = true;
}

Component::~Component()
{
}

}}