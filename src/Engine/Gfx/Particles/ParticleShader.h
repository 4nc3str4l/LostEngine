#pragma once

#include "../Utils/Shader.h"

namespace le { namespace gfx {
    
class ParticleShader : public Shader
{
public:
	ParticleShader();
	void LoadTextureCoordInfo(const glm::vec2&  _offset1, glm::vec2& _offset2, float _numRows, float _blend) const;
	void BindAttributes() const;
	void SetNumberOfRows(float _numberOfRows) const;
	void SetProjectionMatrix(const glm::mat4& _projection) const;
private:
	GLuint m_texOffset1;
	GLuint m_texOffset2;
	GLuint m_texCoordInfo;
	GLuint m_numOfRows;
	GLuint m_projectionMatrix;

};

}}