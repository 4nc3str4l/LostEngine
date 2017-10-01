#include "Light.h"

namespace LostEngine { namespace Gfx {

Light::Light(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular)
{
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
}

Light::~Light()
{
	delete Ambient;
	delete Diffuse;
	delete Specular;
}

}}