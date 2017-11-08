#include "ParticleRenderer.h"

namespace LostEngine { namespace Gfx {
	
	float ParticleRenderer::vertices[8]{ -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };

	ParticleRenderer::ParticleRenderer(Loader * _loader, const glm::mat4& _projectionMatrix)
	{
		quad_ = _loader->LoadToVAO(vertices, 2, 8);
		shader_ = new ParticleShader();
		shader_->Use();
		shader_->SetMat4("projectionMatrix", _projectionMatrix);
	}
	
	ParticleRenderer::~ParticleRenderer()
	{
		delete shader_;
		delete quad_;
	}

	void ParticleRenderer::Prepare()
	{
		shader_->Use();
		glBindVertexArray(quad_->VaoID);
		glEnableVertexAttribArray(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
	}

	void ParticleRenderer::UpdateModelViewMatrix(glm::vec3 * _position, float _rotation, float _scale, const glm::mat4& _viewMatrix)
	{
		glm::mat4 model;
		model = glm::translate(model, *_position);

		// Cancel the rotation but still getting the position on the 3d world (billboard)
		model[0][0] = _viewMatrix[0][0];
		model[0][1] = _viewMatrix[1][0];
		model[0][2] = _viewMatrix[2][0];
		model[1][0] = _viewMatrix[0][1];
		model[1][1] = _viewMatrix[1][1];
		model[1][2] = _viewMatrix[2][1];
		model[2][0] = _viewMatrix[0][2];
		model[2][1] = _viewMatrix[1][2];
		model[2][2] = _viewMatrix[2][2];

		model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0, 0, 1));
		model = glm::scale(model, glm::vec3(_scale));
		glm::mat4 modelViewMatrix = _viewMatrix * model;
		shader_->SetMat4("modelViewMatrix", modelViewMatrix);

	}

	void ParticleRenderer::Render(std::vector<Particle*>* _particles, Camera* _camera)
	{
		glm::mat4 viewMatrix = _camera->GetViewMatrix();
		Prepare();
		for (Particle* particle : *_particles)
		{
			UpdateModelViewMatrix(particle->position, particle->rotation, particle->scale, viewMatrix);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, quad_->VertexCount);
		}
		FinnishRendering();
	}
	
	void ParticleRenderer::FinnishRendering()
	{
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
}}
