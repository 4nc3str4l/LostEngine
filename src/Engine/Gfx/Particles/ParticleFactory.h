#pragma once
#include<vector>
#include "Particle.h"

namespace LostEngine { namespace Gfx {
    class ParticleFactory
    {
    public:
        static void Initialize();
        static Particle* CreateParticle();
        static void RefundParticle(Particle* _p);
        static void Dispose();
    private:
        static std::vector<Particle*>* avaliableParticles;
    };
}}
