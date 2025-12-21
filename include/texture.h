#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <unordered_map>

class Texture
{
public:
    Texture(const std::string &front_path,
            const std::string &back_path,
            const std::string &top_path,
            const std::string &bottom_path,
            const std::string &left_path,
            const std::string &ight_path);
            
    ~Texture();

    // 禁止拷贝（OpenGL 资源不能随便复制）
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    // 允许移动
    Texture(Texture &&other) noexcept;
    Texture &operator=(Texture &&other) noexcept;

    void bind(unsigned int slot = 0) const;
    static void unbind();

    inline unsigned int id() const
    {
        return m_id;
    }

private:
    GLuint m_id = 0;
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;

    GLubyte *block_front;
    GLubyte *block_back;
    GLubyte *block_top;
    GLubyte *block_bottom;
    GLubyte *block_left;
    GLubyte *block_right;

    // 0 front, 1 back
    // 2 top,   3 bottom
    // 4 left,  5 right
    GLubyte *block_sides[];
};

#endif