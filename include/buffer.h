#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Buffer {
public:
    Buffer(const void* data, unsigned int size);
    ~Buffer();
    
private:
    unsigned int ID;
    unsigned int size;
};

#endif