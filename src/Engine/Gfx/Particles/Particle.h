#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "ParticleTexture.h"
#include "../Utils/Camera.h"

namespace le { namespace gfx {
using namespace glm;

class Particle
{
public:
    Particle();
    Particle(ParticleTexture* _texture, vec3* _pos, vec3* _vel, float _grav, float _life, float _rotation, float _scale);
	~Particle();
    bool Tick(Camera* _camera);
	void SetParticle(ParticleTexture * _texture, float posX, float posY, float posZ, float vX, float vY, float vZ, float _grav, float _life, float _rotation, float _scale);
private:
	void UpdateTextureCoordInfo();
	void SetTextureOffset(vec2* _offset, int _index);
public:
    vec3 *position;
	vec2 *texOffset1;
	vec2 *texOffset2;
	float blend;
    float rotation;
    float scale;
	ParticleTexture* texture;
	float distance;
private:

    vec3 *m_velocity;
    vec3 *m_instantVelocity;
    float m_gravityEffect;
    float m_lifeLength;
    float m_elapsedTime;
};

}}
