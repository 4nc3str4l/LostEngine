#include "PostProcessing.h"

#include "../../Tools/Log.h"
#include "../../LostEngine.h"

namespace le { namespace gfx {

PostProcessing PostProcessing::instance;

void PostProcessing::init(Loader* _loader)
{
    m_Quad = _loader->LoadToVAO(m_Positions, 2, 8);
}

void PostProcessing::doPostProcessing(GLuint _colorTexture)
{
    start();

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
    LOG_INFO("Postprocessing deleted");
    std::getchar();
}
}}