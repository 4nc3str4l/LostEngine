#pragma once
#include "../Models/RawModel.h"
#include <glad/glad.h>
#include "../Utils/Loader.h"

namespace le { namespace gfx {


class PostProcessing
{
private:
    void start();
    void end();
public:
    ~PostProcessing();
    void doPostProcessing(GLuint _colorTexture);
    void init(Loader* _loader);
private:
    float m_Positions[8] {-1, 1, -1, -1, 1, 1, 1, -1};
    RawModel* m_Quad;
public:
    static PostProcessing instance;

};
}}