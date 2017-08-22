#pragma once
#include <glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public:
	// the program ID
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();


	// activate / deactivate shader
	void use();

	// Utility Functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};
