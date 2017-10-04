#pragma once
class RawModel
{
public:
	int VaoID;
	int VertexCount;
public:
	RawModel(int _vaoID, int _vertexCount);
	~RawModel();
};
