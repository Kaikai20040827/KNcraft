#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "debug.h"

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // uniform 接口
    void setUniform4f(const std::string& name,
                      float v0, float v1, float v2, float v3);
    void setUniformMat4f(const std::string& name,
                         const glm::mat4& matrix);

private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

private:
    struct ShaderSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    ShaderSource parseShaderFile(const std::string& filepath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertex,
                              const std::string& fragment);

    int getUniformLocation(const std::string& name);
};

#endif