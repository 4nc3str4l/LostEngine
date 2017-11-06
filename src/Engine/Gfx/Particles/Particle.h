#pragma once
#include "../Utils/glad.h"
#include <glm/glm.hpp>

namespace LostEngine { namespace Gfx {
using namespace glm;

class Particle
{
public:
    Particle(vec3* _pos, vec3* _vel, float _grav, float _life, float _rotation, float _scale);
    ~Particle();
    bool Tick();
public:
    vec3* position;
    float rotation;
    float scale;
private:
    vec3* m_velocity;
    vec3* m_instantVelocity;
    float m_gravityEffect;
    float m_lifeLength;
    
    float m_elapsedTime;
};

}}
