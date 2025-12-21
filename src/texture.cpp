#include "Texture.h"
#include <stb_image.h>
#include <iostream>
#include <fstream>

Texture::Texture(const std::string &top_path,
                 const std::string &bottom_path,
                 const std::string &front_path,
                 const std::string &back_path,
                 const std::string &left_path,
                 const std::string &right_path)
{
    stbi_set_flip_vertically_on_load(true);

    block_front = stbi_load(
        front_path.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        4); // 加载图像数据

    block_back = stbi_load(
        back_path.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        4); // 加载图像数据

    block_top = stbi_load(
        top_path.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        4); // 加载图像数据

    block_bottom = stbi_load(
        bottom_path.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        4); // 加载图像数据

    block_left = stbi_load(
        left_path.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        4); // 加载图像数据

    block_right = stbi_load(
        right_path.c_str(),
        &m_width,
        &m_height,
        &m_channels,
        4); // 加载图像数据

    block_sides[0] = block_front;
    block_sides[1] = block_back;
    block_sides[2] = block_top;
    block_sides[3] = block_bottom;
    block_sides[4] = block_left;
    block_sides[5] = block_right;

    // if (!block_top || !block_bottom || !block_front || !block_back || !block_left || !block_right)
    // {
    //     std::cerr << "Failed to load texture" << path << std::endl;
    //     std::ofstream log("texture_load.log", std::ios::app);
    //     if (log)
    //         log << "Failed to load texture: " << path << std::endl;
    //     return;
    // }

    // std::cout << "Loaded texture '" << path << "' (" << m_width << "x" << m_height << ")" << std::endl;
    // std::ofstream log("texture_load.log", std::ios::app);
    // if (log)
    //     log << "Loaded texture '" << path << "' (" << m_width << "x" << m_height << ") id=" << m_id << std::endl;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

    // 像素风（注意 cubemap 不能 REPEAT）
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // 六个面
    for (int i = 0; i < 6; i++)
    {
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            GL_RGBA,
            m_width,
            m_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            block_sides[i]);
    }

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // 释放每一张
    for (int i = 0; i < 6; i++)
    {
        stbi_image_free(block_sides[i]);
    }
}

Texture::~Texture()
{
    if (m_id)
        glDeleteTextures(1, &m_id);
}

Texture::Texture(Texture &&other) noexcept
{
    *this = std::move(other);
}

Texture &Texture::operator=(Texture &&other) noexcept
{
    if (this != &other)
    {
        glDeleteTextures(1, &m_id);
        m_id = other.m_id;
        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        other.m_id = 0;
    }
    return *this;
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
