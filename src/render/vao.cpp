#include "render/vao.h"

Vao::Vao()
{
    GLCall(glGenVertexArrays(1, &m_vao));
}

Vao::~Vao()
{
}

void Vao::bind()
{
    GLCall(glBindVertexArray(m_vao));
}

void Vao::unbind()
{
    GLCall(glBindVertexArray(0));
}