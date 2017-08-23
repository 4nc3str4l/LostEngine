#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	Transform();
	~Transform();
	glm::mat4 GetModelMatrix();
public:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

};

