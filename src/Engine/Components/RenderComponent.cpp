#include "RenderComponent.h"

namespace LostEngine { namespace Components { 

RenderComponent::RenderComponent(SpecificType _type):
    Component(_type)
{
    globalType = GlobalType::Type_RenderComponent;
}

RenderComponent::~RenderComponent()
{
}

}}