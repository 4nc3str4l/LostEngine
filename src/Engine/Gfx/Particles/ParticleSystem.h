#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ParticleTexture.h"
#include "Particle.h"
#include "../../Components/Transform.h"

namespace LostEngine {  namespace Gfx {
class ParticleSystem
{
public:
    ParticleSystem(ParticleTexture* _texture, float _pps, float _speed, float _gravityComplient, float _lifeLength, float _scale);
    ~ParticleSystem();
	ParticleSystem* SetDirection(glm::vec3* _direction, float _deviation);
	ParticleSystem* RandomizeRotation();
	ParticleSystem* SetSpeedError(float _error);
	ParticleSystem* SetLifeEror(float _error);
	ParticleSystem* SetScaleError(float _error);
    void GenerateParticles(glm::vec3* _systemCenter);
private:
    void EmitParticle(glm::vec3* _center);
	float GenerateValue(float _average, float _errorMargin);
	float GenerateRotation();
	glm::vec3* GenerateRandomUnitVectorWithinCone(glm::vec3* coneDirection, float angle);
	glm::vec3* GenerateRandomUnitVector();

public:
	Components::Transform* transform;
private:
            
    float m_pps;
    float m_averageSpeed;
    float m_gravityComplient;
    float m_averageLifeLength;
    float m_averageScale;
    float m_speedError = 0;
    float m_lifeError = 0;
    float m_scaleError = 0;

    bool m_randomRotation = false;
    float m_directionDeviation;
	glm::vec3* m_direction = nullptr;
            
    ParticleTexture* m_particleTexture;
};
}}
