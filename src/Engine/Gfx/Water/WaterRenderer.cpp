#include "WaterRenderer.h"
#include "../../LostEngine.h"

namespace le { namespace water {

WaterRenderer::WaterRenderer(Loader* _loader, WaterShader* _shader, const glm::mat4& _projectionMatrix, WaterFrameBuffer* _fbos)
{
	m_fbos = _fbos;
    Shader = _shader;
	m_dudvMap = _loader->LoadTexture(FileSystem::basePath + "/resources/textures/water/waterDUDV.png");
	m_NormalMap = _loader->LoadTexture(FileSystem::basePath + "/resources/textures/water/matchingNormalMap.png");

	Shader->Use();
	Shader->LoadProjectionMatrix(_projectionMatrix);
	Shader->LoadReflectionTexure();
	Shader->LoadRefractionTexture();
	Shader->LoadDudvMap();
	Shader->LoadNormalMap();
	Shader->LoadDepthMap();

	SetupVAO(_loader);
}

void WaterRenderer::Render(std::vector<WaterTile*>* _water, Camera* _camera, PointLight* _sun)
{
	prepareRenderer(_camera, _sun);
	for (WaterTile* tile : *_water) 
	{
		glm::mat4 modelMatrix;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(tile->X, tile->Height, tile->Z));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(WATER_TILE_SIZE, WATER_TILE_SIZE, WATER_TILE_SIZE));
		Shader->LoadModelMatrix(modelMatrix);
        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, Quad->VertexCount));
	}
	Unbind();
}

void WaterRenderer::prepareRenderer(Camera* _camera, PointLight* _sun)
{
	m_moveFactor += 1 * WAVE_SPEED * Timer::DeltaTime;

	m_moveFactor = m_moveFactor > 1 ? 0 : m_moveFactor;

	Shader->Use();
	Shader->LoadCameraPosition(*_camera->Position);
	Shader->LoadMoveFactor(m_moveFactor);
	Shader->LoadLightPosition(*_sun->Position);
	Shader->LoadLightColour(*_sun->Specular);
	
	Shader->LoadZNear(_camera->ZNear);
	Shader->LoadZFar(_camera->ZFar);

    auto viewMat = _camera->GetViewMatrix();
	Shader->LoadViewMatrix(viewMat);
    GL_CHECK(glBindVertexArray(Quad->VaoID));
    GL_CHECK(glEnableVertexAttribArray(0));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fbos->ReflectionTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_fbos->RefractionTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_dudvMap);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_NormalMap);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_fbos->RefractionDepthTexture);


	// used for soft edges alpha blending using water depth
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void WaterRenderer::Unbind()
{
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

float data[12] { -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };

void WaterRenderer::SetupVAO(Loader * _loader)
{
	Quad = _loader->LoadToVAO(data, 2, 12);
}

WaterRenderer::~WaterRenderer()
{
	
}

}}