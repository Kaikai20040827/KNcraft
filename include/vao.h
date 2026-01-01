#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include <debug.h>

class Vao
{
public:
    Vao();
    ~Vao();

    void bind();
    void unbind();

private:
    unsigned int vao;
};

#endif
