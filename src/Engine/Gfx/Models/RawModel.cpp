#include "RawModel.h"

#include <iostream>
RawModel::RawModel(int _vaoID, int _vertexCount)
{
	VaoID = _vaoID;
	VertexCount = _vertexCount;
	std::cout << "VAO id :" << VaoID << std::endl;
}

RawModel::~RawModel()
{
}
