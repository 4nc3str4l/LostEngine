#pragma once
#include <glm/glm.hpp>
#include "../Utils/Shader.h"
#include "../Utils/Camera.h"

namespace le { namespace water {

using namespace gfx;
class WaterShader : public Shader
{
public:
	WaterShader();
	~WaterShader();

	void BindAttributes();
	void LoadProjectionMatrix(const glm::mat4& _projectionMatrix) const;
	void LoadViewMatrix(const glm::mat4& _viewMatrix)  const;
	void LoadModelMatrix(const glm::mat4& _modelMatrix)  const;

	void LoadReflectionTexure() const;
	void LoadRefractionTexture() const;
	void LoadDudvMap() const;
	void LoadNormalMap() const;
	void LoadDepthMap() const;

	void LoadCameraPosition(const glm::vec3& _position)  const;
	void LoadMoveFactor(float _factor)  const;
	void LoadLightPosition(const glm::vec3& _position)  const;
	void LoadLightColour(const glm::vec3& _specularColour)  const;

	void LoadZNear(const float _zNear) const;
	void LoadZFar(const float _zFar) const;

private:
	GLuint m_viewMatrix;
	GLuint m_projectionMatrix;
	GLuint m_modelMatrix;

	GLuint m_reflectionTexture;
	GLuint m_refractionTexture;
	GLuint m_dudvMap;
	GLuint m_normalMap;
	GLuint m_depthMap;
	GLuint m_cameraPosition;
	GLuint m_moveFactor;
	GLuint m_lightPosition;
	GLuint m_lightColour;

	GLuint m_near;
	GLuint m_far;
};

}}