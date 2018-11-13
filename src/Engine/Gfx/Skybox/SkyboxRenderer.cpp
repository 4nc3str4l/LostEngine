#include "SkyboxRenderer.h"

namespace le { namespace gfx {

	std::string skyboxNames[6] = {
		"bkg1_right.png",
		"bkg1_left.png",
		"bkg1_bot.png",
		"bkg1_top.png",
		"bkg1_back.png",
		"bkg1_front.png"
	};


	float SIZE = 500.0f;
	float skybox_vertices[] = {
		-SIZE,  SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,

		-SIZE, -SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,

		-SIZE,  SIZE, -SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE,  SIZE,  SIZE,
		SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE,  SIZE, -SIZE,

		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		SIZE, -SIZE,  SIZE
	};

	SkyboxRenderer::SkyboxRenderer(Loader* _loader, const glm::mat4& _projectionMatrix, const std::string& base)
	{
		cube = _loader->LoadToVAO(skybox_vertices, 3, 108);
		texture = _loader->LoadCubeMap(skyboxNames);
		skyboxShader = new SkyboxShader();
		skyboxShader->Use();
		skyboxShader->LoadProjectionMatrix(_projectionMatrix);
	}

	SkyboxRenderer::~SkyboxRenderer()
	{
		delete cube;
		delete skyboxShader;
	}

	void SkyboxRenderer::Render(Camera* _camera, Window* _window, const glm::mat4& _projection)
	{
		glDepthMask(GL_FALSE);
	
		skyboxShader->Use();
		skyboxShader->LoadViewMatrix(_camera->GetViewMatrix());

		glBindVertexArray(cube->VaoID);
		glEnableVertexAttribArray(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, cube->VertexCount);

		glDepthMask(GL_TRUE);
	}
}}