#include "Shader.h"
#include "Loader.h"

namespace LostEngine { namespace Gfx {
	
	Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath /*= nullptr*/)
	{
        std::cout << "Building Shader: " << vertexPath << std::endl;
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			
			vShaderFile.close();
			fShaderFile.close();
			
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		
		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");
		
		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			const char * gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			CheckCompileErrors(geometry, "GEOMETRY");
		}
		
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);

		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");

		// As the shaders are already linked it will be no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);

	}

	void Shader::Use() 
	{
        GL_CHECK(glUseProgram(ID));
	}

	void Shader::SetBool(const std::string &name, bool value) const
	{
        GL_CHECK(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
	}
	
	void Shader::SetInt(const std::string &name, int value) const
	{
        GL_CHECK(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
	}
	
	void Shader::SetFloat(const std::string &name, float value) const
	{
        GL_CHECK(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
	}
	
	void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
	{
        GL_CHECK(glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]));
	}
	
	void Shader::SetVec2(const std::string &name, float x, float y) const
	{
        GL_CHECK(glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y));
	}
	
	void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
	{
        GL_CHECK(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]));
	}
	
	void Shader::SetVec3(const std::string &name, glm::vec3 &value) const
	{
        GL_CHECK(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]));
	}
	
	void Shader::SetVec3(const std::string &name, float x, float y, float z) const
	{
        GL_CHECK(glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z));
	}
	
	void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
	{
        GL_CHECK(glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]));
	}
	
	void Shader::SetVec4(const std::string &name, float x, float y, float z, float w)
	{
        GL_CHECK(glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w));
	}
	
	void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
	{
        GL_CHECK(glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
	}
	
	void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
	{
        GL_CHECK(glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
	}
	
	void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
	{
        GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
	}

	void Shader::BindAttribute(const std::string &_name, const int _attribute) const
	{
        GL_CHECK(glBindAttribLocation(ID, _attribute, _name.c_str()));
	}

	void Shader::CheckCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
            GL_CHECK(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
			if (!success)
			{
                GL_CHECK(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
            GL_CHECK(glGetProgramiv(shader, GL_LINK_STATUS, &success));
			if (!success)
			{
                GL_CHECK(glGetProgramInfoLog(shader, 1024, NULL, infoLog));
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}}