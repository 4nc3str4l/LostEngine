#pragma once

#include "../Utils/Shader.h"

namespace LostEngine { namespace Gfx {
    
class ParticleShader : public Shader
{
public:
	ParticleShader();
	void LoadTextureCoordInfo(const glm::vec2&  _offset1, glm::vec2& _offset2, float _numRows, float _blend);
	void BindAttributes();
};

}}