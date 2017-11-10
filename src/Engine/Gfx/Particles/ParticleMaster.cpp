#include "ParticleMaster.h"

namespace LostEngine { namespace Gfx {

std::map<ParticleTexture*, std::vector<Particle*>*>* ParticleMaster::m_particles = new std::map<ParticleTexture*, std::vector<Particle*>*>();
ParticleRenderer* ParticleMaster::renderer = nullptr;

void ParticleMaster::Init(Loader * _loader, const glm::mat4 & _projectionMatrix)
{
	renderer = new ParticleRenderer(_loader, _projectionMatrix);
}

void ParticleMaster::Tick()
{
	for (std::map<ParticleTexture*, std::vector<Particle*>*>::iterator it = m_particles->begin(); it != m_particles->end(); it++)
	{
		ParticleTexture* tex = it->first;
		std::vector<Particle*>* vec = it->second;
		for (int i = vec->size() - 1; i >= 0; i--)
		{
			Particle* p = vec->at(i);
			if (!p->Tick())
			{
				delete p;
				vec->erase(vec->begin() + i);
				if (vec->size() == 0)
				{
					m_particles->erase(p->texture);
					delete vec;
				}
			}
		}
	}
}

void ParticleMaster::RenderParticles(Camera* _camera)
{
	renderer->Render(m_particles, _camera);
}

void ParticleMaster::AddParticle(Particle* _particle)
{
	if (m_particles->count(_particle->texture))
	{
		std::vector<Particle*>* particleList = m_particles->at(_particle->texture);
		particleList->push_back(_particle);
	}
	else
	{
		std::vector<Particle*>* particleVector = new std::vector<Particle*>();
		particleVector->push_back(_particle);
		m_particles->emplace(_particle->texture, particleVector);
	}
}

void ParticleMaster::Dispose()
{
	for (auto keyVal : *m_particles)
	{
		ParticleTexture* tex = keyVal.first;
		std::vector<Particle*>* particleList = keyVal.second;
		for (int i = particleList->size() - 1; i >= 0; i--)
		{
			Particle* p = particleList->at(i);
			delete p;
			particleList->erase(particleList->begin() + i);
		}
		delete particleList;
	}

	delete renderer;
	delete m_particles;
}

}}