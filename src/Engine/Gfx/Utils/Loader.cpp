#include "Loader.h"
#include<iostream>
#include<string>
#include "../../Tools/Log.h"

namespace le { namespace gfx {

using namespace tools;

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

RawModel* Loader::LoadToVAO(float* positions, int _posLength, float* textureCoords, int _textureLength, float* normals, int _normalsLength, int* indices, int _indicesLength) 
{
	int vaoID = CreateVAO();
	BindIndicesBuffer(indices, _indicesLength);
	StoreDataInAttributeList(0, 3, positions, _posLength);
	StoreDataInAttributeList(1, 2, textureCoords, _textureLength);
	StoreDataInAttributeList(2, 3, normals, _normalsLength);
	UnbindVAO();
	return new RawModel(vaoID, _indicesLength);
}

void Loader::BindIndicesBuffer(int* indices, int _indicesLength) {
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesLength * sizeof(int), indices, GL_STATIC_DRAW);
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
			LOG_FAIL("Could not load: " + path);
		}
	}
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	textures.push_back(textureID);

	return textureID;
}

GLuint Loader::LoadTexture(const std::string& _texturePath, int* _width, int* _heigth)
{

	GLuint textureID;
	int textureWidth;
	int textureHeigth;
	int& w = _width ? *_width : textureWidth;
	int& h = _heigth ? *_heigth : textureHeigth;

	// load and create a texture 
	// -------------------------
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int nrChannels;
	unsigned char *data = nullptr;

	if (_texturePath.find(".png") != std::string::npos)
	{
		data = stbi_load(_texturePath.c_str(), &w, &h, &nrChannels, STBI_rgb_alpha);
	}
	else
	{
		data = stbi_load(_texturePath.c_str(), &w, &h, &nrChannels, STBI_rgb);
	}
	if (data)
	{
		if (_texturePath.find(".png") != std::string::npos) 
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << _texturePath << std::endl;
	}
	stbi_image_free(data);
	return textureID;
}

GLuint Loader::CreateEmptyVBO(int maxNumOfFloats)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	vbos.push_back(VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//HACK: Not sure of GL_NONE
	glBufferData(GL_ARRAY_BUFFER, maxNumOfFloats * sizeof(float), GL_NONE,  GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VBO;
}

void Loader::AddInstancedAttributes(int _vao, int _vbo, int _attribute, int _dataSize, int _instancedDataLength, int _offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindVertexArray(_vao);
	glVertexAttribPointer(_attribute, _dataSize, GL_FLOAT, GL_FALSE, _instancedDataLength * 4, (void*)(_offset * 4));
	glVertexAttribDivisor(_attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Loader::UpdateVBO(GLuint _vbo, float* _data, int dataLength)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, dataLength * sizeof(float), GL_NONE, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataLength * 4,  _data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Loader::UnbindVAO() 
{
	glBindVertexArray(0);
}

}}