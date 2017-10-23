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
	void SetPosition(float _x, float _y, float _z);
	void SetRotation(float _x, float _y, float _z);
	void SetScale(float _x, float _y, float _z);

private:
	glm::mat4* model;
};
}}
