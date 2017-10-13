#pragma once

#include<iostream>
#include "../Gfx/Utils/Loader.h"
#include <glm/glm.hpp>
#include "../Gfx/Utils/stb_image.h"
#include "../Gfx/Utils/Shader.h"
#include "../Gfx/Utils/Window.h"


namespace LostEngine { namespace UI {
using namespace Gfx;

class UIImage
{
public:
	UIImage(const char* _texturePath, Loader* _loader);
	~UIImage();
	void Render(Window* _window, Shader* _shader);
public:
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
	GLuint TextureID;
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
};
}}