#include "DirectionalLight.h"

namespace LostEngine { namespace Gfx {

DirectionalLight::DirectionalLight(glm::vec3* direction, glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular) :
	Light(ambient, diffuse, specular)
{
	Direction = direction;
}

DirectionalLight::~DirectionalLight()
{
	delete Direction;
}
}}
