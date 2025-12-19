#ifndef MESH_H
#define MESH_H

class CubeMesh {
public:
    CubeMesh();
    ~CubeMesh();

    void draw() const;

private:
    unsigned int VAO, VBO;
};

#endif