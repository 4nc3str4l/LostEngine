#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../Models/RawModel.h"
#include "../Utils/Loader.h"
#include "WaterTile.h"
#include "WaterShader.h"
#include "WaterFrameBuffer.h"
#include "../Lights/PointLight.h"
#include "../Utils/Camera.h"

using namespace le;
using namespace gfx;

namespace le { namespace water {

//const float WAVE_SPEED = 0.06f;
const float WAVE_SPEED = 0.05f;

class WaterRenderer
{
private:
	RawModel* Quad;
	WaterShader* Shader;
	WaterFrameBuffer* m_fbos;
	GLuint m_NormalMap;
	GLuint m_dudvMap;
	float m_moveFactor = 0;


public:
	WaterRenderer(Loader* _loader, WaterShader* _shader, const glm::mat4& _projectionMatrix, WaterFrameBuffer* _fbos);
	~WaterRenderer();
	void Render(std::vector<WaterTile*>* _water, Camera* _camera, PointLight* _sun);

private:
	void prepareRenderer(Camera* _camera, PointLight* _sun);
	void Unbind();
	void SetupVAO(Loader* _loader);
};

}}