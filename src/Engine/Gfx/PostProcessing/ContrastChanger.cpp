#include "ContrastChanger.h"
#include "../Utils/Window.h"

namespace le { namespace gfx {
	
ContrastChanger::ContrastChanger(float _ammount)
{
	shader = new ContrastShader();
	shader->Use();
	shader->SetFloat("contrast", _ammount);
	renderer = new ImageRenderer();
}

void ContrastChanger::render(GLuint _texture)
{
	shader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);
	renderer->renderQuad();
}

ContrastChanger::~ContrastChanger()
{
	delete renderer;
	delete shader;
}
}}