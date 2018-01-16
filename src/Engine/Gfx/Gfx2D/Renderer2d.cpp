#include "Renderer2d.h"

namespace LostEngine { namespace Gfx2D {
Renderer2d::Renderer2d(Shader* _shader)
{
    m_Shader = _shader;
}

Renderer2d::Init()
{

}

Renderer2d::DrawSprite(GLuint _textureID, Sprite* _sprite)
{

}


Renderer2d::~Renderer2d()
{
    delete m_Shader;
}
}}