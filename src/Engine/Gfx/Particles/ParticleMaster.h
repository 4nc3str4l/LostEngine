#pragma once

#include <map>
#include <vector>
#include "Particle.h"
#include "ParticleRenderer.h"

namespace LostEngine { namespace Gfx {


class ParticleMaster
{
public:
	static void Init(Loader* _loader, const glm::mat4& _projectionMatrix);
	static void Tick();
	static void RenderParticles(Camera* _camera);
	static void AddParticle(Particle* _particle);
	static void Dispose();
private:
	static std::map<ParticleTexture*, std::vector<Particle*>*>* m_particles;
	static ParticleRenderer* renderer;
};


}}