#pragma once
#include <glad/glad.h>

namespace LostEngine { namespace Gfx {

class ParticleTexture
{
public:
	ParticleTexture(GLuint _textureID, int _numberOfRows, bool _additive);
	~ParticleTexture();
public:
	GLuint textureID;
	int numberOfRows;
	bool usesAdditiveBlending;
};

}}