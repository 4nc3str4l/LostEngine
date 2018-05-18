#include "ParticleShader.h"

#include "../../Tools/FileSystem.h"

namespace le { namespace gfx {
	ParticleShader::ParticleShader() : Shader((tools::FileSystem::basePath + "./resources/shaders/particles/particles.vs").c_str(), (tools::FileSystem::basePath + "./resources/shaders/particles/particles.fs").c_str())
	{
		m_texOffset1 = glGetUniformLocation(ID, "texOffset1");
		m_texOffset2 = glGetUniformLocation(ID, "texOffset2");
		m_texCoordInfo = glGetUniformLocation(ID, "texCoordInfo");
		m_numOfRows = glGetUniformLocation(ID, "numberOfRows");
		m_projectionMatrix = glGetUniformLocation(ID, "projectionMatrix");
	}

	void ParticleShader::LoadTextureCoordInfo(const glm::vec2& _offset1, glm::vec2& _offset2, float _numRows, float _blend) const
	{
		SetVec2(m_texOffset1, _offset1);
		SetVec2(m_texOffset2, _offset2);
		SetVec2(m_texCoordInfo, glm::vec2(_numRows, _blend));
	}

	void ParticleShader::BindAttributes() const
	{
		BindAttribute("position", 0);
		BindAttribute("modelViewMatrix", 1);
		BindAttribute("texOffsets", 5);
		BindAttribute("blendFactor", 6);
	}

	void ParticleShader::SetNumberOfRows(float _numberOfRows) const
	{
		SetFloat(m_numOfRows, _numberOfRows);
	}

	void ParticleShader::SetProjectionMatrix(const glm::mat4& _projection) const
	{
		SetMat4(m_projectionMatrix, _projection);
	}



}}
