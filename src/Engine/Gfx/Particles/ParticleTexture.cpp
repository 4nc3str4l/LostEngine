#include "ParticleTexture.h"

namespace LostEngine { namespace Gfx {

ParticleTexture::ParticleTexture(GLuint _textureID, int _numberOfRows)
{
	textureID = _textureID;
	numberOfRows = _numberOfRows;
}

ParticleTexture::~ParticleTexture()
{
}

}}