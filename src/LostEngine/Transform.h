#pragma once

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Transform
{
public:
	Transform();
	~Transform();

public:
	glm::mat4 ModelMatrix;

private:
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
};

