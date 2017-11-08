#include "ParticleShader.h"

#include "../../Tools/FileSystem.h"

namespace LostEngine { namespace Gfx {
	ParticleShader::ParticleShader() : Shader((Tools::FileSystem::basePath + "./resources/shaders/particles/particles.vs").c_str(), (Tools::FileSystem::basePath + "./resources/shaders/particles/particles.fs").c_str())
	{
			
	}
}}
