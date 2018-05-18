#include "Light.h"

namespace le { namespace gfx {

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