#pragma once

#include<glm/glm.hpp>
#include "Light.h"

namespace Lost { namespace Gfx {

class PointLight : public Light
{
public:
	PointLight(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular, glm::vec3* position, float constant, float linear, float quadratic);
	virtual ~PointLight();
public:
	glm::vec3* Position;
	float Constant;
	float Linear;
	float Quadratic;
};

}}
