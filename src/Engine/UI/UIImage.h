#pragma once

#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Gfx/Utils/Loader.h"
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
	glm::mat4* model;
	GLuint TextureID;
private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	void CalcModelMatrix();
};
}}