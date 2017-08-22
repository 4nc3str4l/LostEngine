#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<string>

Texture::Texture(const char* texturePath, bool flipYOnload)
{
	// Generate the texture and bind it
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(flipYOnload); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		std::string str(texturePath);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, str.substr(str.find_last_of(".") + 1) == "png" ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::use() 
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture()
{
}