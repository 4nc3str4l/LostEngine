#include "Sprite.h"


namespace le { namespace gfx2d {
    
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

void Sprite::SetColor(float _r, float _g, float _b, float _a)
{
	Color->x = _r;
	Color-> y = _g;
	Color->z = _b;
	Transparency = _a;
}

void Sprite::SetColor(int _r, int _g, int _b, int _a)
{
	Color->x = _r / 255.0f;
	Color->y = _g / 255.0f;
	Color->z = _b / 255.0f;
	Transparency = _a / 255.0f;
}

}}