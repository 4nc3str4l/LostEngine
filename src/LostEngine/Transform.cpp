#include "Transform.h"

Transform::Transform()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetModelMatrix()
{
	// TODO: This matrix needs only to be calculated if the object is moved
	glm::mat4 model;
	model = glm::translate(model, Position);
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, Scale);
	return model;
}
