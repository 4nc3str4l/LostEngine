#include "Transform.h"

namespace LostEngine { namespace Components {

Transform::Transform()
{
	position = new glm::vec3(0, 0, 0);
	rotation = new glm::vec3(0, 0, 0);
	scale = new glm::vec3(1, 1, 1);
	model = new glm::mat4();
}

Transform::~Transform()
{
	delete position;
	delete rotation;
	delete scale;
	delete model;
}

glm::mat4* Transform::GetModelMatrix()
{
	(*model)[0][0] = 1.0f;
	(*model)[1][0] = 0.0f;
	(*model)[2][0] = 0.0f;
	(*model)[3][0] = 0.0f;

	(*model)[0][1] = 0.0f;
	(*model)[1][1] = 1.0f;
	(*model)[2][1] = 0.0f;
	(*model)[3][1] = 0.0f;

	(*model)[0][2] = 0.0f;
	(*model)[1][2] = 0.0f;
	(*model)[2][2] = 1.0f;
	(*model)[3][2] = 0.0f;

	(*model)[0][3] = 0.0f;
	(*model)[1][3] = 0.0f;
	(*model)[2][3] = 0.0f;
	(*model)[3][3] = 1.0f;

	*model = glm::translate(*model, *this->position);
	*model = glm::rotate(*model, this->rotation->x, glm::vec3(1, 0, 0));
	*model = glm::rotate(*model, this->rotation->y, glm::vec3(0, 1, 0));
	*model = glm::rotate(*model, this->rotation->z, glm::vec3(0, 0, 1));
	*model = glm::scale(*model, *this->scale);
	return model;
}

void Transform::SetPosition(float _x, float _y, float _z)
{
	position->x = _x;
	position->y = _y;
	position->z = _z;
}

void Transform::SetRotation(float _x, float _y, float _z)
{
	rotation->x = _x;
	rotation->y = _y;
	rotation->z = _z;
}

void Transform::SetScale(float _x, float _y, float _z)
{
	scale->x = _x;
	scale->y = _y;
	scale->z = _z;
}

}}