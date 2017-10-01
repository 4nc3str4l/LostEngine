#pragma once
#include<glm/glm.hpp>
#include "Light.h"

namespace LostEngine { namespace Gfx {

class DirectionalLight : public Light
{
public:
	DirectionalLight(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular, glm::vec3* direction);
	~DirectionalLight();
public:
	glm::vec3* Direction;

};
}}



