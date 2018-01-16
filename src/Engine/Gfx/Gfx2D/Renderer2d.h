#pragma once

#include "../Utils/Shader.h"


namespace LostEngine { namespace Gfx2D {

class Renderer2d{
public:
    Renderer2d(Shader* _shader);
    ~Renderer2d();
    void DrawSprite(GLuint _textureID, Sprite* _sprite);
private:
    void Init();
private:
    Shader* m_Shader;
    GLuint m_QuadVAO;
};

}}