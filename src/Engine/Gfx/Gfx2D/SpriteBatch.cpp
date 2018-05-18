#include "SpriteBatch.h"

namespace le { namespace gfx2d {

const int MAX_INSTANCES =  70000;
const int INSTANCE_DATA_LENGTH = 21;

float SpriteBatch::m_vertices[8]{ -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f };
float SpriteBatch::m_buffer[MAX_INSTANCES * INSTANCE_DATA_LENGTH];
unsigned int SpriteBatch::m_bufferPointer = 0;

SpriteBatch::SpriteBatch(Loader* _loader, Shader* _shader)
{
    m_shader = _shader;
	m_loader = _loader;
	m_vbo = _loader->CreateEmptyVBO(INSTANCE_DATA_LENGTH * MAX_INSTANCES);
	m_quad = _loader->LoadToVAO(m_vertices, 2, 8);

	_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
	_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
	_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
	_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);
	_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 5, 4, INSTANCE_DATA_LENGTH, 16);
	_loader->AddInstancedAttributes(m_quad->VaoID, m_vbo, 6, 1, INSTANCE_DATA_LENGTH, 20);
}

SpriteBatch::~SpriteBatch()
{
	delete m_shader;
	delete m_quad;
}

void SpriteBatch::Prepare()
{
	m_shader->Use();
	glBindVertexArray(m_quad->VaoID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
}

void SpriteBatch::Render(std::map<GLuint, std::vector<Sprite*>*> _sprites)
{
    //TODO(4nc3stral): Implement!
}

void SpriteBatch::Finish()
{
    //TODO(4nc3stral): Implement!
}

void SpriteBatch::BindTexture(GLuint texture)
{
    //TODO(4nc3stral): Implement!
}

void SpriteBatch::StoreMatrixData(const glm::mat4& _matrix)
{
	m_buffer[m_bufferPointer++] = _matrix[0][0];
	m_buffer[m_bufferPointer++] = _matrix[0][1];
	m_buffer[m_bufferPointer++] = _matrix[0][2];
	m_buffer[m_bufferPointer++] = _matrix[0][3];

	m_buffer[m_bufferPointer++] = _matrix[1][0];
	m_buffer[m_bufferPointer++] = _matrix[1][1];
	m_buffer[m_bufferPointer++] = _matrix[1][2];
	m_buffer[m_bufferPointer++] = _matrix[1][3];

	m_buffer[m_bufferPointer++] = _matrix[2][0];
	m_buffer[m_bufferPointer++] = _matrix[2][1];
	m_buffer[m_bufferPointer++] = _matrix[2][2];
	m_buffer[m_bufferPointer++] = _matrix[2][3];

	m_buffer[m_bufferPointer++] = _matrix[3][0];
	m_buffer[m_bufferPointer++] = _matrix[3][1];
	m_buffer[m_bufferPointer++] = _matrix[3][2];
	m_buffer[m_bufferPointer++] = _matrix[3][3];
}

void SpriteBatch::UpdateTexCoordInfo(Sprite* _sprite)
{
    //TODO(4nc3stral): Implement!
}


}}