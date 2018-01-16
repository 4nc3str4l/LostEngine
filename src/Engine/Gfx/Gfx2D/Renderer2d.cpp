#include "Renderer2d.h"

namespace LostEngine { namespace Gfx2D {
Renderer2d::Renderer2d(Shader* _shader)
{
    m_Shader = _shader;
    Init();
}

void Renderer2d::Init()
{
    GLuint VBO;
    GLfloat vertices[] = { 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_QuadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_QuadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer2d::Prepare()
{
    m_Shader->Use();
    
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_QuadVAO);
}

void Renderer2d::DrawSprite(GLuint _textureID, Sprite* _sprite)
{
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(*_sprite->Position, 0.0f));
    glBindTexture(GL_TEXTURE_2D, _textureID);

    model = glm::translate(model, glm::vec3(0.5f * _sprite->Scale->x, 0.5f * _sprite->Scale->y, 0.0f));
    model = glm::rotate(model, _sprite->Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * _sprite->Scale->x, -0.5f * _sprite->Scale->y, 0.0f));

    model = glm::scale(model, glm::vec3(*_sprite->Scale, 1.0f));

    m_Shader->SetMat4("model", model);

    // Render textured quad
    m_Shader->SetVec3("spriteColor", *_sprite->Color);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer2d::Finnish()
{
    glBindVertexArray(0);
}


Renderer2d::~Renderer2d()
{
    delete m_Shader;
    glDeleteVertexArrays(1, &m_QuadVAO);
}

}}