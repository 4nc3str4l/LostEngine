#pragma once
#include<glm/glm.hpp>

namespace le { namespace gfx {
class Light
{
public:
	Light(glm::vec3* ambient, glm::vec3* diffuse, glm::vec3* specular);
	virtual ~Light();

	glm::vec3* Ambient;
	glm::vec3* Diffuse;
	glm::vec3* Specular;
};
}}