#pragma once	

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>


namespace LostEngine { namespace Components {
class Entity; // Forward declaration of entity

class Transform
{
public:
	Transform(Entity* _owner);
	~Transform();
public:
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
	glm::vec3* forward;
	glm::vec3* up;
	glm::vec3* left;
	Transform* parent;
	std::vector<Transform*> chilldren;
	Entity* entity;
private:
	glm::mat4* model;
public:
	glm::mat4* GetModelMatrix();
	void SetPosition(float _x, float _y, float _z);
	void SetRotation(float _x, float _y, float _z);
	void SetScale(float _x, float _y, float _z);
	void SetParent(Transform* _newaParent);
	void Unparent();
	inline bool HasParent() const { return parent != nullptr; }
private:
	const void ResetModelMatrix();
	void CalcModelMatrix(Transform* _toCompute);
	void CalcForwardVector();
};
}}
