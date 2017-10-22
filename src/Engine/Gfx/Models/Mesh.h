#pragma once

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>,
#include <vector>

namespace LostEngine { namespace Gfx {

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
	aiString path;
};

class Mesh {
public:
	
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(LostEngine::Gfx::Shader shader);

private:
	unsigned int VBO, EBO;
	void setupMesh();
};
}}