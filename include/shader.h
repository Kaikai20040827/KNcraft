#ifndef SHADER_H
#define SHADER_H

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath){};
    ~Shader(){};
private:
    unsigned int ID;
    std::string file_path;

};

#endif