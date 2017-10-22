#include "Loader.h"
#include<iostream>
#include<string>
#include "../../Tools/Log.h"

namespace LostEngine { namespace Gfx {

Loader::Loader(const std::string& _basePath)
{
	basePath = new std::string(_basePath);
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
	delete basePath;
}

void Loader::StoreDataInAttributeList(int _attributeNumber, int _coordinateSize, float* _data, int _length)
{
	GLuint vboID;
    GL_CHECK(glGenBuffers(1, &vboID));

	vbos.push_back(vboID);
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vboID));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _length, &_data[0], GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(_attributeNumber, _coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	glBindVertexArray(0);
}

RawModel* Loader::LoadToVAO(float* positions, int dimensions, int _length)
{
	int vaoID = CreateVAO();
	StoreDataInAttributeList(0, dimensions, positions, _length);
	
	// Unbind
    GL_CHECK(glBindVertexArray(0));
	return new RawModel(vaoID, _length);
}

GLuint Loader::CreateVAO()
{
	GLuint vaoID;
    GL_CHECK(glGenVertexArrays(1, &vaoID));
    GL_CHECK(glBindVertexArray(vaoID));
	vaos.push_back(vaoID);
	return vaoID;
}

GLuint Loader::LoadCubeMap(std::string* textureFiles)
{
	GLuint textureID;
	GL_CHECK(glGenTextures(1, &textureID));
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));


	for (int i = 0; i < 6; i++)
	{
		int width, height, nrComponents;
		std::string path = (*this->basePath) + "/resources/textures/Skybox/" + textureFiles[i];
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;
			GL_CHECK(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));

			// Free the texture data
			stbi_image_free(data);
		}
		else
		{
			Tools::LOG::FAIL("Could not load: " + path);
		}
	}
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	textures.push_back(textureID);

	return textureID;
}

}}