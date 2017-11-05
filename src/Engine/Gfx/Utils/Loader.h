#pragma once

#include<vector>
#include "../Models/RawModel.h"
#include <glad/glad.h>
#include "../Utils/stb_image.h"

inline void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
        abort();
    }
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            glGetError(); \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif

namespace LostEngine { namespace Gfx {

class Loader
{
private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
	std::string* basePath;
public:
	Loader(const std::string& _basePath);
	~Loader();
	RawModel* LoadToVAO(float* positions, int dimensions, int _arraySize);
	GLuint CreateVAO();
    GLuint LoadCubeMap(std::string* textureFiles);
	GLuint LoadTexture(const std::string& _texturePath);
private:
	void StoreDataInAttributeList(int _attributeNumber, int _coordinateSize, float* _data, int _length);
};

}}
