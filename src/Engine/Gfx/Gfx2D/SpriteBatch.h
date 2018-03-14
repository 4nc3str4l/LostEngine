#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include "../Models/RawModel.h"
#include "../Utils/Loader.h"
#include "../Utils/Camera.h"
#include "Sprite.h"

namespace Lost { namespace Gfx2D {

using namespace Gfx;

class SpriteBatch
{
public:
    SpriteBatch(Loader* _loader, Shader* _shader);
    ~SpriteBatch();
    void Render(std::map<GLuint, std::vector<Sprite*>*> _sprites);
private:
    void Prepare();
    void Finish();
    void BindTexture(GLuint texture);
    void StoreMatrixData(const glm::mat4& _matrix);
    void UpdateTexCoordInfo(Sprite* _sprite);
private:
    static float m_vertices[8];
    static float m_buffer[];
    static unsigned int m_bufferPointer;
    RawModel* m_quad;
    Shader* m_shader;
    Loader* m_loader;
    GLuint m_vbo;
};

}}