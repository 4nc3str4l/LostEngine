#include "ParticleMaster.h"
#include "ParticleFactory.h"

namespace LostEngine { namespace Gfx {

std::map<ParticleTexture*, std::vector<Particle*>*>* ParticleMaster::m_particles = new std::map<ParticleTexture*, std::vector<Particle*>*>();
ParticleRenderer* ParticleMaster::renderer = nullptr;

void ParticleMaster::Init(Loader * _loader, const glm::mat4 & _projectionMatrix)
{
	ParticleFactory::Initialize();
	renderer = new ParticleRenderer(_loader, _projectionMatrix);
}

void ParticleMaster::Tick(Camera* _camera)
{
	for (std::map<ParticleTexture*, std::vector<Particle*>*>::iterator it = m_particles->begin(); it != m_particles->end(); it++)
	{
		ParticleTexture* tex = it->first;
		std::vector<Particle*>* vec = it->second;
		for (int i = vec->size() - 1; i >= 0; i--)
		{
			Particle* p = vec->at(i);
			if (!p->Tick(_camera))
			{
				ParticleFactory::RefundParticle(p);
				vec->erase(vec->begin() + i);
				if (vec->size() == 0)
				{
					m_particles->erase(p->texture);
					delete vec;
				}
			}
		}
		// Sort particles by distance
		if(!tex->usesAdditiveBlending)
			InsertionSort(vec);
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
			ParticleFactory::RefundParticle(p);
			particleList->erase(particleList->begin() + i);
		}
		delete particleList;
	}

	ParticleFactory::Dispose();
	delete renderer;
	delete m_particles;
}

void ParticleMaster::InsertionSort(std::vector<Particle*>* _data)
{
	int j;
	Particle *val;

	for (int i = 1; i < _data->size(); i++) {
		val = _data->at(i);
		j = i - 1;

		while (j >= 0 && _data->at(j)->distance > val->distance) {
			_data->at(j + 1) = _data->at(j);
			j = j - 1;
		}
		_data->at(j + 1) = val;
	}

}

}}