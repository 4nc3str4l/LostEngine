#pragma once
#include "../Utils/Shader.h"

namespace le { namespace gfx {
    
class ContrastShader : public Shader
{

public:
    ContrastShader();
    ~ContrastShader();
    void bindAttributes();
};

}}