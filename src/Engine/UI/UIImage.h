#pragma once

#include<iostream>

#include "../Gfx/Utils/Loader.h"
#include "../Gfx/Utils/stb_image.h"
#include "../Gfx/Utils/Shader.h"
#include "../Gfx/Utils/Window.h"
#include "../Components/Transform.h"


namespace LostEngine { namespace UI {
using namespace Gfx;
using namespace Components;

class UIImage
{
public:
	UIImage(const char* _texturePath, Loader* _loader, Window* _window);
	UIImage(GLuint _textureID, Loader* _loader);
	~UIImage();
	void Render(Window* _window, Shader* _shader);

private:
	void CalcViewportProportion(Window* _window);
public:
	GLuint TextureID;
	Transform* transform;
	glm::vec3* color;
	int textureWidth;
	int textureHeigth;
private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	glm::vec2* initialWindowProportion;
};
}}