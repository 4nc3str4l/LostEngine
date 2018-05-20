#pragma once
#include "../Utils/Shader.h"
#include "../../LostEngine.h"

namespace le { namespace gfx {

    
class ContrastShader : public Shader
{
private:
    const std::string VERTEX_FILE = "./resources/shaders/postProcessing/contrast.vs";
    const std::string FRAGMENT_FILE = "./resources/shaders/postProcessing/constrast.fs";
public:
    ContrastShader();
    ~ContrastShader();
    void bindAttributes();
};
}}