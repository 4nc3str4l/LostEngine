#pragma once

#include "Fbo.h"

namespace le { namespace gfx {
    
    class ImageRenderer
    {
    private:
		Fbo * fbo = nullptr;
    public:
	ImageRenderer();
        ImageRenderer(GLuint _width, GLuint _heigth);
        ~ImageRenderer();
        void renderQuad();
    };
}}