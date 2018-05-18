#include "WaterShader.h"
#include "../../LostEngine.h"

using namespace tools;

namespace le { namespace water {

WaterShader::WaterShader() : Shader((FileSystem::basePath + "./resources/shaders/Water/water.vs").c_str(), (FileSystem::basePath + "./resources/shaders/Water/water.fs").c_str())
{
	m_viewMatrix = glGetUniformLocation(ID, "viewMatrix");
	m_projectionMatrix = glGetUniformLocation(ID, "projectionMatrix");
	m_modelMatrix = glGetUniformLocation(ID, "modelMatrix");

	m_reflectionTexture = glGetUniformLocation(ID, "reflectionTexture");
	m_refractionTexture = glGetUniformLocation(ID, "refractionTexture");
	m_dudvMap = glGetUniformLocation(ID, "dudvMap");
	m_normalMap = glGetUniformLocation(ID, "normalMap");
	m_depthMap = glGetUniformLocation(ID, "depthMap");
	m_cameraPosition = glGetUniformLocation(ID, "cameraPosition");
	m_moveFactor = glGetUniformLocation(ID, "moveFactor");
	m_lightPosition = glGetUniformLocation(ID, "lightPosition");
	m_lightColour = glGetUniformLocation(ID, "lightColour");

	m_near = glGetUniformLocation(ID, "near");
	m_far = glGetUniformLocation(ID, "far");
}

WaterShader::~WaterShader()
{
}

void WaterShader::LoadZNear(const float _zNear) const
{
    SetFloat(m_near, _zNear);
}

void WaterShader::LoadZFar(const float _zFar) const
{
	SetFloat(m_far, _zFar);
}

void WaterShader::BindAttributes()
{
	BindAttribute("position", 0);
}

void WaterShader::LoadProjectionMatrix(const glm::mat4& _projectionMatrix) const
{
	SetMat4(m_projectionMatrix, _projectionMatrix);
}

void WaterShader::LoadViewMatrix(const glm::mat4& _viewMatrix) const
{
	SetMat4(m_viewMatrix, _viewMatrix);
}

void WaterShader::LoadModelMatrix(const glm::mat4& _modelMatrix) const
{
	SetMat4(m_modelMatrix, _modelMatrix);
}

void WaterShader::LoadReflectionTexure()  const
{
	SetInt(m_reflectionTexture, 0);
}

void WaterShader::LoadRefractionTexture() const
{
	SetInt(m_refractionTexture, 1);
}

void WaterShader::LoadDudvMap() const
{
	SetInt(m_dudvMap, 2);
}

void WaterShader::LoadNormalMap() const
{
	SetInt(m_normalMap, 3);
}

void WaterShader::LoadDepthMap() const
{
	SetInt(m_depthMap, 4);
}

void WaterShader::LoadCameraPosition(const glm::vec3& _position) const
{
	SetVec3(m_cameraPosition, _position);
}

void WaterShader::LoadMoveFactor(float _factor) const
{
	SetFloat(m_moveFactor, _factor);
}

void WaterShader::LoadLightPosition(const glm::vec3& _position) const
{
	SetVec3(m_lightPosition, _position);
}

void WaterShader::LoadLightColour(const glm::vec3& _specularColour) const
{
	SetVec3(m_lightColour, _specularColour);
}

}}