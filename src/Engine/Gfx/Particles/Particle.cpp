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
	texOffset1 = new vec2();
	texOffset2 = new vec2();
    m_instantVelocity = new vec3();

	ParticleMaster::AddParticle(this); 
}

void Particle::SetParticle(ParticleTexture * _texture, vec3 * _pos, vec3 * _vel, float _grav, float _life, float _rotation, float _scale)
{
	texture = _texture;
	position = _pos;
	rotation = _rotation;
	scale = _scale;
	m_velocity = _vel;
	m_gravityEffect = _grav;
	m_lifeLength = _life;

	m_elapsedTime = 0.0f;
	ParticleMaster::AddParticle(this);
}

Particle::~Particle()
{
	delete texOffset1;
	delete texOffset2;
	delete position;
	delete m_velocity;
	delete m_instantVelocity;
}

bool Particle::Tick(Camera* _camera)
{
    m_velocity->y += -9.8 * m_gravityEffect * Timer::DeltaTime;
    *m_instantVelocity = *m_velocity * Timer::DeltaTime;
	*position += *m_instantVelocity;
	distance = glm::length2(_camera->Position - *position);
	UpdateTextureCoordInfo();
    m_elapsedTime += Timer::DeltaTime;
    return m_elapsedTime < m_lifeLength;
}



void Particle::UpdateTextureCoordInfo()
{
	float lifeFactor = m_elapsedTime / m_lifeLength;
	int stageCount = texture->numberOfRows * texture->numberOfRows;
	float atlasProgression = lifeFactor * stageCount;
	int index1 = (int)floor(atlasProgression);
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;
	blend = atlasProgression - index1;
	SetTextureOffset(texOffset1, index1);
	SetTextureOffset(texOffset2, index2);
}

void Particle::SetTextureOffset(vec2 * _offset, int _index)
{
	int column = _index % texture->numberOfRows;
	int row = _index / texture->numberOfRows;
	_offset->x = (float)column / (float)texture->numberOfRows;
	_offset->y = (float)row / (float)texture->numberOfRows;
}


}}