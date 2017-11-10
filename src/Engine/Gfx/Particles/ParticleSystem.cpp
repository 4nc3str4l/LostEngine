#include "ParticleSystem.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "../../Tools/Timer.h"
#include "../../Tools/Maths.h"

namespace LostEngine { namespace Gfx {
using namespace Tools;

ParticleSystem::ParticleSystem(ParticleTexture* _texture, float _pps, float _speed, float _gravityComplient, float _lifeLength, float _scale)
{
	m_particleTexture = _texture;
    m_pps = _pps;
    m_averageSpeed = _speed;
    m_gravityComplient = _gravityComplient;
    m_averageLifeLength = _lifeLength;
    m_averageScale = _scale;
	transform = new Components::Transform(nullptr);
}

		
ParticleSystem::~ParticleSystem()
{
}

ParticleSystem* ParticleSystem::SetDirection(glm::vec3* _direction, float _deviation)
{
	m_direction = new glm::vec3(*_direction);
	m_directionDeviation = _deviation * M_PI;
	return this;
}

ParticleSystem* ParticleSystem::RandomizeRotation()
{
	m_randomRotation = true;
	return this;
}

ParticleSystem* ParticleSystem::SetSpeedError(float _error)
{
	m_speedError = _error;
	return this;
}

ParticleSystem* ParticleSystem::SetLifeEror(float _error)
{
	m_lifeError = _error;
	return this;
}

ParticleSystem* ParticleSystem::SetScaleError(float _error)
{
	m_scaleError = _error;
	return this;
}

void ParticleSystem::GenerateParticles(glm::vec3* _systemCenter)
{
	float delta = Timer::DeltaTime;
	float particlesToCreate = m_pps * delta;
	int count = (int)floor(particlesToCreate);
	float partialParticle = particlesToCreate - (int)particlesToCreate;
	for (int i = 0; i < count; i++)
	{
		EmitParticle(_systemCenter);
	}

	if (Maths::GetRandomFloat() < partialParticle)
	{
		EmitParticle(_systemCenter);
	}
}
		
void ParticleSystem::EmitParticle(glm::vec3* _center)
{
	glm::vec3* velocity = nullptr;
	if (m_direction != nullptr) {
		velocity = GenerateRandomUnitVectorWithinCone(m_direction, m_directionDeviation);
	}
	else {
		velocity = GenerateRandomUnitVector();
	}
	*velocity = glm::normalize(*velocity);
	(*velocity) *= GenerateValue(m_averageSpeed, m_speedError);
	float scale = GenerateValue(m_averageScale, m_scaleError);
	float lifeLength = GenerateValue(m_averageLifeLength, m_lifeError);
	new Particle(m_particleTexture, new glm::vec3(*_center), velocity, m_gravityComplient, lifeLength, GenerateRotation(), scale);
}

float ParticleSystem::GenerateValue(float _average, float _errorMargin)
{
	float offset = (Maths::GetRandomFloat() - 0.5f) * 2.0f * _errorMargin;
	return _average + offset;
}

float  ParticleSystem::GenerateRotation()
{
	if (m_randomRotation) {
		return Maths::GetRandomFloat(0, 360.0f);
	}
	else {
		return 0;
	}
}

glm::vec3* ParticleSystem::GenerateRandomUnitVectorWithinCone(glm::vec3 * _coneDirection, float _angle)
{
	float cosAngle = cos(_angle);
	float theta = (float)(Maths::GetRandomFloat() * 2.0f * M_PI);
	float z = cosAngle + (Maths::GetRandomFloat() * (1 - cosAngle));
	float rootOneMinusZSquared = sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));

	glm::vec4 direction = glm::vec4(x, y, z, 1.0f);
	if (_coneDirection->x != 0 || _coneDirection->y != 0 || (_coneDirection->z != 1 && _coneDirection->z != -1)) {
		glm::vec3 rotateAxis;
		rotateAxis = glm::cross(rotateAxis, glm::vec3(0, 1, 0));
		rotateAxis = glm::normalize(rotateAxis);
		float rotateAngle = acos(glm::dot(*_coneDirection, glm::vec3(0, 0, 1)));
		glm::mat4 rotationMatrix;
		rotationMatrix = glm::rotate(rotationMatrix , -rotateAngle, rotateAxis);
		direction = rotationMatrix * direction;
	}
	else if (_coneDirection->z == -1) {
		direction.z *= -1;
	}
	return new glm::vec3(direction);
}
glm::vec3* ParticleSystem::GenerateRandomUnitVector()
{
	float theta = (float)(Maths::GetRandomFloat() * 2.0f * M_PI);
	float z = (Maths::GetRandomFloat() * 2) - 1;
	float rootOneMinusZSquared = sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));
	return new glm::vec3(x, y, z);
}
}}
