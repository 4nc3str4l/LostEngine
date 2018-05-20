#pragma once
#include "Fbo.h"

namespace le { namespace gfx {
    
    class ImageRenderer
    {
    private:
        Fbo* fbo;
    public:
        ImageRenderer(GLuint _width, GLuint _heigth);
        ~ImageRenderer();
    protected:
        void renderQuad();
    };
    

    
}}