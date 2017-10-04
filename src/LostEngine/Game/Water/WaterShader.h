#pragma once
#include <glm/glm.hpp>
#include "../../Engine/Gfx/Utils/Shader.h"
#include "../../Engine/Gfx/Utils/Camera.h"

class WaterShader
{
public:
	LostEngine::Gfx::Shader* Shader;

public:
	WaterShader();
	~WaterShader();

	void BindAttributes();
	void LoadProjectionMatrix(glm::mat4* _projectionMatrix);
	void LoadViewMatrix(glm::mat4* _viewMatrix);
	void LoadModelMatrix(glm::mat4* _modelMatrix);
};

