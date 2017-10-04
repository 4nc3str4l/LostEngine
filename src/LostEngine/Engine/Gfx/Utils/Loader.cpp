#include "Loader.h"


namespace LostEngine { namespace Gfx {

Loader::Loader()
{

}

Loader::~Loader()
{
	for (GLuint vao : vaos) 
	{
		glDeleteVertexArrays(1, &vao);
	}

	for (GLuint vbo : vbos) 
	{
		glDeleteBuffers(1, &vbo);
	}

	for (GLuint texture : textures) 
	{
		glDeleteTextures(1, &texture);
	}
}

RawModel* Loader::LoadToVAO(float* positions, int dimensions)
{
	int vaoID = CreateVAO();
	return nullptr;
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

}}