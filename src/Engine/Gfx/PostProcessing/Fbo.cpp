#include "Fbo.h"

namespace le { namespace gfx{

Fbo::Fbo(const GLuint _width, const int _heigth, DepthBufferTypes _depthBufferType)
{
	width = _width;
	height = _heigth;
	initialiseFrameBuffer(_depthBufferType);
}

void Fbo::bindFrameBuffer() 
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
}
 
void Fbo::unbindFrameBuffer() 
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::Width, Window::Heigth);
}
 

void Fbo::bindToRead() 
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
}
 
void Fbo::initialiseFrameBuffer(DepthBufferTypes _type) 
{
    createFrameBuffer();
    createTextureAttachment();
    if (_type == DepthBufferTypes::DEPTH_RENDER_BUFFER) {
        createDepthBufferAttachment();
    } else if (_type == DepthBufferTypes::DEPTH_TEXTURE) {
        createDepthTextureAttachment();
    }
    unbindFrameBuffer();
}
 
 void Fbo::createFrameBuffer() 
 {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}


void Fbo::createTextureAttachment() 
{
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
}
 

void Fbo::createDepthTextureAttachment() 
{
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
}
 
void Fbo::createDepthBufferAttachment() 
{
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
}

Fbo::~Fbo()
{
    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteTextures(1, &colorTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteRenderbuffers(1, &colorBuffer);
}

}}

