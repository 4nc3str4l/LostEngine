#include "PointLight.h"

namespace LostEngine { namespace Gfx {

PointLight::PointLight(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular, glm::vec3* position, float constant, float linear, float quadratic)
	: Light(ambient, diffuse, specular)
{
	Position = position;
	Constant = constant;
	Linear = linear;
	Quadratic = quadratic;
}


PointLight::~PointLight()
{
	delete Position;
}

}}