#pragma once

#include "Sprite.h"
#include "../Utils/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Lost { namespace Gfx2D {

using namespace Gfx;

class Renderer2d{
public:
    Renderer2d(Shader* _shader);
    ~Renderer2d();
    void DrawSprite(GLuint _textureID, Sprite* _sprite);
    void Prepare();
    void Finnish();
private:
    void Init();
private:
    Shader* m_Shader;
    GLuint m_QuadVAO;
};

}}