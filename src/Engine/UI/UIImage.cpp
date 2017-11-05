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

UIImage::UIImage(const char * _texturePath, Loader * _loader, Window* _window) :
	RenderComponent(Components::SpecificType::Type_UIImage)
{
	m_Window = _window;
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	TextureID = _loader->LoadTexture(_texturePath, &textureWidth, &textureHeigth);

	initialWindowProportion = new glm::vec2(1.0f, 1.0f);
	transform = new Transform(nullptr);
	color = new glm::vec3(1.0f, 1.0f, 1.0f);
}

UIImage::UIImage(GLuint _textureID, Loader* _loader, Window* _window):
	RenderComponent(Components::SpecificType::Type_UIImage)
{
	m_Window = _window;
	TextureID = _textureID;
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, TextureID));

	textureWidth = 512;
	textureHeigth = 512;

	VAO = _loader->CreateVAO();
	GL_CHECK(glGenBuffers(1, &VBO));
	GL_CHECK(glGenBuffers(1, &EBO));

	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

	// position attribute
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0));

	// texture coord attribute
	GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
	GL_CHECK(glEnableVertexAttribArray(1));

	initialWindowProportion = new glm::vec2(1.0f, 1.0f);
	transform = new Transform(nullptr);
	color = new glm::vec3(1.0f, 1.0f, 1.0f);
}

void UIImage::Render(Shader * _shader)
{
	_shader->Use();
	_shader->SetVec3("color", *color);
	
	CalcViewportProportion(m_Window);

	float lastScaleX = transform->scale->x;
	float lastScaleY = transform->scale->y;
	
	transform->scale->x = transform->scale->x * initialWindowProportion->x;
	transform->scale->y = transform->scale->y * initialWindowProportion->y;
	_shader->SetMat4("model", *transform->GetModelMatrix());
	
	transform->scale->x = lastScaleX;
	transform->scale->y = lastScaleY;

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
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