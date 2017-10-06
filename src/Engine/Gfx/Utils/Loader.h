#pragma once
#include<vector>
#include "../Models/RawModel.h"
#include <glad/glad.h>

namespace LostEngine { namespace Gfx {

class Loader
{
private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
public:
	Loader();
	~Loader();
	RawModel* LoadToVAO(float* positions, int dimensions);
private:
	GLuint CreateVAO();
	void StoreDataInAttributeList(int _attributeNumber, int _coordinateSize, float* _data);
};

}}
