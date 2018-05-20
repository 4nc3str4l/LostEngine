#pragma once

#include "ImageRenderer.h"
#include "ContrastShader.h"

namespace le { namespace gfx {

class ContrastChanger
{
public:
	ContrastChanger(float _ammount);
	~ContrastChanger();
	void render(GLuint _texture);
private:
	ImageRenderer *renderer;
	ContrastShader *shader;
};

}}