#pragma once
#include "../Utils/Shader.h"
#include <string>

namespace LostEngine { namespace Gfx{
	class SkyboxShader
	{
	public:
		SkyboxShader(const std::string& base);
		~SkyboxShader();
		void BindAttributes();
		void LoadProjectionMatrix(const glm::mat4& _projectionMatrix);
		void LoadViewMatrix(const glm::mat4& _viewMatrix);

	public:
		Shader* shader;
	private:

	};
}}