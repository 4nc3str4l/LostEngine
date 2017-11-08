#pragma once

#include <vector>
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
	void Render(std::vector<Particle*>* _particles, Camera* _camera);
private:
	void Prepare();
	void UpdateModelViewMatrix(glm::vec3* _position, float _rotation, float _scale, const glm::mat4& viewMatrix);
	void FinnishRendering();
private:
	static float vertices[8];
	RawModel* quad_;
	ParticleShader* shader_;
};

}}