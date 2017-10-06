#include "Loader.h"
#include<iostream>

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

void Loader::StoreDataInAttributeList(int _attributeNumber, int _coordinateSize, float* _data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float), &_data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(_attributeNumber, _coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

RawModel* Loader::LoadToVAO(float* positions, int dimensions)
{
	int vaoID = CreateVAO();
	StoreDataInAttributeList(0, dimensions, positions);
	
	// Unbind
	glBindVertexArray(0);
	return new RawModel(vaoID, 12);
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

}}