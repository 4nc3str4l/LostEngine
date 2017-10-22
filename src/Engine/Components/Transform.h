#pragma once	

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LostEngine { namespace Components { 
class Transform
{
public:
	Transform();
	~Transform();

public:
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
	glm::mat4* GetModelMatrix();

private:
	glm::mat4* model;
};
}}
