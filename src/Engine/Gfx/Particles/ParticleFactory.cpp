#include "ParticleFactory.h"
#include "ParticleMaster.h"

namespace Lost { namespace Gfx {
    
    const int INITIAL_STOCK = 200000;
	std::vector<Particle*>* ParticleFactory::avaliableParticles = new std::vector<Particle*>();
    void ParticleFactory::Initialize()
    {
        for(int i = 0; i < INITIAL_STOCK; i++)
        {
            avaliableParticles->push_back(new Particle());
        }
    }

    Particle* ParticleFactory::CreateParticle()
    {
		Particle* p;
        if(avaliableParticles->size() > 0)
        {
            p = avaliableParticles->back();
            avaliableParticles->pop_back();
        }
        else
        {
            p = new Particle();
        }
        return p; 
    }

    void ParticleFactory::RefundParticle(Particle* _p)
    {
        avaliableParticles->push_back(_p);
    }

    void ParticleFactory::Dispose()
    {
        for(int i = avaliableParticles->size() -1 ; i >= 0; i--)
        {
            delete avaliableParticles->at(i);
        }
		delete avaliableParticles;
    }

}}