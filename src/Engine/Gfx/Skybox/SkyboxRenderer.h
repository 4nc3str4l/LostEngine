#pragma once
#include <string>
#include "../Utils/Window.h"
#include "../Utils/Loader.h"
#include "../Models/RawModel.h"
#include "SkyboxShader.h"
#include "../Utils/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace le { namespace gfx {
	class SkyboxRenderer
	{
	public:
		SkyboxRenderer(Loader* _loader, const glm::mat4& _projectionMatrix, const std::string& base);
		~SkyboxRenderer();
		void Render(Camera* _camera, Window* _window, const glm::mat4& _projection);
		SkyboxShader* skyboxShader;
	private:
		RawModel* cube;
		GLuint texture;
	};
}}