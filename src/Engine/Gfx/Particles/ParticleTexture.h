#pragma once
#include <glad/glad.h>

namespace LostEngine { namespace Gfx {

class ParticleTexture
{
public:
	ParticleTexture(GLuint _textureID, int _numberOfRows);
	~ParticleTexture();
public:
	GLuint textureID;
	int numberOfRows;
};

}}