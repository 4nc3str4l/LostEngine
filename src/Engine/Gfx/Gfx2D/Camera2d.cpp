#include "Camera2d.h"

namespace le { namespace gfx2d{

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
	if (Input::IsKeyPressed(sf::Keyboard::Up))
		View = glm::translate(View, glm::vec3(0, 1, 0));

	if (Input::IsKeyPressed(sf::Keyboard::Down))
		View = glm::translate(View, glm::vec3(0, -1, 0));

	if (Input::IsKeyPressed(sf::Keyboard::Right))
		View = glm::translate(View, glm::vec3(-1, 0, 0));

	if (Input::IsKeyPressed(sf::Keyboard::Left))
		View = glm::translate(View, glm::vec3(1, 1, 0));
}

}}