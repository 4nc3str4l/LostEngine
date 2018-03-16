#version 330 core

layout (location=0) in vec2 position;

out vec4 clipSpaceCoords;
out vec2 textureCoords;
out vec3 toCameravector;
out vec3 fromLightVector;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 plane;

const float tiling = 4.0;

void main(void) 
{
	vec4 worldPosition = modelMatrix * vec4(position.x, 0.0, position.y, 1.0);

	gl_ClipDistance[0] = -1;

	clipSpaceCoords = projectionMatrix * viewMatrix * worldPosition;
	gl_Position = clipSpaceCoords;
	textureCoords = vec2(position.x / 2.0 + 0.5, position.y / 2.0 + 0.5) * tiling;
	toCameravector = cameraPosition - worldPosition.xyz;
	fromLightVector = worldPosition.xyz - lightPosition;

}