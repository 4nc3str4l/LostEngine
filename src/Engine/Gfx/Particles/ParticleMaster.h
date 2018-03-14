#pragma once

#include <map>
#include <vector>
#include "Particle.h"
#include "ParticleRenderer.h"

namespace Lost { namespace Gfx {


class ParticleMaster
{
public:
	static void Init(Loader* _loader, const glm::mat4& _projectionMatrix);
	static void Tick(Camera* _camera);
	static void RenderParticles(Camera* _camera);
	static void AddParticle(Particle* _particle);
	static void Dispose();
private:
	static std::map<ParticleTexture*, std::vector<Particle*>*>* m_particles;
	static ParticleRenderer* renderer;
	static void InsertionSort(std::vector<Particle*>* _data);
};


}}