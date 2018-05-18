#include "WaterFrameBuffer.h"

namespace le { namespace water {
	WaterFrameBuffer::WaterFrameBuffer(le::gfx::Window* _window)
	{
		window = _window;
		InitializeReflectionFrameBuffer();
		InitializeRefractionFrameBuffer();
	}

	WaterFrameBuffer::~WaterFrameBuffer()
	{
		glDeleteFramebuffers(1, &ReflectionFrameBuffer);
		glDeleteTextures(1, &ReflectionTexture);
		glDeleteRenderbuffers(1, &ReflectionDepthBuffer);

		glDeleteFramebuffers(1, &RefractionFrameBuffer);
		glDeleteTextures(1, &RefractionTexture);
		glDeleteTextures(1, &RefractionDepthTexture);
	}

	void WaterFrameBuffer::BindReflectionFrameBuffer()
	{
		BindFrameBuffer(ReflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
	}

	void WaterFrameBuffer::BindRefractionFrameBuffer()
	{
		BindFrameBuffer(RefractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
	}

	void WaterFrameBuffer::UnbindCurrentFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, window->Width, window->Heigth);
	}

	void WaterFrameBuffer::InitializeReflectionFrameBuffer()
	{
		
		ReflectionFrameBuffer = CreateFrameBuffer();
		ReflectionTexture = CreateTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		ReflectionDepthBuffer = CreateDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
		UnbindCurrentFrameBuffer();
	}

	void WaterFrameBuffer::InitializeRefractionFrameBuffer()
	{
		RefractionFrameBuffer = CreateFrameBuffer();
		RefractionTexture = CreateTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		RefractionDepthTexture = CreateDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
		UnbindCurrentFrameBuffer();
	}

	void WaterFrameBuffer::BindFrameBuffer(int _frameBuffer, int _width, int _heigth)
	{
		// Make sure its not bound
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
		glViewport(0, 0, _width, _heigth);

		// Clear the buffers or anything will be displayed
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
	}

	GLuint WaterFrameBuffer::CreateFrameBuffer()
	{
		GLuint frameBuffer;
		glGenFramebuffers(1, &frameBuffer);
		//generate name for frame buffer
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		//create the framebuffer
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		//indicate that we will always render to color attachment 0
		return frameBuffer;
	}

	GLuint WaterFrameBuffer::CreateTextureAttachment(int _width, int _height)
	{
		GLuint texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
		return texId;
	}

	GLuint WaterFrameBuffer::CreateDepthTextureAttachment(int _width, int _heigth)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, _width, _heigth,
			0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			texture, 0);
		return texture;
	}

	GLuint WaterFrameBuffer::CreateDepthBufferAttachment(int _width, int _heigth)
	{
		GLuint depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width,
			_heigth);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_RENDERBUFFER, depthBuffer);
		return depthBuffer;
	}

}}

	