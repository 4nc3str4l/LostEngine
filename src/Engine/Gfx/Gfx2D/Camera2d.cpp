#include "Camera2d.h"

namespace Lost { namespace Gfx2D{

Camera2d::Camera2d(Window* _window) : Entity()
{
	Projection = glm::ortho(0.0f, static_cast<GLfloat>(_window->Width), static_cast<GLfloat>(_window->Heigth), 0.0f, -1.0f, 1.0f);
	View = glm::mat4(1.0f);
}

Camera2d::~Camera2d()
{
}

void Camera2d::Update(float _delta)
{
	if (Input::IsKeyPressed(GLFW_KEY_UP))
		View = glm::translate(View, glm::vec3(0, 1, 0));

	if (Input::IsKeyPressed(GLFW_KEY_DOWN))
		View = glm::translate(View, glm::vec3(0, -1, 0));

	if (Input::IsKeyPressed(GLFW_KEY_RIGHT))
		View = glm::translate(View, glm::vec3(-1, 0, 0));

	if (Input::IsKeyPressed(GLFW_KEY_LEFT))
		View = glm::translate(View, glm::vec3(1, 1, 0));
}

}}