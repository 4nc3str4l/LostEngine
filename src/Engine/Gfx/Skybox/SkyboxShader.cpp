#include "SkyboxShader.h"

namespace LostEngine { namespace Gfx {
   
	SkyboxShader::SkyboxShader(const std::string& base)
	{
		shader = new Shader((base + "./resources/shaders/skybox.vs").c_str(), (base + "./resources/shaders/skybox.fs").c_str());
	}

	SkyboxShader::~SkyboxShader()
	{
		delete shader;
	}

	void SkyboxShader::BindAttributes()
	{
		shader->BindAttribute("position", 0);
	}

	void SkyboxShader::LoadProjectionMatrix(const glm::mat4& _projectionMatrix)
	{
		shader->SetMat4("projectionMatrix", _projectionMatrix);
	}

	void SkyboxShader::LoadViewMatrix(const glm::mat4& _viewMatrix)
	{
		glm::mat4 new_view(_viewMatrix);
		new_view[3][0] = 0.0f;
		new_view[3][1] = 0.0f;
		new_view[3][2] = 0.0f;
		shader->SetMat4("viewMatrix", new_view);
	}
}}