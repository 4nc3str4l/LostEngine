#include "SkyboxShader.h"

#include "../../Tools/FileSystem.h"

namespace le { namespace gfx {
   
	SkyboxShader::SkyboxShader()
		:Shader((tools::FileSystem::basePath + "./resources/shaders/skybox.vs").c_str(), 
		(tools::FileSystem::basePath + "./resources/shaders/skybox.fs").c_str())
	{
		m_projectionMatrix = glGetUniformLocation(ID, "projectionMatrix");
		m_viewMatrix = glGetUniformLocation(ID, "viewMatrix");
	}

	SkyboxShader::~SkyboxShader()
	{
	}

	void SkyboxShader::BindAttributes()
	{
		BindAttribute("position", 0);
	}

	void SkyboxShader::LoadProjectionMatrix(const glm::mat4& _projectionMatrix)
	{
		SetMat4(m_projectionMatrix, _projectionMatrix);
	}

	void SkyboxShader::LoadViewMatrix(const glm::mat4& _viewMatrix)
	{
		glm::mat4 new_view(_viewMatrix);
		new_view[3][0] = 0.0f;
		new_view[3][1] = 0.0f;
		new_view[3][2] = 0.0f;
		SetMat4(m_viewMatrix, new_view);
	}
}}