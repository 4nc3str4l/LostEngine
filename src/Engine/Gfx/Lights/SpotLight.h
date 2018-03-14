#pragma once
#include<glm/glm.hpp>
#include "PointLight.h"

namespace Lost { namespace Gfx {
class SpotLight : public PointLight
{
public:
	SpotLight(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular,
		glm::vec3* position, float constant, float linear, float quadratic,
		glm::vec3* direction, float cutoff, float outerCutoff);
	~SpotLight();
public:
	glm::vec3* Direction;
	float Cutoff;
	float OuterCutoff;
};
}}

