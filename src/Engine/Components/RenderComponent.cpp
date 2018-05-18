#include "RenderComponent.h"

namespace le { namespace components { 

RenderComponent::RenderComponent(SpecificType _type):
    Component(_type)
{
    globalType = GlobalType::Type_RenderComponent;
}

RenderComponent::~RenderComponent()
{
}

}}