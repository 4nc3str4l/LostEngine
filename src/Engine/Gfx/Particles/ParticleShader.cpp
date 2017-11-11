#include "ParticleShader.h"

#include "../../Tools/FileSystem.h"

namespace LostEngine { namespace Gfx {
	ParticleShader::ParticleShader() : Shader((Tools::FileSystem::basePath + "./resources/shaders/particles/particles.vs").c_str(), (Tools::FileSystem::basePath + "./resources/shaders/particles/particles.fs").c_str())
	{
			
	}

	void ParticleShader::LoadTextureCoordInfo(const glm::vec2& _offset1, glm::vec2& _offset2, float _numRows, float _blend)
	{
		SetVec2("texOffset1", _offset1);
		SetVec2("texOffset2", _offset2);
		SetVec2("texCoordInfo", glm::vec2(_numRows, _blend));
	}


}}
