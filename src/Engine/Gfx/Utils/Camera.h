#pragma once

#include "../../Input/Input.h"
#include "Window.h"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


namespace le { namespace gfx { 
	
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVTY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera
	{

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, const float _zNear = 0.1f, const float _zFar = 1000.0f);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, const float _zNear, const float _zFar);
		virtual ~Camera();
		virtual glm::mat4 GetViewMatrix();
        virtual glm::mat4 GetProjectionMatrix(Window* _window);
		virtual void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		virtual void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		virtual void ProcessMouseScroll(float yoffset);
		virtual void Tick(float _delta);
        glm::vec2 WordToScreenCoords(const glm::vec3& _coordinates, Window* _window);
        glm::vec3 ScreenToWorldCoords(const glm::vec2& _coordinates, Window* _window);
	protected:
		virtual void updateCameraVectors();

	public:

		glm::vec3* Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		float Yaw;
		float Pitch;

		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;
		
		float ZNear;
		float ZFar;
	};
}}

