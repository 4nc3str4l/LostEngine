#pragma once
#include "../Utils/Shader.h"
#include <string>

namespace LostEngine { namespace Gfx{
	class SkyboxShader : public Shader
	{
	public:
		SkyboxShader();
		~SkyboxShader();
		void BindAttributes();
		void LoadProjectionMatrix(const glm::mat4& _projectionMatrix);
		void LoadViewMatrix(const glm::mat4& _viewMatrix);
	private:
		GLuint m_projectionMatrix;
		GLuint m_viewMatrix;

	};
}}