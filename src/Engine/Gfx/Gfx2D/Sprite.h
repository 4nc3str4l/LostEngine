#pragma once

#include "../../Components/RenderComponent.h"

namespace LostEngine { namespace Gfx2D {

class Sprite
{
public:
    Sprite();
    ~Sprite();
    glm::vec2* Position;
    glm::vec2* Scale;
    GLfloat Rotation;
    glm::vec3* Color;
};

}}