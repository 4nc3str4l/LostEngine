#pragma once
#include <glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Texture
{
public:
	unsigned int ID;
	Texture(const GLchar* vertexPath, bool flipYOnload);
	~Texture();
	void use();
};

