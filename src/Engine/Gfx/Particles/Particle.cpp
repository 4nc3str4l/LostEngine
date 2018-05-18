#include "Particle.h"
#include "../../LostEngine.h"
#include "ParticleMaster.h"

namespace le { namespace gfx {

Particle::Particle()
{
	texOffset1 = new vec2();
	texOffset2 = new vec2();
    m_instantVelocity = new vec3();
	position = new vec3();
	m_velocity = new vec3();
}

void Particle::SetParticle(ParticleTexture * _texture, float posX, float posY, float posZ, float vX, float vY, float vZ, float _grav, float _life, float _rotation, float _scale)
{
	texture = _texture;
	position->x = posX;
	position->y = posY;
	position->z = posZ;

	m_velocity->x = vX;
	m_velocity->y = vY;
	m_velocity->z = vZ;

	rotation = _rotation;
	scale = _scale;
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
	distance = glm::length2(*_camera->Position - *position);
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