#include "Transform.h"

Transform::Transform()
{
	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

void Transform::UpdateModelMatrix()
{
	glm::mat4 m_ModelMatrix;
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
	m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));
	m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
}

void Transform::SetRotation(float _x, float _y, float _z)
{
	m_Rotation.x = _x;
	m_Rotation.y = _y;
	m_Rotation.z = _z;
	UpdateModelMatrix();
}

void Transform::SetPosition(float _x, float _y, float _z)
{
	m_Position.x = _x;
	m_Position.y = _y;
	m_Position.z = _z;
	UpdateModelMatrix();
}

void Transform::SetScale(float _x, float _y, float _z)
{
	m_Scale.x = _x;
	m_Scale.y = _y;
	m_Scale.z = _z;
	UpdateModelMatrix();
}

