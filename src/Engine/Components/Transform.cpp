#include "Transform.h"

namespace le { namespace components {

Transform::Transform(Entity* _owner)
{
	entity = _owner;
	position = new glm::vec3(0, 0, 0);
	rotation = new glm::vec3(0, 0, 0);
	scale = new glm::vec3(1, 1, 1);
	model = new glm::mat4();
	forward = new glm::vec3(0, 0, 1);
	up = new glm::vec3(0, 0, 1);
	left = new glm::vec3(0, 0, 1);
	parent = nullptr;
}

Transform::~Transform()
{
	delete position;
	delete rotation;
	delete scale;
	delete model;
	delete forward;
	delete up;
	delete left;
	for (Transform* child : chilldren)
	{
		delete child->entity;
	}
}

const void Transform::ResetModelMatrix()
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
}

void Transform::CalcModelMatrix(Transform* _toCompute)
{
	*model = glm::translate(*model, *_toCompute->position);
	*model = glm::rotate(*model, glm::radians(_toCompute->rotation->x), glm::vec3(1, 0, 0));
	*model = glm::rotate(*model, glm::radians(_toCompute->rotation->y), glm::vec3(0, 1, 0));
	*model = glm::rotate(*model, glm::radians(_toCompute->rotation->z), glm::vec3(0, 0, 1));
	*model = glm::scale(*model, *_toCompute->scale);
}

glm::mat4* Transform::GetModelMatrix()
{
	ResetModelMatrix();

	if (HasParent()) 
	{
		// Populate the transformation stack
		std::stack<Transform*> transformStack;
		Transform* current = this;
		do 
		{
			transformStack.push(current);
			current = current->parent;
		} while (current != nullptr);

		do
		{
			CalcModelMatrix(transformStack.top());
			transformStack.pop();
		} while (!transformStack.empty());

	}
	else
	{
		CalcModelMatrix(this);
	}
	
	CalcForwardVector();
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

void Transform::SetParent(Transform* _newParent)
{
	_newParent->chilldren.push_back(this);
	parent = _newParent;
}

void Transform::Unparent()
{
	parent = nullptr;
}

void Transform::CalcForwardVector()
{
	forward->x = (*model)[0][2];
	forward->y = (*model)[1][2];
	forward->z = (*model)[2][2];

	up->x = (*model)[0][1];
	up->y = (*model)[1][1];
	up->z = (*model)[2][1];

	left->x = (*model)[0][0];
	left->y = (*model)[1][0];
	left->z = (*model)[2][0];
}

}}