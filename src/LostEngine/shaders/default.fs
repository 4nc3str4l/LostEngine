#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPosition;

uniform vec3 lightPosition;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
	vec3 lightDirection = normalize(lightPosition - FragPosition);

	// Ambient Lighting
	float ambientIntensity = 0.1f;
	vec3 ambientLight = ambientIntensity * lightColor;

	// Difuse lighting
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuseLight = diff * lightColor;

	// Specular lighting
	float shininess = 128;
	float specularIntensity = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPosition);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float specularity = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specularLight = specularIntensity * specularity * lightColor;

	//  Resulting lighting
	vec3 finalLight = (ambientLight + diffuseLight + specularLight) * objectColor;

	// Final fragment color
	FragColor = vec4(finalLight, 1.0);
}