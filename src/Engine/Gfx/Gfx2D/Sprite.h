#pragma once

#include "../../Components/RenderComponent.h"

namespace Lost { namespace Gfx2D {

class Sprite
{
public:
    Sprite();
    ~Sprite();
	void SetColor(float _r, float _g, float _b, float _a);
	void SetColor(int _r, int _g, int _b, int _a);
public:
    glm::vec2* Position;
    glm::vec2* Scale;
    GLfloat Rotation;
    glm::vec3* Color;
	float Transparency;
};

}}