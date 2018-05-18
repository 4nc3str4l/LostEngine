#pragma once

#include "../Gfx/Utils/Shader.h"
#include "Component.h"

namespace le { namespace components {
class RenderComponent : public Component
{
public:
    RenderComponent(SpecificType _type);
	virtual ~RenderComponent();
	virtual void Render(gfx::Shader* _shader) = 0;
};
}}