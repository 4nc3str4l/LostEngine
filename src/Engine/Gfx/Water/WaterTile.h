#pragma once

namespace le { namespace water {

const int WATER_TILE_SIZE = 64;

class WaterTile
{
public:
	float Height;
	float X, Z;
public:
	WaterTile(float _centerX, float _centerZ, float height);
	~WaterTile();
};

}}