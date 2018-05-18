#include "ParticleTexture.h"

namespace le { namespace gfx {

ParticleTexture::ParticleTexture(GLuint _textureID, int _numberOfRows, bool _additive)
{
	textureID = _textureID;
	numberOfRows = _numberOfRows;
	usesAdditiveBlending = _additive;
}

ParticleTexture::~ParticleTexture()
{
}

}}