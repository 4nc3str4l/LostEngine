#include "ParticleMaster.h"

namespace LostEngine { namespace Gfx {

std::vector<Particle*>* ParticleMaster::particles = new std::vector<Particle*>();
ParticleRenderer* ParticleMaster::renderer = nullptr;

void ParticleMaster::Init(Loader * _loader, const glm::mat4 & _projectionMatrix)
{
	renderer = new ParticleRenderer(_loader, _projectionMatrix);
}

void ParticleMaster::Tick()
{
	for (int i = particles->size() - 1; i >= 0; i--)
	{
		Particle* p = particles->at(i);
		if (!p->Tick())
		{
			delete p;
			particles->erase(particles->begin() + i);
		}
	}
}

void ParticleMaster::RenderParticles(Camera* _camera)
{
	renderer->Render(particles, _camera);
}

void ParticleMaster::AddParticle(Particle* _particle)
{
	particles->push_back(_particle);
}

void ParticleMaster::Dispose()
{
	for (int i = particles->size() - 1; i >= 0; i--)
	{
		Particle* p = particles->at(i);
		delete p;
		particles->erase(particles->begin() + i);
	}
	delete renderer;
	delete particles;
}

}

}