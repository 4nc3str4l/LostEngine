#pragma once

#include<glad/glad.h>

namespace le { namespace gfx{

enum DepthBufferTypes
{
	NONE = 0,
	DEPTH_TEXTURE = 1,
	DEPTH_RENDER_BUFFER = 2,
};

class Fbo
{


public:
	Fbo(GLuint _width, GLuint _heigth, DepthBufferTypes _depthBufferType);
    ~Fbo();
    void bindFrameBuffer();
    void unbindFrameBuffer();
    void bindToRead();
private:
    void initialiseFrameBuffer(DepthBufferTypes _type);
    void createFrameBuffer();
    void createTextureAttachment();
    void createDepthTextureAttachment();
    void createDepthBufferAttachment();

public:
    GLuint width;
    GLuint height;
    
    GLuint frameBuffer;
    
    GLuint colorTexture;
    GLuint depthTexture;
    
    GLuint depthBuffer;
    GLuint colorBuffer;
};





}}