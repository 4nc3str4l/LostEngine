#include "Sprite.h"


namespace LostEngine { namespace Gfx2D {
    
Sprite::Sprite()
{
    Position = new glm::vec2(0, 0);
    Scale = new glm::vec2(1, 1);
    Rotation = 0.0f;
    Color = new glm::vec3(1.0f);
}

Sprite::~Sprite()
{
    delete Position;
    delete Scale;
    delete Color;
}

}}