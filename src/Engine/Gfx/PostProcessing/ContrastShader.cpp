#include "ContrastShader.h"

namespace le { namespace gfx {
    
ContrastShader::ContrastShader(): Shader((FileSystem::basePath + VERTEX_FILE).c_str(), (FileSystem::basePath + FRAGMENT_FILE).c_str())
{
}

ContrastShader::~ContrastShader()
{
}


void ContrastShader::bindAttributes()
{
    BindAttribute("position", 0);
}

}}