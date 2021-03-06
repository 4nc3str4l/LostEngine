#include "ImageRenderer.h"

namespace le { namespace gfx {
ImageRenderer::ImageRenderer(GLuint _width, GLuint _heigth)
{
    fbo = new Fbo(_width, _heigth, DepthBufferTypes::NONE);
}

ImageRenderer::ImageRenderer() {}

ImageRenderer::~ImageRenderer()
{
	if(fbo != nullptr)
		delete fbo;
}

void ImageRenderer::renderQuad(){

	if(fbo != nullptr)
		fbo->bindFrameBuffer();

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	if (fbo != nullptr)
		fbo->unbindFrameBuffer();
}

}}