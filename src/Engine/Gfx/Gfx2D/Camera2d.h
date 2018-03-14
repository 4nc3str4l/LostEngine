
#pragma once

#include "../../Entities/Entity.h"
#include "../Utils/Shader.h"
#include "../Utils/Window.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Lost { namespace Gfx2D {

using namespace Components;
using namespace Gfx;

class Camera2d : public Entity
{
public:
	Camera2d(Window* _window);
	~Camera2d();
	void Update(float _delta);
public:
	glm::mat4 Projection;
	glm::mat4 View;
};

}}