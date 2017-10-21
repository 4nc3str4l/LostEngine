#include "UIImage.h"

namespace LostEngine { namespace UI {

float vertices[] = {
	// positions          // colors           // texture coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

UIImage::UIImage(const char* _texturePath, Loader* _loader)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// load and create a texture 
	// -------------------------
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	
	unsigned char *data = stbi_load(_texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// TODO: Add this inside a class transform
	position = new glm::vec3(0, 0, 0);
	rotation = new glm::vec3(0, 0, 0);
	scale = new glm::vec3(1, 1, 1);
	model = new glm::mat4(); 
}

void UIImage::Render(Window * _window, Shader * _shader)
{
	_shader->Use();

	CalcModelMatrix();
	_shader->SetMat4("model", *model);
	// bind Texture
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void UIImage::CalcModelMatrix()
{
	(*model)[0][0] = 1.0f;
	(*model)[1][0] = 0.0f;
	(*model)[2][0] = 0.0f;

	(*model)[0][1] = 0.0f;
	(*model)[1][1] = 1.0f;
	(*model)[2][1] = 0.0f;

	(*model)[0][2] = 0.0f;
	(*model)[1][2] = 0.0f;
	(*model)[2][2] = 1.0f;

	*model = glm::translate(*model, *this->position);
	*model = glm::rotate(*model, this->rotation->x, glm::vec3(1, 0, 0));
	*model = glm::rotate(*model, this->rotation->y, glm::vec3(0, 1, 0));
	*model = glm::rotate(*model, this->rotation->z, glm::vec3(0, 0, 1));
	*model = glm::scale(*model, *this->scale);
}

UIImage::~UIImage()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	delete position;
	delete rotation;
	delete scale;
	delete model;
}

}}