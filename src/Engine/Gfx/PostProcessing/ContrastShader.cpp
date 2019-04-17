#include "ContrastShader.h"
#include "../../LostEngine.h"

namespace le { namespace gfx {
    
ContrastShader::ContrastShader(): Shader((FileSystem::basePath + "/resources/shaders/postProcessing/contrast.vs").c_str(), (FileSystem::basePath + "/resources/shaders/postProcessing/contrast.fs").c_str())
{
	bindAttributes();
}

ContrastShader::~ContrastShader()
{
}

void ContrastShader::bindAttributes()
{
    BindAttribute("position", 0);
}
}}