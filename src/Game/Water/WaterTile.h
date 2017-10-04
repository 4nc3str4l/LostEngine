#pragma once

#define WATER_TILE_SIZE 60

class WaterTile
{
public:
	float Height;
	float X, Z;
public:

	WaterTile(float _centerX, float _centerZ, float height);
	~WaterTile();
};

