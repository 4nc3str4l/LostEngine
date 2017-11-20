#include "Camera.h"

namespace LostEngine { namespace Gfx {

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	Position = new glm::vec3(position);
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}
		
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	Position = new glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(*Position, *Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix(Window* _window)
{
    return glm::perspective(glm::radians(Zoom),(float)_window->Width/(float)_window->Heigth, 0.1f, 1000.0f); 
}
        
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	
	if (LostEngine::InputHandlers::Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		velocity *= 4;
	}

	if (direction == FORWARD)
		*Position += Front * velocity;
	if (direction == BACKWARD)
		*Position -= Front * velocity;
	if (direction == LEFT)
		*Position -= Right * velocity;
	if (direction == RIGHT)
		*Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Camera::Tick(float _delta)
{
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

glm::vec2 WordToScreenCoordinates(const glm::vec3& _coordinates, Window* _window)
{
    // TODO:(4nc3str4l): Don't compute those matrices all the time, try to cache them
    glm::mat4 view = GetViewMatrix();
    glm::mat4 projection = GetProjectionMatrix();
    glm::mat4 viewProjectionMatrix = projection * viewMatrix;
    // Transform world to clipping coordinates
    glm::vec3 point = _coordinates * viewProjectionMatrix;
    glm::vec2 screenPoint;
    screenPoint.x = round((point.x + 1) / 2.0f) * _window->Width);
        screenPoint.y = round((1 - point.y) / 2.0f) * _window->Heigth);
    return screenPoint;
}
        
Camera::~Camera()
{
	delete Position; 
}

}}
