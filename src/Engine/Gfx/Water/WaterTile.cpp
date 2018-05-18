#include "WaterTile.h"

namespace le { namespace water {

WaterTile::WaterTile(float _centerX, float _centerZ, float _height)
{
	X = _centerX;
	Z = _centerZ;
	Height = _height;
}

WaterTile::~WaterTile()
{
}

}}