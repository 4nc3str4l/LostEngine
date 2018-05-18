#pragma once

#include "Camera.h"
#include "../../Entities/Entity.h"

namespace Lost { namespace Gfx { 

using namespace Components;

class ThirdPersonCamera: public Camera
{
public:
	const float kMinPitch = 4.0f;
	const float kMaxPitch = 89.99f;

	// Max distance between the camera and the player
	const float kMinDistance = 20.0f;
	const float kMaxDistance = 50.0f;

	ThirdPersonCamera(Entity* _ship, glm::vec3 position = glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 0, float pitch = 20.0f);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch=true) override;
	void ProcessMouseScroll(float yoffset) override;
	void Tick(float _delta) override;
	void CalculateCameraPosition();
	void UpdateYaw();
	glm::mat4 GetViewMatrix();
private:
	float CalculateHorizontalDistance();
	float CalculateVerticalDistance();

public:
	Entity *entityToTrack;
private:
	float m_distanceFromPlayer = 35.0f;
	float m_angleArroundPlayer = 180.0f;
	float horizontalDistance;
	float verticalDistance;
};

}}