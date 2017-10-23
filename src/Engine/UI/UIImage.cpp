#include "UIImage.h"

namespace LostEngine { namespace UI {

float vertices[] = {
	// positions         // texture coords
	0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 
	0.5f, -0.5f, 0.0f,    0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f,   1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f,   1.0f, 0.0f 
};

unsigned int indices[] = {
	1, 2, 3,  // second triangle
	0, 1, 3 // first triangle
};

UIImage::UIImage(const char * _texturePath, Loader * _loader, Window* _window)
{
	VAO = _loader->CreateVAO();
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
		
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
	int nrChannels;

	unsigned char *data = stbi_load(_texturePath, &textureWidth, &textureHeigth, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	initialWindowProportion = new glm::vec2(1.0f, 1.0f);
	transform = new Transform();
	color = new glm::vec3(1.0f, 1.0f, 1.0f);
}

UIImage::UIImage(GLuint _textureID, Loader* _loader)
{
	TextureID = _textureID;

	textureWidth = 512;
	textureHeigth = 512;

	VAO = _loader->CreateVAO();
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	initialWindowProportion = new glm::vec2(1.0f, 1.0f);
	transform = new Transform();
	color = new glm::vec3(1.0f, 1.0f, 1.0f);
}

void UIImage::Render(Window * _window, Shader * _shader)
{
	_shader->Use();
	_shader->SetVec3("color", *color);
	
	CalcViewportProportion(_window);

	float lastScaleX = transform->scale->x;
	float lastScaleY = transform->scale->y;
	
	transform->scale->x = transform->scale->x * initialWindowProportion->x;
	transform->scale->y = transform->scale->y * initialWindowProportion->y;
	_shader->SetMat4("model", *transform->GetModelMatrix());
	
	transform->scale->x = lastScaleX;
	transform->scale->y = lastScaleY;

	// bind Texture
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, TextureID));

	GL_CHECK(glBindVertexArray(VAO));
	GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

// Do that only on window resize
void UIImage::CalcViewportProportion(Window * _window)
{
	if (!_window->Resized)
		return;
	std::cout << "Calculating new proportions" << std::endl;
	initialWindowProportion->x = textureWidth / (float)_window->Width * 2;
	initialWindowProportion->y = textureHeigth / (float)_window->Heigth * 2;
}


UIImage::~UIImage()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete color;
	delete transform;
}

}}