#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include "../Models/RawModel.h"
#include "../Utils/Loader.h"
#include "../Utils/Camera.h"
#include "ParticleShader.h"
#include "Particle.h"

namespace LostEngine { namespace Gfx {

class ParticleRenderer
{
public:
	ParticleRenderer(Loader *_loader, const glm::mat4 &_projectionMatrix);
	virtual ~ParticleRenderer();
	void Render(std::map<ParticleTexture*, std::vector<Particle*>*>* _particles, Camera* _camera);
private:
	void Prepare();
	void UpdateModelViewMatrix(glm::vec3* _position, float _rotation, float _scale, const glm::mat4& viewMatrix);
	void FinnishRendering();
	void BindTexture(ParticleTexture* _particleTexture);
	void StoreMatrixData(const glm::mat4& _matrix);
	void UpdateTexCoordInfo(Particle* _particle);
private:
	static float m_vertices[8];
	static float m_buffer[];
	static uint m_bufferPointer;
	RawModel* m_quad;
	ParticleShader* m_shader;
	Loader* m_loader;
	GLuint m_vbo;
};

}}