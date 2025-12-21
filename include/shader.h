#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char *vertexSrc, const char *fragmentSrc);
    ~Shader();

    void use() const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec4(const std::string &name, const glm::vec4 &vec) const;
    void setInt(const std::string &name, int value) const;

private:
    unsigned int programID;

    unsigned int compile(unsigned int type, const char *src);
};

#endif