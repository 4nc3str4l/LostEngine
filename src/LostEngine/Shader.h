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
	void setBool(const std::string &_name, bool _value) const;
	void setInt(const std::string &_name, int _value) const;
	void setFloat(const std::string &_name, float _value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

