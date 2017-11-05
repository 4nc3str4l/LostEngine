#pragma once
#include<glm/glm.hpp>
#include "../../Engine/Gfx/Models/RawModel.h"
#include "../../Engine/Gfx/Utils/Loader.h"
#include "WaterShader.h"
#include "WaterFrameBuffer.h"

using namespace LostEngine;
using namespace Gfx;
class WaterRenderer
{
private:
	RawModel* quad;
	WaterShader* shader;

public:
	WaterRenderer(Loader* _loader, WaterShader* _shader, glm::mat4* _projectionMatrix);
	~WaterRenderer();
};

