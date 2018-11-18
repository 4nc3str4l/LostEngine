#pragma once

#include<iostream>

#include "../Gfx/Utils/Loader.h"
#include "SFML/Graphics.hpp"
#include "../Gfx/Utils/Shader.h"
#include "../Gfx/Utils/Window.h"
#include "../Components/Transform.h"
#include "../Components/RenderComponent.h"


namespace le { namespace ui {
using namespace gfx;
using namespace components;

class UIImage : public RenderComponent
{
public:
	UIImage(const char* _texturePath, Loader* _loader, Window* _window);
	UIImage(GLuint _textureID, Loader* _loader, Window* _window);
	~UIImage();
	void Render(le::gfx::Shader* _shader);

private:
	void CalcViewportProportion(Window* _window);
public:
	GLuint TextureID;
	Transform* transform;
	glm::vec3* color;
	int textureWidth;
	int textureHeigth;
private:
	Window* m_Window;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	glm::vec2* initialWindowProportion;
};
}}