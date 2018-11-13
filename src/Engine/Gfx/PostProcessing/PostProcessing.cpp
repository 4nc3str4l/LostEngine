#include "PostProcessing.h"

#include "../../Tools/Log.h"
#include "../../LostEngine.h"

namespace le { namespace gfx {

void PostProcessing::init(Loader* _loader)
{
    m_Quad = _loader->LoadToVAO(m_Positions, 2, 8);
	contrast = new ContrastChanger(2.0f);
}


void PostProcessing::doPostProcessing(GLuint _colorTexture)
{
    start();
	contrast->render(_colorTexture);
    end();
}

void PostProcessing::start()
{
    glBindVertexArray(m_Quad->VaoID);
    glEnableVertexAttribArray(0);
    glDisable(GL_DEPTH_TEST);
}

void PostProcessing::end()
{
    glEnable(GL_DEPTH_TEST);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);   
}

PostProcessing::~PostProcessing()
{
    delete m_Quad;
	delete contrast;
}
}}