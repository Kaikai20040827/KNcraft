#include "system/render/vao.h"

Vao::Vao()
{
    GLCall(glGenVertexArrays(1, &m_Vao));
}

Vao::~Vao()
{
}

void Vao::bind()
{
    GLCall(glBindVertexArray(m_Vao));
}

void Vao::unbind()
{
    GLCall(glBindVertexArray(0));
}