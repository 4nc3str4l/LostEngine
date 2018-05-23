#include "HeightsGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <assert.h>

namespace le { namespace gfx {

int HeightsGenerator::getRandomNumberBetween(int _min, int _max) 
{
	return _min + (rand() % static_cast<int>(_max - _min + 1));
}

HeightsGenerator::HeightsGenerator() 
{
	m_Seed = getRandomNumberBetween(0, 1000000000);
}

HeightsGenerator::HeightsGenerator(int _gridX, int _gridZ, int _vertexCount, int _seed)
{
	assert(_gridX > 0 && _gridZ > 0);
	m_Seed = _seed;
	m_XOffset = _gridX * (_vertexCount - 1);
	m_ZOffset = _gridZ * (_vertexCount - 1);
}

float HeightsGenerator::generateHeight(int _x, int _z)
{
	float total = 0;
	float d = pow(2, OCTAVES - 1);
	for (int i = 0; i < OCTAVES; i++) {
		float freq = (float)(pow(2, i) / d);
		float amp = (float)pow(ROUGHNESS, i) * AMPLITUDE;
		total += getInterpolatedNoise((_x + m_XOffset)*freq, (_z + m_ZOffset)*freq) * amp;
	}
	return total;
}

float HeightsGenerator::getInterpolatedNoise(float _x, float _z)
{
	int intX = (int)_x;
	int intZ = (int)_z;
	float fracX = _x - intX;
	float fracZ = _z - intZ;

	float v1 = getSmoothNoise(intX, intZ);
	float v2 = getSmoothNoise(intX + 1, intZ);
	float v3 = getSmoothNoise(intX, intZ + 1);
	float v4 = getSmoothNoise(intX + 1, intZ + 1);
	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}

float HeightsGenerator::interpolate(float _a, float _b, float _blend)
{
	double theta = _blend * M_PI;
	float f = (float)(1.0f - cos(theta)) * 0.5f;
	return _a * (1.0f - f) + _b * f;
}

float HeightsGenerator::getSmoothNoise(int _x, int _z)
{
	float corners = (getNoise(_x - 1, _z - 1) + getNoise(_x + 1, _z - 1) + getNoise(_x - 1, _z + 1)
		+ getNoise(_x + 1, _z + 1)) / 16.0f;
	float sides = (getNoise(_x - 1, _z) + getNoise(_x + 1, _z) + getNoise(_x, _z - 1)
		+ getNoise(_x, _z + 1)) / 8.0f;
	float center = getNoise(_x, _z) / 4.0f;
	return corners + sides + center;
}

float HeightsGenerator::getNoise(int _x, int _z)
{
	srand(_x * 49632 + _z * 325176 + m_Seed);
	return rand()  * 2.0f - 1.0f;
}
}}