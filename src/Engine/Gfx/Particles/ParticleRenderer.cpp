#include "ParticleRenderer.h"

namespace le { namespace gfx {
    
	const int MAX_INSTANCES =  70000;
	const int INSTANCE_DATA_LENGTH = 21;

	float ParticleRenderer::m_vertices[8]{ -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
	float ParticleRenderer::m_buffer[MAX_INSTANCES * INSTANCE_DATA_LENGTH];
	uint ParticleRenderer::m_bufferPointer = 0;

	ParticleRenderer::ParticleRenderer(Loader * _loader, const glm::mat4& _projectionMatrix)
	{
		m_loader = _loader;
		m_vbo = _loader->CreateEmptyVBO(INSTANCE_DATA_LENGTH * MAX_INSTANCES);
		m_quad = _loader->LoadToVAO(m_vertices, 2, 8);

		_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
		_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
		_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
		_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);
		_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 5, 4, INSTANCE_DATA_LENGTH, 16);
		_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 6, 1, INSTANCE_DATA_LENGTH, 20);


		m_shader = new ParticleShader();
		m_shader->Use();
		m_shader->SetProjectionMatrix(_projectionMatrix);
	}
	
	ParticleRenderer::~ParticleRenderer()
	{
		delete m_shader;
		delete m_quad;
	}

	void ParticleRenderer::Prepare()
	{
		m_shader->Use();
		glBindVertexArray(m_quad->VaoID);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);
		glEnableVertexAttribArray(6);

		glEnable(GL_BLEND);
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
		StoreMatrixData(modelViewMatrix);

	}

	void ParticleRenderer::StoreMatrixData(const glm::mat4& _matrix)
	{
		m_buffer[m_bufferPointer++] = _matrix[0][0];
		m_buffer[m_bufferPointer++] = _matrix[0][1];
		m_buffer[m_bufferPointer++] = _matrix[0][2];
		m_buffer[m_bufferPointer++] = _matrix[0][3];

		m_buffer[m_bufferPointer++] = _matrix[1][0];
		m_buffer[m_bufferPointer++] = _matrix[1][1];
		m_buffer[m_bufferPointer++] = _matrix[1][2];
		m_buffer[m_bufferPointer++] = _matrix[1][3];

		m_buffer[m_bufferPointer++] = _matrix[2][0];
		m_buffer[m_bufferPointer++] = _matrix[2][1];
		m_buffer[m_bufferPointer++] = _matrix[2][2];
		m_buffer[m_bufferPointer++] = _matrix[2][3];

		m_buffer[m_bufferPointer++] = _matrix[3][0];
		m_buffer[m_bufferPointer++] = _matrix[3][1];
		m_buffer[m_bufferPointer++] = _matrix[3][2];
		m_buffer[m_bufferPointer++] = _matrix[3][3];
	}

	void ParticleRenderer::UpdateTexCoordInfo(Particle* _particle)
	{
		m_buffer[m_bufferPointer++] = _particle->texOffset1->x;
		m_buffer[m_bufferPointer++] = _particle->texOffset1->y;
		m_buffer[m_bufferPointer++] = _particle->texOffset2->x;
		m_buffer[m_bufferPointer++] = _particle->texOffset2->y;
		m_buffer[m_bufferPointer++] = _particle->blend;
	}

	void ParticleRenderer::Render(std::map<ParticleTexture*, std::vector<Particle*>*>* _particles, Camera* _camera)
	{
		glm::mat4 viewMatrix = _camera->GetViewMatrix();
		Prepare();
		for (auto keyVal : *_particles)
		{
			ParticleTexture* tex = keyVal.first;
			std::vector<Particle*>* particleList = keyVal.second;
			BindTexture(tex);
			m_bufferPointer = 0;
			float size = particleList->size() * INSTANCE_DATA_LENGTH;
			for (Particle* particle : *particleList)
			{
				UpdateModelViewMatrix(particle->position, particle->rotation, particle->scale, viewMatrix);
				UpdateTexCoordInfo(particle);
			}
			m_loader->UpdateVBO(m_vbo, m_buffer, size);
			glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particleList->size());
		}
		FinnishRendering();
	}
	
	void ParticleRenderer::BindTexture(ParticleTexture* _particleTexture)
	{
		if (_particleTexture->usesAdditiveBlending) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}
		else {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _particleTexture->textureID);
		m_shader->SetNumberOfRows(_particleTexture->numberOfRows);
	}

	void ParticleRenderer::FinnishRendering()
	{
		glDepthMask(true);
		glDisable(GL_BLEND);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
		glDisableVertexAttribArray(5);
		glDisableVertexAttribArray(6);
		glBindVertexArray(0);
	}
}}
