#include "vao.h"

Vao::Vao()
{
    GLCall(glGenVertexArrays(1, &vao));
}

Vao::~Vao()
{
}

void Vao::bind()
{
    GLCall(glBindVertexArray(vao));
}

void Vao::unbind()
{
    GLCall(glBindVertexArray(0));
}