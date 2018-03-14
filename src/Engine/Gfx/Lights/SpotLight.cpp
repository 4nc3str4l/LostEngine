 #include "SpotLight.h"

namespace Lost { namespace Gfx {

SpotLight::SpotLight(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular, glm::vec3* position, float constant, float linear, float quadratic, glm::vec3* direction, float cutoff, float outerCutoff) :
	PointLight(ambient, diffuse, specular, position, constant, linear, quadratic)
{
	Direction = direction;
	Cutoff = cutoff;
	OuterCutoff = outerCutoff;
}

SpotLight::~SpotLight()
{
}

}}