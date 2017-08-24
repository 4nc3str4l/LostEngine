#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	Transform();
	~Transform();
	void SetRotation(float _x, float _y, float _z);
	void SetPosition(float _x, float _y, float _z);
	void SetScale(float _x, float _y, float _z);
private:
	void UpdateModelMatrix();
public:
	glm::mat4 m_ModelMatrix;
private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};

