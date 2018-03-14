#pragma once

#include "../Gfx/Utils/Shader.h"
#include "Component.h"

namespace Lost { namespace Components {
class RenderComponent : public Component
{
public:
    RenderComponent(SpecificType _type);
	virtual ~RenderComponent();
	virtual void Render(Gfx::Shader* _shader) = 0;
};
}}