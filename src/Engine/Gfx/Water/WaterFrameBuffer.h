#pragma once

#include <glad/glad.h>
#include "../Utils/Window.h"

namespace le { namespace water {

#define REFLECTION_WIDTH 320
#define REFLECTION_HEIGHT  180

#define REFRACTION_WIDTH 1280
#define REFRACTION_HEIGHT 720

class WaterFrameBuffer
{
public:
	GLuint ReflectionFrameBuffer;
	GLuint ReflectionTexture;
	GLuint ReflectionDepthBuffer;

	GLuint RefractionFrameBuffer;
	GLuint RefractionTexture;
	GLuint RefractionDepthTexture;
private:
    le::gfx::Window* window;
public:
	WaterFrameBuffer(le::gfx::Window* _window);
	~WaterFrameBuffer();
	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();
    void UnbindCurrentFrameBuffer();

private:
	void InitializeReflectionFrameBuffer();
	void InitializeRefractionFrameBuffer();
	void BindFrameBuffer(int _frameBuffer, int _width, int _heigth);
	
	GLuint CreateFrameBuffer();
	GLuint CreateTextureAttachment(int _width, int _height);
	GLuint CreateDepthTextureAttachment(int _width, int _heigth);
	GLuint CreateDepthBufferAttachment(int _width, int _heigth);
};

}}