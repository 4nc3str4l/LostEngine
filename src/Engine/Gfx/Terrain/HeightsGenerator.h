#pragma once

namespace le { namespace gfx {

class HeightsGenerator 
{
public:
	HeightsGenerator();
	HeightsGenerator(int _gridX, int _gridZ, int _vertexCount, int _seed);
	float generateHeight(int _x, int _z);

private:
	float getInterpolatedNoise(float _x, float _z);
	float interpolate(float _a, float _b, float _blend);
	float getSmoothNoise(int _x, int _z);
	float getNoise(int _x, int _z);
	int getRandomNumberBetween(int _min, int _max);

private:
	const float AMPLITUDE = 75.0f;
	const  int OCTAVES = 3;
	const  float ROUGHNESS = 0.3f;

	int m_Seed;
	int m_XOffset = 0;
	int m_ZOffset = 0;

};

}}