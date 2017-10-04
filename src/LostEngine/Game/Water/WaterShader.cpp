#include "WaterShader.h"

WaterShader::WaterShader()
{
	Shader = new LostEngine::Gfx::Shader("./shaders/water.vs", "./shaders/water.vs");
}


WaterShader::~WaterShader()
{
}

void WaterShader::BindAttributes()
{
	Shader->BindAttribute("position", 0);
}

void WaterShader::LoadProjectionMatrix(glm::mat4 * _projectionMatrix)
{
	Shader->SetMat4("projectionMatrix", *_projectionMatrix);
}

void WaterShader::LoadViewMatrix(glm::mat4 * _viewMatrix)
{
	Shader->SetMat4("viewMatrix", *_viewMatrix);
}

void WaterShader::LoadModelMatrix(glm::mat4 * _modelMatrix)
{
	Shader->SetMat4("modelMatrix", *_modelMatrix);
}
