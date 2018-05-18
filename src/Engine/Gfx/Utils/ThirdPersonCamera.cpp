#include "ThirdPersonCamera.h"
#include "glm/glm.hpp"


namespace Lost { namespace Gfx { 
using namespace Tools;

ThirdPersonCamera::ThirdPersonCamera(Entity* _toTrack, glm::vec3 _position, glm::vec3 _up, float _yaw, float _pitch)
	: Camera(_position, _up, _yaw, _pitch)
{
	entityToTrack = _toTrack;
	Up = glm::vec3(0, 1, 0);
}

void ThirdPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	// Pitch
	if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) 
	{
		float pitchChange = yoffset * 0.1f;
		Pitch -= pitchChange;

		if (Pitch > kMaxPitch)
			Pitch = kMaxPitch;

		if (Pitch < kMinPitch)
			Pitch = kMinPitch;

		float angleChange = xoffset * 0.3f;
		m_angleArroundPlayer -= angleChange;
	}

	ProcessMouseScroll(Input::ScrollOffset);

}

void ThirdPersonCamera::ProcessMouseScroll(float yoffset)
{
	m_distanceFromPlayer -= yoffset;

	if (m_distanceFromPlayer > kMaxDistance)
		m_distanceFromPlayer = kMaxDistance;

	if (m_distanceFromPlayer < kMinDistance)
		m_distanceFromPlayer = kMinDistance;
}
   
void ThirdPersonCamera::Tick(float _delta)
{
	ProcessMouseMovement(0, 0, false);
	CalculateCameraPosition();
	UpdateYaw();
}

glm::mat4 ThirdPersonCamera::GetViewMatrix()
{
	return glm::lookAt(*Position, *entityToTrack->transform->position, Up);
}

float ThirdPersonCamera::CalculateHorizontalDistance()
{
	return  m_distanceFromPlayer * cos(glm::radians(Pitch));
}

float ThirdPersonCamera::CalculateVerticalDistance()
{
	return  m_distanceFromPlayer * sin(glm::radians(Pitch));
}

void ThirdPersonCamera::CalculateCameraPosition()
{
	horizontalDistance = CalculateHorizontalDistance();
	verticalDistance = CalculateVerticalDistance();
	float theta = entityToTrack->transform->rotation->y + m_angleArroundPlayer;
	float offsetX = horizontalDistance * sin(glm::radians(theta));
	float offsetZ = horizontalDistance * cos(glm::radians(theta));
	Position->x = entityToTrack->transform->position->x - offsetX;
	Position->z = entityToTrack->transform->position->z - offsetZ;
	Position->y = entityToTrack->transform->position->y + verticalDistance;
}

void ThirdPersonCamera::UpdateYaw()
{
	Yaw = 180.0f - entityToTrack->transform->rotation->y + m_angleArroundPlayer;
}

}}