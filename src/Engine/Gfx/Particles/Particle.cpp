#include "Particle.h"
#include "../../LostEngine.h"
#include "ParticleMaster.h"

namespace LostEngine { namespace Gfx {
Particle::Particle(ParticleTexture* _texture, vec3* _pos, vec3* _vel, float _grav, float _life, float _rotation, float _scale)
{
	texture = _texture;
    position = _pos;
    rotation = _rotation;
    scale = _scale;
    m_velocity = _vel;
    m_gravityEffect = _grav;
    m_lifeLength = _life; 
    
    m_elapsedTime = 0.0f;
    m_instantVelocity = new vec3();

	ParticleMaster::AddParticle(this); 
}

Particle::~Particle()
{
	delete position;
	delete m_velocity;
	delete m_instantVelocity;
}

bool Particle::Tick()
{
    m_velocity->y += -9.8 * m_gravityEffect * Timer::DeltaTime;
    *m_instantVelocity = *m_velocity * Timer::DeltaTime;
	*position += *m_instantVelocity;
    m_elapsedTime += Timer::DeltaTime;
    return m_elapsedTime < m_lifeLength;
}

}}