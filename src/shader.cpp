#include "shader.h"

Shader::Shader(const std::string &filepath)
    : m_FilePath(filepath)
{
    ShaderSource source = parseShaderFile(filepath);
    m_RendererID = createShader(source.VertexSource,
                                source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
    LOG("Using program ID = " + std::to_string(m_RendererID));
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

/* ================= Shader 创建 ================= */

unsigned int Shader::createShader(const std::string &vertex,
                                  const std::string &fragment)
{
    LOG("Creating a shader program...");
    GLCall(unsigned int program = glCreateProgram());
    LOG("Creating a shader program done");

    LOG("Compiling vertex shader...");
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex);
    LOG("Compiling vertex shader done");
    LOG("Compiling fragment shader...");
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment);
    LOG("Compiling fragment shader done");

    LOG("Attaching vertex shader...");
    GLCall(glAttachShader(program, vs));
    LOG("Attaching vertex shader done");
    LOG("Attaching fragment shader...");
    GLCall(glAttachShader(program, fs));
    LOG("Attaching fragment shader done");

    LOG("Compiling vertex shader...");
    GLCall(glLinkProgram(program));
    LOG("Compiling vertex shader...");

    LOG("Validating shader...");
    GLCall(glValidateProgram(program));
    LOG("Validating shader done");

    int linkStatus;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &linkStatus));
    if (linkStatus == GL_FALSE)
    {
        int length;
        GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length);
        GLCall(glGetProgramInfoLog(program, length, &length, message));

        ERR("Program link failed");
        ERR(message);

        GLCall(glDeleteProgram(program));
        return 0; // ← 关键
    }

    LOG("Deleting vertex shader...");
    GLCall(glDeleteShader(vs));
    LOG("Deleting vertex shader done");
    LOG("Deleting fragment shader...");
    GLCall(glDeleteShader(fs));
    LOG("Deleting fragment shader done");

    return program;
}

unsigned int Shader::compileShader(unsigned int type,
                                   const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int success;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length);
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        ERR(std::string("Shader compile failed (") + (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") + ")");
        ERR(message);

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

/* ================= Shader 解析 ================= */

Shader::ShaderSource Shader::parseShaderFile(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE,
        VERTEX,
        FRAGMENT
    };
    ShaderType type = ShaderType::NONE;

    std::stringstream ss[2];

    std::string line;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type - 1] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

/* ================= Uniform ================= */

int Shader::getUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.count(name))
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist\n";

    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::setUniform4f(const std::string &name,
                          float v0, float v1, float v2, float v3)
{
    bind();
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string &name,
                             const glm::mat4 &matrix)
{
    bind();
    GLCall(glUniformMatrix4fv(getUniformLocation(name),
                              1, GL_FALSE, &matrix[0][0]));
}
